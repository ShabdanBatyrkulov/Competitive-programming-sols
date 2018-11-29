#include <bits/stdc++.h>

#define ll long long

/*
Editorial in Russian
http://dl.gsu.by/NForum/posts/topicshow/817.dl#last
*/

using namespace std;

const int N = (int)307;
const int inf = (int)1e9 + 7;

int dp[N][N][2];
int n, m, pos;
int X[N];

main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	memset(dp, 63, sizeof dp);
	cin >> n >> m;
	int add = 0;
	for (int i = 1; i <= n; i++) {
		cin >> X[i];
	}
	sort(X + 1, X + n + 1);
	int ans = 0;
	for (int k = 1; k <= n; k++) {
		for (int len = 1; len < k; len++) {
			for (int i = 1; i + len - 1 <= n; i++) {
				if (len == 1) {
					dp[i][i][0] = dp[i][i][1] = k * abs(X[i]);
				}
				if (i > 1) {
					dp[i - 1][i + len - 1][0] = min(dp[i - 1][i + len - 1][0], dp[i][i + len - 1][0] + (k - len) * abs(X[i - 1] - X[i]));
					dp[i - 1][i + len - 1][0] = min(dp[i - 1][i + len - 1][0], dp[i][i + len - 1][1] + (k - len) * abs(X[i - 1] - X[i + len - 1]));
				}
				if (i + len <= n) {
					dp[i][i + len][1] = min(dp[i][i + len][1], dp[i][i + len - 1][0] + (k - len) * abs(X[i] - X[i + len]));
					dp[i][i + len][1] = min(dp[i][i + len][1], dp[i][i + len - 1][1] + (k - len) * abs(X[i + len - 1] - X[i + len]));
				}
			}
		}
		for (int i = 1; i + k - 1 <= n; i++) {
			ans = max(ans, max(k * m - dp[i][i + k - 1][0], k * m - dp[i][i + k - 1][1]));
		}
		for (int i = 1; i <= n; i++) {
			for (int j = i; j <= n; j++) {
				dp[i][j][0] = dp[i][j][1] = dp[N - 1][N - 1][0];
			}
		}
	}
	cout << ans;
}
