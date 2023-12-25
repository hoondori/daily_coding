#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

// 두 문자열, S, T 사이의 편집거리 측정
int solve(const string& S, const string& T) {

    int M = S.size();
    int N = T.size();

    //동적 계획법을 위한 배열
    // 배열 전체를 무한대를 나타내는 값으로 초기화한다.  (여기선 N+M)
    vector<vector<int>> dp(M+1, vector<int>(N+1, N+M));

    dp[0][0] = 0;

    // 각 정점의 최단거리를 순서대로 구해 나간다. 
    for (int x = 0 ; x <= M; ++x) {
        for (int y = 0; y <= N; ++y) {
            //위쪽 정점에서 출발하는 경로를 고려한다. 
            if (x > 0) {
                dp[x][y] = min(dp[x][y], dp[x-1][y] + 1);
            }

            //왼쪽 정점에서 출발하는 경로를 고려한다. 
            if (y > 0) {
                dp[x][y] = min(dp[x][y], dp[x][y-1] + 1);
            }

            // 왼쪽 위 정점에서 출발하는 경로를 고려한다. 
            if (x > 0 && y > 0) {
                // 문자가 일치할 경우 간선의 길이는 0이 된다.
                int length = 1;
                if (S[x - 1] == T[y -1]) length = 0;

                // 갱신
                dp[x][y] = min(dp[x][y], dp[x-1][y-1] + length);
            }
        }
    }

    return dp[M][N]; // 최종 편집거리
}

int main() {

    string S = "ROOF";
    string T = "SOFT";

    cout << solve(S, T) << endl;
}