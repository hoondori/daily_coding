#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <utility>

using namespace std;

// 좌표
using Cor = pair<int, int>;

// 상하좌우 이동 좌표(0: 아래, 1: 오른쪽, 2:위, 3:왼쪽)
const vector<Cor> DIR = {Cor(1,0), Cor(0,1), Cor(-1,0), Cor(0, -1)};

// 확정되지 않은 값(거리)
const int NOTIN = -1;

// 미로 프로그램
// board: 미로 판, 칸(x,y)의 정보는 board[x][y] 로 얻는다. 
// start : 시작 지점 좌표
// goal : 목표 지점 좌표
void solve(const vector<string>& board,
           const Cor& start,
           const Cor& goal) {

    // 판의 가로, 세로 사이즈 
    int H = board.size(), W = board[0].size();

    // nodes[k] : k 번째 방문한 노드를 중심으로 볼때, 해당 좌표에서 방문 가능한 인접 노드들 관리 (너비 탐색용)
    vector<vector<Cor>> nodes;

    // dist[x][y]: 시작지점에서 칸(x,y) 까지의 소요된 거리 (block distance)
    vector<vector<int>> dist(H, vector<int>(W, NOTIN));

    // arrow[x][y] : 칸(x,y) 를 시점으로 하는 화살표 종점 좌표 (경로 복원용)
    vector<vector<Cor>> arrow(H, vector<Cor>(W, Cor(NOTIN, NOTIN)));

    // 시작 지점에 관한 정보로 탐색 정보를 초기화한다. 
    nodes.push_back(vector<Cor>(1,start));
    dist[start.first][start.second] = 0;

    // 너비 우선 탐색한다 (새 nodes 가 빌 때까지 실시)
    while(!nodes.back().empty()) {
        // 마지막에 추가된 "이동 가능한 칸의 집합"
        const vector<Cor>& cur = nodes.back();

        // 이동 가능 칸들을 방문하면서 새로운 이동 가능한 칸들을 구한다
        vector<Cor> nex;
        for (const Cor& cell : cur) {
            // cell의 좌표값
            int x = cell.first, y = cell.second;

            // cell의 상하좌우의 칸을 순서대로 살펴본다. 
            for (int direction = 0; direction < 4; ++direction) {
                int new_x = x + DIR[direction].first;
                int new_y = y + DIR[direction].second;

                // 새 칸이 판 밖에 있는 경우는 건너뛴다. 
                if (new_x < 0 || new_x >= H) continue;
                if (new_y < 0 || new_y >= W) continue;

                // 새 칸이 벽일 경우는 건너뛴다. 
                if (board[new_x][new_y] == '#') continue;

                // 새 칸이 이미 방문한 경우(거리값이 적혀 있는 경우)는 건너뛴다. 
                if (dist[new_x][new_y] != NOTIN) continue;

                // 세 칸의 거리값과 화살표를 적는다(즉 방문한다)
                dist[new_x][new_y] = dist[x][y] + 1; // 현재 cell의 거리보다 한 단계가 더 길다. 
                arrow[new_x][new_y] = Cor(x,y);
                nex.push_back(Cor(new_x, new_y));
            }
        }
        // 이동 가능한 칸들을 nodes 말미에 추가한다. (expand 후보 등록)
        nodes.push_back(nex);
    }

    // 여기까지 오면 모든 칸들을 방문하게 된다. 

    // 시작지점에서 도착지점으로 이동할 수 없게 되는 경우(미로 탈출 실패)는 예외처리한다. 
    if (dist[goal.first][goal.second] == NOTIN) {
        cout << "No Path" << endl;
        return;
    }

    // 도달지점에서 화살표를 따라감으로써 시작점에 도달하는 경로를 복원한다. 
    vector<string> res = board;
    int cur_x = goal.first, cur_y = goal.second;
    while( arrow[cur_x][cur_y] != Cor(NOTIN, NOTIN)) { // 시작점에 도달전까지.. 시작점만 화살표가 없음 
        res[cur_x][cur_y] = 'o';

        // 화살표를 따라 cursor 이동
        int new_x = arrow[cur_x][cur_y].first;
        int new_y = arrow[cur_x][cur_y].second;
        cur_x = new_x; cur_y = new_y;
    }

    // 최단 경로를 출력한다. 
    cout << "----------- solution ----------" << endl;
    for (const string& str: res) cout << str << endl;
    cout << "length = " << dist[goal.first][goal.second] << endl;
}

int main() {
    cout << "MAZE Input: " << endl;
    int H = 8, W = 8;

    // # 은 벽, . 은 이동 가능, S는 시작, G는 목표
    vector<string> board = {
        ".#....#G", 
        ".#.#....", 
        "...#.##.",         
        "#.##...#",
        "...###.#",
        ".#.....#",
        "...#.#..",
        "S......."
    };
    for (const string& str: board) cout << str << endl;

    // 시작지점과 도착지점을 구한다. 
    Cor start, goal;
    for (int x = 0; x < H; ++x) {
        for (int y = 0; y < W; ++y) {
            if (board[x][y] == 'S')
                start = Cor(x,y);
            else if (board[x][y] == 'G')
                goal = Cor(x,y);
        }
    }

    // 미로를 푼다
    solve(board, start, goal);
}
