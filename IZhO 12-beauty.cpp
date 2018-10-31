#include <stdio.h>
#include <algorithm>
 
using namespace std;
 
#define int long long
#define ll long long
 
int a[22];
int n;
// can these two elements i and j be neighbours?
int ok[22][22];
 
// return number of '1' in ternary representation
int get(int x) {
	int res = 0;
	while (x) {
		res += (x % 3 == 1);
		x /= 3;
	}
	return res;
}
 
// return number of '1' in binary representation
int get1(int x) {
	int res = 0;
	while (x) {
		res += (x % 2 == 1);
		x /= 2;
	}
	return res;
}
 
 /*
dp[mask][i] = mask shows which elements we took, it avoids to take element twice
              i shows which element we took last, it avoids to calc wrong permutation
*/
int dp[1 << 20][20];
 
main() {
	int n;
	scanf("%lld", &n);
	for (int i = 0; i < n; i++) {
		int x;
		scanf("%lld", &x);
		a[i] = x;
    // initially we can take an element i 
		dp[1 << i][i]++;
	}
  // precalc ok[i][j]
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ok[i][j] = (get(a[i]) == get(a[j]) || get1(a[i]) == get1(a[j]));
		}
	}
	for (int mask = 1; mask < (1 << n); mask++) {
		for (int j = 0; j < n; j++) {
      if ((mask >> j) & 1 ^ 1) continue;
      // we push value of dp[mask][j] to front
      // if element j is not taken, skip it
      // because we add to the dp[mask | (1 << k)][k] the value dp[mask][j]
      // we can't add dp[mask][j] if we didn't took it
			for (int k = 0; k < n; k++) {
				if (((mask >> k) & 1 ^ 1) && ok[j][k]) {
          // if we can take an element k after element j
          // we push value front
					dp[mask | (1 << k)][k] += dp[mask][j];
				}
			}
		}
	}
  // answer is sum of ( dp[2^n - 1][i] ): 0 <= i <= n - 1 
	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans += dp[(1 << n) - 1][i];
	}
	printf("%lld", ans);
}
