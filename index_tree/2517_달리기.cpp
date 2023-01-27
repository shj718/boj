#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 500000

using namespace std;
typedef long long lld;

lld tree[4 * MAX];
int PIV;
vector<pair<int, int>> arr;

void update(int idx, int val) {
	idx += PIV;
	tree[idx] += val;
	while (idx >>= 1) {
		tree[idx] += val;
	}
}

lld query(int l, int r) {
	lld sum = 0;
	l += PIV;
	r += PIV;
	while (l <= r) {
		if (l & 1)
			sum += tree[l++];
		if (~r & 1)
			sum += tree[r--];
		l >>= 1;
		r >>= 1;
	}
	return sum;
}

int main() {
	int N;
	cin >> N;
	for (PIV = 1; PIV <= MAX; PIV <<= 1); // 첫번째 리프 노드 인덱스 계산
	int x;
	for (int i = 0; i < N; i++) {
		cin >> x;
		arr.push_back(make_pair(x, i)); // 실력, 순서 삽입
	}

	sort(arr.begin(), arr.end()); // 실력 순으로 오름차순 정렬
	for (int i = 0; i < N; i++) {
		arr[i].first = i + 1; // 실력 값 재설정
		swap(arr[i].first, arr[i].second); // 다시 원래 순서대로 정렬하기 위해 swap 진행
	}
	sort(arr.begin(), arr.end());

	int ability;
	for (int i = 0; i < N; i++) {
		ability = arr[i].second;
		update(ability, 1);
		cout << query(ability + 1, N) + 1 << '\n';
	}
}
