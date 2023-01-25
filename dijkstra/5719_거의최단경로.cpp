#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX 501

using namespace std;

const long long INF = 1e9;
const long long DELETED = -1;

struct edge {
	int end;
	long long cost;

	bool operator<(const edge& b) const {  // 최소 힙
		return cost > b.cost;
	}
};

vector<vector<edge>> adj;
long long dist[MAX];
vector<vector<int>> minPathAdj;
bool visited[MAX];

void dijk(int N, int S) {
	priority_queue<edge> pq;

	// 전체 dist 초기화
	for (int i = 0; i < N; i++) {
		dist[i] = INF;
	}
	// 시작점 초기화
	dist[S] = 0;
	pq.push({ S,0 });

	// 최단 경로 계산
	while (!pq.empty()) {
		edge top = pq.top();
		pq.pop();

		int nowNode = top.end;
		long long nowCost = top.cost;

		if (dist[nowNode] < nowCost) {
			continue;
		}

		int adjLen = adj[nowNode].size();
		for (int i = 0; i < adjLen; i++) {
			edge next = adj[nowNode][i];

			int nextNode = next.end;
			long long nextCost = next.cost;

			if (nextCost == -1) continue;

			if (dist[nextNode] > dist[nowNode] + nextCost) {
				dist[nextNode] = dist[nowNode] + nextCost;
				pq.push({ nextNode, dist[nextNode] });

				// 최단경로를 거꾸로 저장
				minPathAdj[nextNode].clear();
				minPathAdj[nextNode].push_back(nowNode);
			}
			if (dist[nextNode] == dist[nowNode] + nextCost) { // 최단경로가 여러개 존재할 경우 모두 저장
				minPathAdj[nextNode].push_back(nowNode);
			}
		}
	}
}

void BFS(int N, int D) { // 거꾸로 저장한 최단경로들을 제거
	fill(visited, visited + N, false);
	queue<int> q;
	// 이번에는 도착점이 시작점
	q.push(D);
	visited[D] = true;

	while (!q.empty()) {
		int nowNode = q.front();
		q.pop();

		int pathLen = minPathAdj[nowNode].size();
		for (int i = 0; i < pathLen; i++) {
			int nextNode = minPathAdj[nowNode][i];

			int adjLen = adj[nextNode].size();
			for (int j = 0; j < adjLen; j++) {
				edge prev = adj[nextNode][j];

				int prevNode = prev.end;

				if (prevNode == nowNode) { // cost를 -1로 변경
					adj[nextNode][j].cost = DELETED;

					if (!visited[nextNode]) {
						visited[nextNode] = true;
						q.push(nextNode);
					}
				}
			}
		}
	}
}

int main() {
	int N, M, S, D, u, v;
	long long p;
	while (1) {
		cin >> N >> M;
		if (N == 0 && M == 0) break;
		adj.clear(); minPathAdj.clear();
		adj.resize(N + 1); minPathAdj.resize(N + 1);
		cin >> S >> D;
		for (int i = 0; i < M; i++) {
			cin >> u >> v >> p;
			adj[u].push_back({ v,p });
		}
		// 우선 다익스트라로 최단경로 찾고
		dijk(N, S);
		// BFS로 최단경로 제거
		BFS(N, D);
		// 다시 한번 다익스트라로 최단경로 찾기
		dijk(N, S);
		cout << ((dist[D] != INF) ? dist[D] : -1) << '\n';
	}
}
