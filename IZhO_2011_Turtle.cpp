#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int N = (int)1e6 + 7;

int mod;
int cnt[N], lp[N];
map < pair < int, int >, int > mp;

int mult(int a, int b) {
	return (a * 1LL * b) % mod;
}

int add(int a, int b) {
	return (a + b) % mod;
}

void precalc() {
	for (int i = 2; i < N; i++) {
		if (lp[i]) continue;
		for (int j = i; j < N; j += i) {
			if (!lp[j]) {
				lp[j] = i;
			}
		}
 	}
}

void add1(int x, int val) {
	while (x > 1) {
		cnt[lp[x]] += val;
		x /= lp[x];
	}
}

int calc(int n, int k) {
	if (mp.count({n, k})) {
		return mp[{n, k}];
	} else if (k > n) {
		return 0;
	}
	int res = 1;
	for (int i = 2; i <= n; i++) {
		add1(i, 1);
	}
	for (int i = 2; i <= k; i++) {
		add1(i, -1);
	}
	for (int i = 2; i <= n - k; i++) {
		add1(i, -1);
	}
	for (int i = 2; i <= n; i++) {
		while (cnt[i] > 0) {
			res = mult(res, i);
			cnt[i]--;
		}
	}
	//return res;
	return mp[{n, k}] = res;
}

int n, m, k, t;
int dp[33][33];
int dist[33][33];
int dist1[33][33];
pair < int, int > ar[33];

main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	memset(dp, -1, sizeof dp);
	precalc();
	cin >> n >> m >> k >> t >> mod;
	if (mod == 1) {
		cout << 0;
		return 0;
	}
	n++; m++;
	for (int i = 1; i <= k; i++) {
		cin >> ar[i].first >> ar[i].second;
		ar[i].first++;
		ar[i].second++;
	}
	k++;
	ar[k] = {n, m};
	sort(ar + 1, ar + k + 1);
	for (int i = 1; i <= k; i++) {
		dp[0][i] = calc(ar[i].first + ar[i].second - 2, ar[i].first - 1);
	}
	int ans = 0;
	for (int i = 1; i <= k; i++) {
		for (int j = 1; j < i; j++) {
			// ar[i].first <= ar[j].first
			int len1 = abs(ar[i].first - ar[j].first);
			int len2 = abs(ar[i].second - ar[j].second);
			dist[i][j] = dist[j][i] = calc(len1 + len2, len1);
			dist1[i][j] = dist1[j][i] = dist[i][j];
			if (ar[j].second <= ar[i].second) {
				dp[0][i] = add(dp[0][i], mod - mult(dp[0][j], dist[i][j]));
			} 
		}
	}
	for (int i = 1; i <= k; i++) {
		for (int j = 1; j < i; j++) {
			for (int l = j + 1; l < i; l++) {
				if (ar[j].second <= ar[l].second && ar[l].second <= ar[i].second) {
					dist1[i][j] = dist1[j][i] = add(dist1[i][j], mod - mult(dist1[i][l], dist1[l][j]));
				}
			}
		}
	}
	for (int i = 1; i <= t; i++) {
		for (int j = 1; j <= k; j++) {
			dp[i][j] = dp[0][j];
			for (int l = 1; l < j; l++) {
				if (ar[l].second <= ar[j].second) {
					if (dp[i - 1][l] == -1) continue;
					dp[i][j] = add(dp[i][j], mult(dp[i - 1][l], dist1[j][l]));
				}
			}
		}
	}
	cout << dp[t][k] << endl;
}
/*
5 5 3 1 1000000000
2 2
2 3
3 3

5 5 1 0 1000000
4 5
*/
