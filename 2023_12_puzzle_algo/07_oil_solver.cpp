#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

// 각 항아리의 기름 양을 정점으로 한다. 
using Node = vector<int>;  

// 그래프 너비 탐색을 통해 기름 나누기 문제를 해결한다.
void solve(const Node& cap,   // 각 항아리에 최대로 채울 수 있는 용량
           const Node& start, // 각 항아리에 초기에 채워진 기름 양
           const Node& goal) { // 최종적으로 달성하고자 하는 각 항아리별 기름 양

    // dist: 검색 시점 start에서 각 Node까지의 최단 경로
    map<Node, int> dist;
    dist[start] = 0;

    // 경로 복원을 위한 변수
    map<Node, Node> arrow;

    // 이미 방문한 리스트 todo. 
    // start를 삽입한다. 
    queue<Node> todo;
    todo.push(start);

    // 더이상 방문할 게 없을 때까지 한다.
    while(!todo.empty())  {
        // 방문할 노드를 꺼낸다. 
        Node cur = todo.front();
        todo.pop();

        // 현재 노드에서 방문할 수 있는 노드들을 조사한다
        // (기름 나누는 법을 모두 조사한다. 항아리 from에서 항아리 to로)
        for (int from = 0; from < 3; ++from) {
            for (int to = 0; to < 3; ++to) {
                if (from == to) continue;

                // 옮겨 담은 후의 상태를 구한다. 
                Node nex = cur;
                if( nex[to] + nex[from] <= cap[to]) { //  from에서 to로 모두 옮겨 담아도 넘치지 않는 경우
                    nex[to] += nex[from];
                    nex[from] = 0;
                } else { // 넘칠 경우
                    nex[from] = nex[from] + nex[to] - cap[to]; 
                    nex[to] = cap[to];
                }

                // 옮겨 담은 후의 상태가 이미 발견한 것이라면 건너뛴다. 
                if (dist.count(nex)) continue;

                // 거리를 구하고, 경로 화살표를 구하고 
                // 오픈리스트에 추가한다. 
                dist[nex] = dist[cur] + 1;
                arrow[nex] = cur;
                todo.push(nex);
            }
        }
    }
    
    //  불가능할 경우 (goal까지 dist계산이 도달하지 못한 경우)
    if (!dist.count(goal)) {
        cout << "Impossible" << endl;
        return;
    }

    // 경로 복원 
    vector<Node> res;
    Node cur = goal;
    while(arrow.count(cur)) {
        res.push_back(cur);
        cur = arrow[cur];
    }
    res.push_back(cur);

    // 출력
    reverse(res.begin(), res.end()); // 경로 반전
    for (int i = 0; i < res.size(); ++i) {
        cout << i << " th ";
        for (int val : res[i]) cout << val <<" ";
        cout << endl;
    }


}

int main() {

    Node cap = {10, 7, 3};
    Node start = {10,0,0};
    Node goal = {5,5,0};

    solve(cap, start, goal);

}