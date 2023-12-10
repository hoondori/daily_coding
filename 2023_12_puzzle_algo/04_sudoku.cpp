#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <utility>
using namespace std;

using Field = vector<vector<int>>;

class Sudoku {
    private:
        Field field_;  // 스도쿠 판
    public:
        Sudoku() : field_(9, vector<int>(9, -1)) {}  // 9x9, init by -1 

        const Field& get() {
            return field_;
        }

        // 칸(x,y)에 수 val을 넣는다. 
        void put(int x, int y, int val) {
            field_[x][y] = val;
        }

        // 칸(x,y)에 수를 삭제한다.  
        void reset(int x, int y) {
            field_[x][y] = -1;
        }

        // 반칸을 찾는다. (부존재시 false)
        bool find_empty(int &x, int& y) {
            for(x = 0; x < 9; ++x) 
                for(y = 0; y < 9; ++y) 
                    if (field_[x][y] == -1)
                        return true;
            return false;
        }

        // 칸(x,y)에 넣을 수 있는 수의 집합을 반환한다. 
        vector<int> find_choices(int x, int y) {
            // 칸(x,y) 와 같은 행, 같은 열, 블록에 있는 수를 구한다. 
            set<int> cannot_use;

            // 같은 행에 포함된 수를 제외한다. 
            for(int i = 0; i < 9; ++i) 
                if (field_[x][i] != -1)
                    cannot_use.insert(field_[x][i]);

            // 같은 열에 포함된 수를 제외한다. 
            for(int i = 0; i < 9; ++i) 
                if (field_[i][y] != -1)
                    cannot_use.insert(field_[i][y]);

            // 같은 블록(3x3)에 포함된 수를 제외한다. 
            int x2 = x / 3 * 3, y2 = y / 3 * 3; //같은 블록의 왼 위쪽 칸
            for (int i = x2; i < x2 + 3; ++i)
                for (int j = y2; j < y2 + 3; ++j)
                    if (field_[i][j] != -1)
                        cannot_use.insert(field_[i][j]);

            // 칸 (x,y)에 넣을 수 있는 수로 이루어진 배열을 구한다. 
            vector<int> res;
            for (int val =1; val <=9; ++val) 
                if (!cannot_use.count(val))
                    res.push_back(val);
            return res;
        }

        // 입력 데이터를 받는다. 
        void input() {
            field_ = {
                { 5, 3, -1, -1, 7, -1, -1, -1, -1},
                { 6,-1, -1,  1, 9,  5, -1, -1, -1},
                {-1, 9,  8, -1,-1, -1, -1,  6, -1},
                { 8,-1, -1, -1, 6, -1, -1, -1,  3},
                { 4,-1, -1,  8,-1,  3, -1, -1,  1},
                { 7,-1, -1, -1, 2, -1, -1, -1,  6},
                {-1, 6, -1, -1,-1, -1,  2,  8, -1},
                {-1,-1, -1,  4, 1,  9, -1, -1,  5},
                {-1,-1, -1, -1, 8, -1, -1,  7,  9} 
            };
        }
};

void dfs(Sudoku& board, vector<Field>& res, bool all = true) {
    // 조건 all이 false일 때는 해를 1개 구하면 중단한다. 
    if(!all && !res.empty()) return;

    // 빈칸을 찾는다. (존재하지 않으면 종료)
    int x, y;
    if(!board.find_empty(x,y)) {
        // 해에 추가
        res.push_back(board.get());
        return;
    }

    // 칸(x,y)에 넣을 수 있는 수 집합을 구한다. 
    const vector<int> & can_use = board.find_choices(x,y);

    // 빈 칸(x,y)에 넣을 수 있는 수를 순서대로 넣어간다. 
    for (int val: can_use) {
        board.put(x, y, val);
        dfs(board, res, all);
        board.reset(x,y);
    }
}

vector<Field> solve(Sudoku& board, bool all = true) {
    vector<Field> res;

    dfs(board, res, all);
    return res;
}

int main() {
    Sudoku board;
    board.input();

    vector<Field> res = solve(board);

    // 해를 출력
    if (res.size() == 0) {
        cout << "No solutions" << endl;
    } else if (res.size() > 1) {
        cout << "More than one solution" << endl;
    } else {
        const Field& answer = res[0];
        for (int x = 0; x < 9; ++x) {
            for (int y = 0; y < 9; ++y)
                cout << answer[x][y] << " ";
            cout << endl;
        }
    }
}
