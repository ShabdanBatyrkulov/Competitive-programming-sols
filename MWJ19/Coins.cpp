#include <bits/stdc++.h>

#define ll long long
 
using namespace std;

const ll linf = (ll)1e15;

int n, k;
ll ans = 1e18;
ll ans1 = 1e18;
ll g[40], pref[40];
pair < int, int > ar[40];
int pos[40];
ll dp[40][5005];
pair < int, int > pr[40][5005];
int used[40][5005];

ll get(int l, int r) {
	return pref[r] - pref[l - 1];
}

ll go(int pos, int ost) {
	if (ost == 0) return 0;
	if (pos == n) return linf;
	ll &res = dp[pos][ost];
	if (used[pos][ost]) return res;
	used[pos][ost] = 1;
	res = linf;
	for (int i = pos + 1; i < n; i++) {
		for (int j = 0; j <= ost; j++) {
			if (ost >= (n - i + 1) * j) {
				ll cost = go(i, ost - (n - i + 1) * j) + get(pos, i - 1) * (n - i + 1);
				if (cost < res) {
					res = cost;
					pr[pos][ost] = {i, j};
				}
			} else {
				break;
			}
		}
	}
	if (get(pos, n - 1) < res) {
		res = get(pos, n - 1);
		pr[pos][ost] = {n, ost};
	}
	return res;
}

main() {
	scanf("%d %d", &n, &k);
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= k; j++) {
			dp[i][j] = linf;
			pr[i][j] = {-1, 0};
		}
	}
	ll cur = 0;
	for (int i = 1; i <= n; i++) {
		cin >> g[i];
		ar[i] = {g[i], i};
	}
	if (k % n == 0) {
		cout << 0 << endl;
		for (int i = 1; i <= n; i++) {
			cout << k / n << ' ';
		}
		return 0;
	}
	sort(ar + 1, ar + n + 1);
	for (int i = 1; i <= n; i++) {
		pos[ar[i].second] = i;
		pref[i] = pref[i - 1] + ar[i].first;
	}
	for (int i = 1; i < k; i++) {
		if ((k - i) % (n - 1) == 0 && i < (k - i) / (n - 1)) {
			cout << ar[1].first * (n - 1) << endl;
			for (int j = 1; j <= n; j++) {
				if (pos[j] == 1) {
					cout << i << ' ';
				} else {
					cout << (k - i) / (n - 1) << ' ';
				}
			} 
			return 0;
		}
	}
	ll ans = 1e18;
	int res1, res2;
	int st = 1;
	for (int i = 1; i <= n; i++) {
		if (k - n * i <= 0) break;
		if (go(1, k - n * i) < ans) {
			ans = go(1, k - n * i);
			st = i;
			res2 = k - n * i;
		}
	}
	cout << ans << endl;
	res1 = 1;
	vector < int > ansv(n + 1, st);
	while (res1 > 0) {
		for (int i = pr[res1][res2].first; i <= n; i++) {
			ansv[i] += pr[res1][res2].second;
		}
		pair < int, int > asd = pr[res1][res2];
		res1 = asd.first;
		res2 -= (n - res1 + 1) * asd.second;
	}
	for (int i = 1; i <= n; i++) {
		cout << ansv[pos[i]] << ' ';
	}
}
