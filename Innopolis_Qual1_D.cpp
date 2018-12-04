#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int N = (int)1e3 + 7;
const ll linf = (ll)1e18 + 7;

ll dp[2][3][N][N];
int n, v;
ll s;
int a[N];

main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> s >> v;
	for (int i = 1; i < n; i++) {
		cin >> a[i];
	}
	int val[] = {0, v, (int)(s % v)};
	for (int i = 0; i < 2; i++) 
		for (int j = 0; j < 3; j++) 
			for (int k = 0; k <= n; k++) 
				for (int l = 0; l <= n; l++)
					dp[i][j][k][l] = linf;
	dp[0][0][0][0] = 0;
	int cnt = s / v;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= cnt; j++) {
			for (int k = 0; k < 2; k++) {
				for (int last = 0; last < 3; last++) {
					dp[k][0][i + 1][j] = min(dp[k][0][i + 1][j], dp[k][last][i][j]);
					if (!k && val[2] > 0) {
						dp[1][2][i + 1][j] = min(dp[1][2][i + 1][j], dp[k][last][i][j] + a[i] * 1LL * val[2] * val[last]);
					}
					if (j <= cnt - 1)
						dp[k][1][i + 1][j + 1] = min(dp[k][1][i + 1][j + 1], dp[k][last][i][j] + a[i] * 1LL * val[1] * val[last]);
				}
			}
		}
	}
	ll ans = linf;
	for (int i = 0; i < 3; i++) {
		ans = min(ans, dp[bool(s % v)][i][n][cnt]);
	}
	cout << ans;
}
