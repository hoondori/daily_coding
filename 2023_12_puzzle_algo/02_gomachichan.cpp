#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <utility>
using namespace std;

// 연산자의 종류
const int EMPTY = 0;
const int PLUS = 1;
const int MINUS = 2;
const int MUL = 3;
const int DIV = 4;

// 만들고자 하는 수 
const int TARGET = 100;

// 공백 처리 함수 : 나머지 연산은 그대로 둔다
pair<vector<double>, vector<int>> calc_empty(const vector<int> &signs) {

    // 공백 처리한 후의 연산식을 나타내는 데이터
    vector<double> new_vals; // 수
    vector<int> new_signs; // 연산자

    // 맨 처음 값
    double val = 1;

    for (int i = 0; i < signs.size(); ++i) {
        
        // 그 다음 수
        double add = i + 2;
        
        if (signs[i] == EMPTY) {
            // 두 수를 연결 ex) 23 4 =>23*10 + 4
            val = val * 10 + add;
        } else {
            new_vals.push_back(val);
            new_signs.push_back(signs[i]);

            // 직후의 새 값을 val에 기록
            val = add;    
        }
    }

    // 마지막 값을 기록
    new_vals.push_back(val);
    return make_pair(new_vals, new_signs);
}

// 곱셈 나눗셈 처리 함수 : 입력 연산자는 곱셈, 나눗셈, 덧셈, 뺄샘이 들어오는 데 그 중에서 곱셈과 나눗셈만 처리 
pair<vector<double>, vector<int>> 
calc_mul_div(const vector<double> &vals, const vector<int> &signs) {

    // 처리한 후의 연산식을 나타내는 데이터
    vector<double> new_vals; // 수
    vector<int> new_signs; // 연산자

    // 도중 경과 값
    double val = vals[0];

    for (int i = 0; i < signs.size(); ++i) {
        
        // 그 다음 수
        double add = vals[i + 1];
        
        if (signs[i] == MUL) {
            val *= add;
        } else if (signs[i]==DIV) {
            val /= add;
        } else {
            // 곱셈, 나눗셈이 아닌 경우 수와 연산자의 조합을 새로 기록한다.
            new_vals.push_back(val);
            new_signs.push_back(signs[i]);

            // 직후의 새 값을 val에 기록
            val = add;    
        }
    }

    // 마지막 값을 기록
    new_vals.push_back(val);
    return make_pair(new_vals, new_signs);
}


// 덧셈 뺄샘 처리 함수 : 입력 연산자는 덧셈, 뺄샘밖에 없다고 가정
double calc_plus_minus(const vector<double> &vals, const vector<int> &signs) {

    // 답을 나타내는 변수
    double res = vals[0];

    // 연산자를 순서대로 살펴본다
    for (int i = 0; i < signs.size(); ++i) {
        
        // 그 다음 수
        double add = vals[i + 1];
        
        if (signs[i] == PLUS) {
            res += add;
        } else if (signs[i] == MINUS) {
            res -= add;
        } 
    }
    return res;
}


double calc(const vector<int>& signs) {
    // Step 1. 공백 연결 : 1 2*3+4 => 12*3+4
    pair<vector<double>, vector<int>> step1 = calc_empty(signs);

    // Step 2. 곱셈,나눗셈 연결 :  12*3+4 => 36+4
    pair<vector<double>, vector<int>> step2 = calc_mul_div(step1.first, step1.second);

    // Step 3. 덧셈, 뺄샘 연결 : 36+4 = 40
    return calc_plus_minus(step2.first, step2.second);
}

// 수식 재현
string decode(const vector<int>& signs) {
    string res = "1";
    for (int i = 0; i < signs.size(); ++i) {
        if (signs[i] == PLUS) res += " + ";
        else if (signs[i] == MINUS) res += " - ";
        else if (signs[i] == MUL) res += " * ";
        else if (signs[i] == DIV) res += " / ";
        
        res += to_string(i+2);
    }
    return res;
}


void rec(vector<int> &vec, vector<string>& res){
    if (vec.size() == 8) {
        // 종료 조건 

        const double EPS = 1e-9;
        if (abs(calc(vec) - TARGET) < EPS)
            res.push_back(decode(vec));

        return; // 재귀 처리를 마친다.
    }

    // vec 말미에 값 5를 순서대로 삽입해 시험한다. 
    for (int add = 0; add < 5; ++add) {
        vector<int> vec2 = vec;

        vec2.push_back(add);

        // 재귀호출
        rec(vec2, res);
    }
}

int main() {
    vector<int> vec;

    vector<string> res;
    rec(vec, res);

    // 답을 출력
    cout << "The number of solutions : " << res.size() << endl;
    for (const string& str : res) {
        cout << str <<" = " << TARGET << endl;
    }
}