
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <utility>

using namespace std;

// 역폴란드 표기법의 계산식을 계산한다. 
// ex) 612+x- => 6*(1+2)-8 = 10
double calc_poland(const string& exp) {
    // 계산을 위한 배열
    vector<double> space;

    // 역폴란드 표기법 exp의 각 문자 c를 순서로 본다
    for (char c : exp) {
        if (c >= '0' && c <= '9') {
            // 숫자를 표기하는 문자인 경우는 숫자로 변경
            int int_val = c - '0';

            // 배열 말미에 삽입
            space.push_back(int_val);
        } else {
            // 연산자인 경우는 말미에서 2개의 수를 꺼낸다. 
            double second = space.back();
            space.pop_back();
            double first = space.back();
            space.pop_back();

            // 연산 결괄를 배열 말미에 삽입
            if (c == '+') 
                space.push_back(first + second);
            else if (c == '-')
                space.push_back(first - second);
            else if (c == '*')
                space.push_back(first * second);
            else    
                space.push_back(first / second);
        }
    }

    // 배열 말미에 남아있는 값을 반환한다. 
    return space.back();    
}

// 역폴란드 표기법 계산식에서 기존 계산식을 복원한다. 
// ex) 612+x- => 6*(1+2)-8
string decode_poland(const string& exp) {
    // 복원을 위한 배열
    vector<string> space;

    // 역폴란드 표기법 exp의 각 문자 c를 순서로 본다
    for (char c : exp) {
        if (c >= '0' && c <= '9') {
            // 숫자를 표기하는 문자 c는 문자열로 변환해 말미에 삽입
            space.push_back({c});
        } else {
            // 연산자인 경우는 말미에서 2개의 계산식을 꺼낸다. 
            string second = space.back();
            space.pop_back();
            string first = space.back();
            space.pop_back();

            // 곱셈, 나눗셈의 우선순위가 높으므로 그 전후의 계산식에 괄호를 붙인다.(단독수 제외)
            if (c == '*' || c == '/') {
                if (first.size() > 1)
                    first = "(" + first + ")";
                if (second.size() > 1) 
                    second = "(" + second + ")"; 
            }

            // 연산자를 토대로 복원한 계산식을 배열 말미에 삽입
            if (c == '+') 
                space.push_back(first + " + " + second);
            else if (c == '-')
                space.push_back(first + " - " + second);
            else if (c == '*')
                space.push_back(first + " * " + second);
            else    
                space.push_back(first + " / " + second);
        }
    }
    return space.back(); // 제일 말미에 있는 것이 복원된 것
}


// 텐퍼즐 프로그램
// val: 4개 수를 저장한 배열, target: 만들고자 하는 수
vector<string> solve(vector<int> val, int target) {
    // 답을 나타내는 계산기를 저장할 배열
    vector<string> res;

    const double EPS = 1e-9;
    auto check = [&](const string& exp) -> void {
        if(abs(calc_poland(exp) - target) < EPS)
            res.push_back(decode_poland(exp));
    };

    // 4개의 수 val의 정렬을 순서대로 시험한다. 
    sort(val.begin(), val.end());
    do {
        // 4개의 문자를 연결해 가능한 문자열 fours 를 만든다. 
        string fours = "";
        for (int v : val) fours += to_string(v);

        // 4^3 = 64 가지 연산자 조합을 알아본다. 6가지 패턴
        const string ops = "+-*/";
        for (char op1: ops) {
            for (char op2: ops) {
                for (char op3: ops) {
                    // 패턴 xxxxooo 
                    string exp = fours + op1 + op2 + op3;
                    check(exp);

                    // 패턴 xxxoxoo
                    swap(exp[3], exp[4]), check(exp);

                    // 패턴 xxxooxo
                    swap(exp[4], exp[5]), check(exp);

                    // 패턴 xxoxoxo
                    swap(exp[2], exp[3]), check(exp);

                    // 패턴 xxoxxoo
                    swap(exp[4], exp[5]), check(exp);
                }
            }
        }
    } while (next_permutation(val.begin(), val.end()));
    return res;
}

int main()
{
    string exp = "612+*8-";
    cout << exp << " = " << decode_poland(exp) << " = " << calc_poland(exp);
    cout << endl;

    vector<int> val = {1,3,3,7};
    int target = 10;

    vector<string> res = solve(val, target);

    for (const string& exp : res)
        cout << exp << " = " << target << endl;

}

