#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 21
#define INF 5001

using namespace std;

int dp[MAX][2];

int main() {
	int N, K;
	cin >> N;
	vector<pair<int, int>> energy(N);
	int s, b;
	for (int i = 1; i <= N - 1; i++) {
		cin >> s >> b;
		energy[i] = make_pair(s, b);
	}
	cin >> K;
	// 초기화
	dp[1][0] = 0;
	dp[1][1] = INF;
	dp[2][0] = dp[1][0] + energy[1].first;
	dp[2][1] = INF;
	dp[3][0] = min(dp[2][0] + energy[2].first, dp[1][0] + energy[1].second);
	dp[3][1] = INF;
	for (int i = 4; i <= N; i++) {
		// 이전에 단 한번의 큰 점프 기회를 사용하지 않은 경우
		dp[i][0] = min(dp[i - 1][0] + energy[i - 1].first, dp[i - 2][0] + energy[i - 2].second);
		// 이전에 단 한번의 큰 점프 기회를 사용한 경우
		dp[i][1] = min(min(dp[i - 3][0] + K, dp[i - 2][1] + energy[i - 2].second), dp[i - 1][1] + energy[i - 1].first);
	}
	cout << min(dp[N][0], dp[N][1]) << '\n';
}
