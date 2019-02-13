#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int N = (int)1e3 + 7;

int n, m;
int a[N];

main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &a[i]);
	}
	sort(a + 1, a + m + 1);
	multiset < int > s;
	s.insert(0);
	for (int i = 1; i <= m; i++) {
		int x = a[i];
		auto it = s.begin();
		while (s.size() <= n) {
			s.insert(*it + x);
			it++;
		}
		while (*it + x < *s.rbegin()) {
			s.erase(s.find(*s.rbegin()));
			s.insert(*it + x);
			it++;
		}
	}
	ll sum = 0;
	for (int to : s) {
		sum += to;
	}
	cout << sum;
}
