#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

LL N, K;

bool check(LL x) { // x보다 작거나 같은 수의 개수가 K보다 작으면 lo = mid
    LL sum = 0;
    for (LL i = 1; i <= N; ++i) {
        if (i > x) break;
        sum += min(N, x / i); // i번째 행의 수들은 i의 배수이기 때문
    }
    return sum < K;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;

    LL lo = 0, hi = N * N + 1; // lo가 가질 수 있는 최솟값 = 1, hi가 가질 수 있는 최댓값 = N * N 이기 때문

    while (lo + 1 < hi) {
        LL mid = (lo + hi) / 2;
        if (check(mid)) lo = mid;
        else hi = mid;
    }
    cout << hi << '\n';

    return 0;
}
