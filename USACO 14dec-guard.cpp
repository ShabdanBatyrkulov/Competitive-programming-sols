#include <stdio.h>
#include <memory.h>
#include <vector>

using namespace std;

#define ll long long
#define int long long

const int inf = (int)1e9 + 7;

int dp[1 << 20];
ll sum[1 << 20], sum1[1 << 20];
int n, h;
int a[20], b[20], c[20];

main() {
	freopen("guard.in", "r", stdin);
	freopen("guard.out", "w", stdout);
	scanf("%lld %lld", &n, &h);
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld %lld", &a[i], &b[i], &c[i]);
	}
	for (int i = 1; i < (1 << n); i++) {
		for (int j = 0; j < n; j++) 
			if ((i >> j) & 1) {
				sum[i] += b[j];
				sum1[i] += a[j];
			}
		dp[i] = -1;
	}
	dp[0] = inf;
	for (int mask = 0; mask < (1 << n); mask++) {
		for (int j = 0; j < n; j++) {
			if (((mask >> j) & 1) == 0 && sum[mask] <= c[j] && dp[mask] != -1) {
				dp[mask | (1 << j)] = max(dp[mask | (1 << j)], min(dp[mask], (int)(c[j] - sum[mask])));
			}
		}
	}
	int ans = -1;
	for (int mask = 0; mask < (1 << n); mask++) {
		if (sum1[mask] >= h && dp[mask] != -1) {
			ans = max(ans, dp[mask]);
			// printf("%d %d\n", mask, dp[mask]);
		}
	}
	if (ans == -1) {
		puts("Mark is too tall");
		return 0;
	}
	printf("%lld", ans);
}
