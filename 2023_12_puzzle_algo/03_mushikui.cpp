#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

// 정수 val 가 문자열 str 에 정합한가?
// ex) 4649, **** => True
// ex) 4649, 4*** => True
// ex) 4649, 3*** => False
bool is_valid(int64_t val, const string& str) {
    // 정수 val을 문자열로 변환한다. 
    string sval = to_string(val);

    // 자릿수가 일치해야 한다. 
    if (sval.size() != str.size()) return false;

    for (int i = 0; i < sval.size(); ++i) {
        // 빈칸은 신경쓰지 않는다. 
        if (str[i] == '*') continue;

        // 일치하지 않는 부분이 있으면 False
        if (sval[i] != str[i]) return false;
    }

    return true;

}

// 수 v를 문자열 str의 오른쪽에서 k번째 적용했을 때 정합한가?
// ex) v=4, k=1, str=4*6* => false
// ex) v=4, k=0, str=4*6* => true
bool is_valid_sub(int v, int k, const string& str) {
    char c = str[(int)str.size() - 1 - k]; // k번째 위치 문자

    if (c == '*') return true;

    return (v == (c-'0'));
}

// 빈칸에 넣은 수에서 정수 전체를 복원한다. 
// ex) [3,1,4,1,5] => 51413
int64_t decode(const vector<int>& vec) {
    int64_t res = 0;
    int64_t order = 1; // 10, 100, 1000
    for (int v : vec) {
        res += order * v;
        order *= 10;
    }
    return res;
}

class Mushikuzan {
    private:
    // 피승수, 승수, 곱
    string multiplicand_, multiplier_, product_;

    // 부분곱
    vector<string> middle_;

    // 답 (피승수, 승수)
    vector<pair<int64_t, int64_t>> res_;  

    public:
        Mushikuzan( const string& multiplicand,
                    const string& multiplier,
                    const string& product,
                    const vector<string>& middle):
            multiplicand_(multiplicand), multiplier_(multiplier), product_(product), 
            middle_(middle) {}

    // 피승수가 확정된 후 승수(multiplier) 에 수를 채워 나가는 재귀함수
    void rec_plier(int64_t plicand, vector<int>& vec) {
        // 종료 조건
        if(vec.size() == multiplier_.size()) { // 승수의 모든 빈칸이 채워 있음

            // 승수를 구한다
            int64_t plier = decode(vec);

            // 정합하지 않으면 
            if(!is_valid(plicand*plier, product_)) return;

            // 정합하면 답을 저장한다. 
            res_.emplace_back(plicand, plier);
            return;
        }

        // 새 빈칸에 수를 넣는다(승수에 0은 들어가지 않는 것으로 한다)
        for (int add = 1; add <= 9; ++add) {

            // 이미 수가 들어가 있어 모순되면 건너뛴다
            if (is_valid_sub(add, vec.size(), multiplier_)) continue; 

            // 빈칸에 수를 넣고 부분곱에서 정합성을 확인한다. 
            if(!is_valid(plicand*add, middle_[vec.size()])) continue;

            vec.push_back(add);
            rec_plier(plicand, vec);
            vec.pop_back();
        }
    }

    // 피승수(multiplicand) 에 수를 채워 나가는 재귀함수
    void rec_plicand(vector<int>& vec) {
        // 종료 조건
        if(vec.size() == multiplicand_.size()) { // 피승수의 모든 빈칸이 채워 있음
            // 이번에는 rec_plier를 호출해서 승수를 채워나간다
            vector<int> vec2;
            rec_plier(decode(vec), vec2);
            return;
        }

        // 새 빈칸에 수를 넣는다
        for (int add = 0; add <= 9; ++add) {
            // 맨 왼쪽에는 0이 들어갈 수 없다. 
            if(vec.empty() && add == 0) continue;

            // 이미 수가 들어가 있어 모순되면 건너뛴다
            if (is_valid_sub(add, vec.size(), multiplicand_)) continue; 

            vec.push_back(add);
            rec_plicand(vec);
            vec.pop_back();
        }
    }

    vector<pair<int64_t, int64_t>> solve() {

        res_.clear();

        vector<int> vec;
        rec_plicand(vec);
        return res_;
    }
};

int main() {

    cout << "Input" << endl;

    int A = 7; // 피승수 자릿수
    int B = 6; // 승수 자릿수

    string multiplicand = "*1*****";
    string multiplier    = "******";
    string product = "*******9*****";

    vector<string> middle = {
        "2*3****", 
        "********", 
        "**4*5*6*",
        "*******",
        "****7*8",
        "********"
    };

    // 재귀적으로 푼다
    Mushikuzan mu(multiplicand, multiplier, product, middle);
    const vector<pair<int64_t, int64_t>>& res = mu.solve();

    // 해를 출력한다. 
    cout << "The num of solutions: " << res.size() << endl;
    for (int i = 0; i < res.size(); ++i) {
        cout << i << " th solution: "
             << res[i].first << " * " << res[i].second
             << " = " << res[i].first * res[i].second << endl;
    }

}



