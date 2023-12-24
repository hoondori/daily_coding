#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

// 좌표(x,y) 를 하나의 정수값 쌍으로 정의한다. 
using Cor = pair<int, int>;

// 이진법 표기로 나타난 배치에서 좌표 pos의 정보가 담긴 자리를 구한다
int get_digit(const Cor& pos) {
    return (pos.first * 4 + pos.second) * 4;
}

// 배치 pl의 좌표 pos 수를 구한다. 
int get_val(uint64_t pl, const Cor& pos) {

    // 칸 (x,y) 의 정보를 구하고 이 자리의 아래 자리를 삭제한다. 
    pl >>= get_digit(pos);

    // 아래 4자리를 얻는다. 
    return pl & 0b1111;
}

// 배치를 4x4 형태로 출력한다. 
void print(uint64_t pl) {
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            cout << get_val(pl, Cor(x,y)) << " ";
        }
        cout << endl;
    }
}

uint64_t input(vector<vector<uint64_t>> values, Cor& emp) {
    uint64_t pl = 0;
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            uint64_t val = values[x][y];
            if ( val == 0) 
                emp = Cor(x, y);  // 빈칸 위치 결정
            else
                pl += val << get_digit(Cor(x,y));

        }
    }
    return pl;
}

// val : 슬라이딩할 타일 수  ex) 13
// pos: 배치 pl에서 슬라이딩할 좌표  ex) (2,1)
// emp : 배치 pl에서 빈칸 좌표 (2,2)
uint64_t slide(uint64_t pl, int val, const Cor& pos, const Cor& emp) {

    // 칸 pos의 수 val 을 삭제한다. 
    pl -= uint64_t(val) << get_digit(pos);

    // 칸 emp 에 수 val을 추가한다.
    pl += uint64_t(val) << get_digit(emp);

    return pl;
}

//  수가 val 인 타일의 본래 위치와의 맨해튼 거리를 계산한다. 
int calc_distance(int val, const Cor& pos) {
    // 목표 지점에서 패널 val의 좌표   ex) 16 => (3,3),  3 => (0, 2)
    int x = (val - 1) / 4, y = (val - 1) % 4;

    //  그 목표까지의 거리 계산
    return abs(x - pos.first) + abs(y - pos.second);
}

// 배치 pl의 추정값(goal pl 과의 거리차) 을 구한다. 
int estimate(uint64_t pl) {
    int res = 0;

    // 배치 pl 의 좌표(x,y) 타일을 순서대로 살핀다. 
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            // 값
            int val = get_val(pl, Cor(x,y));

            // 빈칸은 스킵
            if (val == 0) continue;

            // 맨허튼 거리 누적
            res += calc_distance(val, Cor(x,y));
        }
    }

    return res;
}

// 추정값을 est로 가진 배치에서 
// 수 val의 타일을 pos 위치에서 emp 위치로 슬라이딩 할 때의 배치 추정값을 구한다. 
int estimate(int est, int val, const Cor& pos, const Cor& emp) {
    return est + calc_distance(val, emp) - calc_distance(val, pos);
}

void dfs(int max_depth, // 깊이 제한값
         int depth, // 현재 깊이
         uint64_t pl,  // 현재 배치
         const Cor& emp, // 현재 배치에서의 빈칸 좌표 
         int est, // 현재 배치의 추정값, 0이면 목표 도달
         int pre_dir, // 배치 pl에서 목표배치로 이르기까지 배치 이동이 저장된다 (역순)
         vector<uint64_t> &res) {

    // 상화좌우 이동 (0: 아래, 1: 오른쪽, 2: 위쪽, 3: 왼쪽)
    static const int DX[4] = {1, 0, -1, 0};
    static const int DY[4] = {0, 1, 0, -1};

    // 만약 이미 해를 찾았다면 중단
    if (!res.empty()) return;

    // 종료 조건 : 현재 배치 pl이 목표 배치와 일치하는 경우
    if (est == 0) {
        res.push_back(pl);
        return;
    }

    // 종료 조건 : 깊이가 한계에 다다른 경우 (포기)
    if (depth >= max_depth) return;

    // 상하좌우로 이동하는 슬라이드 조작을 순서대로 시험해 본다. 
    for (int dir = 0; dir < 4; ++dir) {
        // 직전의 배치로 돌아가도록 조작하지는 않는다. 
        // 즉 이전 방향(pre_dir)이 위쪽이었고  이번 dir 이 아래로 향하는 거라면 그냥 돌아가는 것이다. 이것은 배체되어야 한다. 
        int reverse_dir = (dir + 2 ) % 4;   // ex) 위 => 아래, 오른쪽 => 왼쪽
        if (reverse_dir == pre_dir) continue;
        
        // 슬라이딩할 좌표를 계산 (빈칸 좌표를 dir 방향으로 움직이는 것)
        int nx = emp.first + DX[dir];
        int ny = emp.second + DY[dir];
        Cor pos(nx, ny);

        // 판을 벗어났다면 건너뛴다. 
        if (nx < 0 || nx >= 4 || ny < 0 || ny >=4) continue;

        // 새 배치를 구한다. 
        int val = get_val(pl, pos); // 슬라이딩할 위치에 있는 타일 수 (빈칸이 이동할 자리에 현재 있는 숫자)
        uint64_t next_pl = slide(pl, val, pos, emp);

        // 새 배치에서의 추정값을 구한다. (차분만 계산)
        int next_est = estimate(est, val, pos, emp);

        // 가지치기 조건에 걸리지 않으면 탐색을 진행한다. 
        if (depth + next_est <= max_depth) {
            // 해를 찾은 경우  res 는 배치 이력을 나타내고 찾지 못한 경우는 res는 빈 벡터이다. 
            dfs(max_depth, depth+1, next_pl, pos, next_est, dir, res);

            // 해를 찾은 경우 (dfs의 역순으로 호출되면서 goal -> ... -> start 방향으로 res가 채워질 것이다)
            if (!res.empty()) {
                res.push_back(pl);
                return;                
            }
        }
    }
}


vector<uint64_t> solve(const uint64_t& pl, const Cor& emp) {
    // 초기 추정값
    int est = estimate(pl);

    // 깊이 제한을 늘리면서 깊이 우선탐색을 한다. 
    for (int max_depth = 0; max_depth < 80; ++max_depth) {
        vector<uint64_t> res;
        dfs(max_depth, 0, pl, emp, est, -1, res);

        // 해를 찾으면 탐색 중단
        if(!res.empty()) {
            reverse(res.begin(), res.end());
            return res;
        }
    }

    return vector<uint64_t>();
}

int main() {

    cout << "15 Puzzle input: " << endl;
    
    // 초기 배치
    vector<vector<uint64_t>> values = {
        {1, 2, 3, 4}, 
        {5, 6, 0, 8},
        {9, 10, 7, 11},
        {13, 14, 15, 12}
    };

    Cor emp;   // 빈칸 좌표
    uint64_t pl = input(values, emp);
    print(pl);

    vector<uint64_t> res = solve(pl, emp);

    // 출력
    for(int i = 0; i < res.size(); ++i) {
        cout << "-----" << endl;
        cout << i << " th move: " << endl;
        print(res[i]);
    }

}