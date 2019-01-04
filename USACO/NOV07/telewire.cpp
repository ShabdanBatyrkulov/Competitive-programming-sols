#include <bits/stdc++.h>
 
using namespace std;

#define ll long long

const int N = (int)1e5 + 7;
const ll inf = (ll)1e18 + 7;

int n;
int h[N];
ll dp[2][101];
ll c;

ll sqr(ll x) {
	return x * x;
}

main() {
	freopen("telewire.in", "r", stdin);
	freopen("telewire.out", "w", stdout);
	scanf("%d %lld", &n, &c);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &h[i]);
	}
	for (int i = 1; i <= 100; i++) {
		dp[1][i] = (i < h[1]) ? inf : sqr(i - h[1]);
	}
	int cur, prv;
	for (int i = 2; i <= n; i++) {
		cur = i & 1;
		prv = cur ^ 1;
		ll asd = inf;
		for (int j = 1; j <= 100; j++) {
			asd = (asd > dp[prv][j] - j * c) ? dp[prv][j] - j * c : asd;
			dp[cur][j] = asd + j * c;
		}
		asd = inf;
		for (int j = 100; j >= 1; j--) {
			asd = (asd > dp[prv][j] + j * c) ? dp[prv][j] + j * c : asd;
			dp[cur][j] = min(dp[cur][j], asd - j * c);
		}
		for (int j = 1; j <= 100; j++) {
			dp[cur][j] = (j < h[i]) ? inf : (dp[cur][j] + sqr(h[i] - j));
		}
	}
	ll ans = inf;
	for (int i = 1; i <= 100; i++) {
		ans = min(ans, dp[n & 1][i]);
	}
	cout << ans;
}
