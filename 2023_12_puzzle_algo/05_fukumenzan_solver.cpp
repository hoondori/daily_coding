#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <utility>
using namespace std;

// 복면산
class Fukumenzan {

    private: 
        // 복면산 문자열 저장 
        vector<string> problem_;

        // 계산을 위한 변수
        vector<vector<int>> board_; // 문자에 수를 넣는 과정
        set<int> used_; // 이미 사용한 수의 집합

        // 확정되지 않은 수
        const int NOTIN = -1;
    public:
        // 생성자
        Fukumenzan(const vector<string>& input) : problem_(input) {};

        void init() {
            // 문자에 수를 넣는 판 전체를 NOTIN으로 초기화
            board_.resize(problem_.size());
            for (int i = 0; i < problem_.size(); ++i) {
                board_[i].assign(problem_[i].size(), NOTIN);
            }
            used_.clear();
        }

        // 복면산 전체의 행수
        int get_size() const { return problem_.size(); }

        // 복면산 전체의 자릿수 (맨 아래 행의 자리수)
        int get_digit() const { return problem_.back().size(); }

        // 특정 행의 자릿수
        int get_digit(int row) const { return problem_[row].size(); }

        // 수 val 이 이미 사용되었는지 여부를 반환
        bool is_used(int val) const { return used_.count(val); }

        // 복면산의 row, 오른쪽에서 digit 자리에 넣은 수를 반환한다. 
        int get_val(int row, int digit) const {
            if (digit >= get_digit(row)) return 0; // digit 자리가 row행의 문자열을 초과한 경우는 0 
            return board_[row][get_digit(row) - 1 - digit];
        }

        // 복면산의 row, 오른쪽에서 digit 자리의 문자를 반환한다. 
        int get_char(int row, int digit) const {
            return problem_[row][get_digit(row) - 1 - digit];
        }

        // 복면산의 계산 결과를 출력한다. 
        void print() const {
            for (const vector<int>& vec : board_) {
                for (int v: vec) cout << v;
                cout << endl;
            }
        }

        // 복면산의 row, 오른쪽에서 digit 자리의 문자에 값 val을 넣는다.
        void set_val(int row, int digit, int val);

        // 복면산의 row, 오른쪽에서 digit 자리에 넣은 수를 삭제한다.
        void reset_val(int row, int digit, int val);

        // 복면 문자에 넣은 수로 계산이 맞는지 확인한다. 
        bool is_valid();

        // 깊이 우선 탐색을 위한 재귀함수
        void dfs(Fukumenzan& fu, int row, int digit, vector<Fukumenzan>& res);
};

// 복면산의 row, 오른쪽에서 digit 자리의 문자에 값 val을 넣는다.
void Fukumenzan::set_val(int row, int digit, int val) {

    // 해당 자리의 문자를 구한다. 
    char c = get_char(row, digit);

    // 문자가 c인 모든 칸에 수 val 을 넣는다. 
    for (int r = 0; r < get_size(); ++r) {
        for (int d = 0; d < get_digit(r); ++d) {
            if (problem_[r][d] == c) board_[r][d] = val;
        }
    }

    // 사용을 마친 것으로 한다. 
    used_.insert(val);
}

// 복면산의 row, 오른쪽에서 digit 자리에 넣은 수를 삭제한다.
void Fukumenzan::reset_val(int row, int digit, int val) {

    // 해당 자리의 문자를 구한다. 
    char c = get_char(row, digit);

    // 문자가 c인 모든 칸에 수 val 을 삭제한다
    for (int r = 0; r < get_size(); ++r) {
        for (int d = 0; d < get_digit(r); ++d) {
            if (problem_[r][d] == c) board_[r][d] = -1;
        }
    }

    // 사용 가능하게 한다.
    used_.erase(val);
}

// 복면 문자에 넣은 수로 계산이 맞는지 확인한다. 
bool Fukumenzan::is_valid() {

    // 맨 앞쪽 자리에 0이 있으면 안된다. 
    for (const vector<int>& val : board_) {
        if (val[0] == 0) return false;
    }

    // 오른쪽 0의 자리부터 계산
    int kuriagari = 0; // 받아올림값
    for (int digit = 0; digit < get_digit(); ++digit) {
        // 맨 아래 행을 제외한 모든 행의 합을 구한다. 
        int sum = 0;
        for (int row = 0; row < get_size(); ++row) {
            // 아직 수가 들어가지 않은 행이 있는 경우에는 valid=True 이므로 즉시 종료
            if (get_val(row, digit) == NOTIN) return true;

            // 모든 행의 합을 구한다. 
            if (row != get_size()-1) sum += get_val(row, digit);
        }

        // 앞에서 올라온 받아올림(kuriagari) 을 합에 더하고 받아올림을 갱신한다. 
        sum += kuriagari;
        kuriagari = sum / 10;

        // 합이 기대되는 것과 같은지 확인한다. 아니라면 valid=False로 즉시 종료 
        if (sum % 10 != get_val(get_size() - 1, digit)) return false;
    }

    // 마지막에 받아올림 값이 있으면 valid=False, 아니라면 valid=True 이다. 
    return (kuriagari == 0);
}

// 깊이 우선 탐색을 위한 재귀함수
void dfs(Fukumenzan& fu, int row, int digit, vector<Fukumenzan>& res) {
    //cout << row << ", " << digit << endl;

    // 종료 조건 : 모든 문자에 수가 들어갔을 때
    if (row == 0 && digit == fu.get_digit() ) {
        res.push_back(fu); // 답을 저장
        return;
    }

    // 재귀 호출을 위한 다음 칸을 구한다.  (위에서 아래로, 오른쪽에서 왼쪽으로)
    int next_row = row + 1;
    int next_digit = digit;
    if (next_row == fu.get_size()) {
        next_row = 0;
        next_digit = digit + 1;
    }

    // 이미 수가 들어갔는지 여부로 조건을 나뉜다. 
    if(fu.get_val(row, digit) != -1) { // 이미 수가 들어가 있으므로 다음 호출
        dfs(fu, next_row, next_digit, res);
    } else {
        // 모든 가능한 수를 시도한다. 
        for (int val = 0; val <= 9; ++val) {
            // 이미 사용한 수는 사용할 수 없다. 
            if (fu.is_used(val)) continue;

            fu.set_val(row, digit, val);  // 셋팅하고
            if (fu.is_valid()) { // 검증하고 맞다면 
                dfs(fu, next_row, next_digit, res);
            }
            fu.reset_val(row, digit, val);  // 아니라면 리셋
        }
    }
}

// 복면산을 푸는 함수
vector<Fukumenzan> solve(Fukumenzan& fu) {
    
    // 합의 자리수가 최대가 아닌 경우 해가 존재하지 않으므로 빈 배열 반환
    for (int i = 0; i < fu.get_size() - 1; ++i) {
        if (fu.get_digit(i) > fu.get_digit()) {
            return vector<Fukumenzan>();
        }
    }

    fu.init();

    vector<Fukumenzan> res;
    dfs(fu, 0, 0, res);
    return res;
}

int main() {

    vector<string> input = {
        "INTO", 
        "ONTO", 
        "CANON",
        "INTACT",
        "AMMONIA",
        "OMISSION",
        "DIACRITIC",
        "STATISTICS",
        "ASSOCIATION",
        "ANTIMACASSAR",
        "CONTORTIONIST",
        "NONDISCRIMINATION",
        "CONTRADISTINCTION",
        "MISADMINISTRATION"
    };

    // vector<string> input = {
    //     "A", 
    //     "B", 
    //     "AC"
    // };    

    Fukumenzan fu(input);
    const vector<Fukumenzan>& res = solve(fu);

    cout << "The num of solutions: " << res.size() << endl;
    for (int i = 0; i < res.size(); ++i) {
        cout << i << " th solution:" << endl;
        res[i].print();
    }
}