#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
// #pragma warning(disable:4996)

using namespace std;

typedef long long ll;
const int mx = 10004;
const ll INF = 1e9;
ll dist[mx];
int t, n, d, c;
bool visited[mx];
int totalCnt;
ll totalTime;

struct edge {
    int end;
    ll cost;

    bool operator<(const edge& b) const {
        if (cost != b.cost) return cost > b.cost;
        return end < b.end;
    }
};
vector<vector<edge>> adj;

void init() {
    fill(&dist[0], &dist[0] + mx, INF);
}

void dijk(int start) {
    init();
    priority_queue<edge> pq;

    pq.push({ start,0 });
    dist[start] = 0;

    while (!pq.empty()) {
        edge top = pq.top();
        pq.pop();
        int nowEnd = top.end;
        int nowCost = top.cost;
        if (!visited[nowEnd]) {
            visited[nowEnd] = 1;
            totalCnt++;
        }

        if (dist[nowEnd] < nowCost) continue;

        int len = adj[nowEnd].size();
        for (int i = 0; i < len; ++i) {
            edge next = adj[nowEnd][i];
            if (dist[next.end] > dist[nowEnd] + next.cost) {
                dist[next.end] = dist[nowEnd] + next.cost;
                pq.push({ next.end, dist[next.end] });
            }
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    // freopen("C:\\Users\\hyejunseo\\source\\repos\\algo\\algo\\input.txt", "r", stdin);
    // freopen("C:\\Users\\hyejunseo\\source\\repos\\algo\\algo\\output.txt", "w", stdout);

    int a, b, s;
    cin >> t;
    while (t--) {
        totalCnt = 0;
        totalTime = -1;
        fill(&visited[0], &visited[0] + mx, 0);

        cin >> n >> d >> c;
        adj.clear();  adj.resize(n + 1);
        for (int i = 0; i < d; ++i) {
            cin >> a >> b >> s;
            adj[b].push_back({ a,s });
        }

        dijk(c);

        for (int i = 1; i <= n; ++i) {
            if (dist[i] == INF) continue;
            if (totalTime < dist[i]) totalTime = dist[i];
        }

        cout << totalCnt << ' ' << totalTime << '\n';
    }

    return 0;
}
