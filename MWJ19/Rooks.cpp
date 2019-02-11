#include <bits/stdc++.h>

#define ll long long
 
using namespace std;

int n, m;
int a[10][10];
ll dp[11][20000];
int musk[10];

bool check(int pos, int mask) {
	vector < int > vec;
	for (int i = 0; i < m; i++) {
		if ((mask >> i) & 1) {
			if ((musk[pos] >> i) & 1 ^ 1) return 0;
			vec.push_back(i);
		}
	}
	bool ok = 1;
	for (int i = 1; i < (int)vec.size(); i++) {
		bool res = 0;
		for (int j = vec[i - 1]; j <= vec[i]; j++) {
			res |= ((musk[pos] >> j) & 1 ^ 1);
		}
		ok &= res;
	}
	return ok;
}

int pw[11];

void precalc() {
	pw[0] = 1;
	for (int i = 1; i < 11; i++) {
		pw[i] = pw[i - 1] * 3;
	}
}

int retmask(int pos, int mask, int mask3) {
	int ret = 0;
	for (int i = 0; i < m; i++) {
		if ((musk[pos] >> i) & 1 ^ 1) {
			ret += pw[i];
			continue;
		} else {
			if ((mask3 / pw[i]) % 3 == 2 || ((mask >> i) & 1)) {
				ret += 2 * pw[i];
			} else {
				if ((mask3 / pw[i]) % 3 == 0) continue;
				int res = 0;
				for (int j = i; j < m; j++) {
					if ((musk[pos] >> j) & 1 ^ 1) break;
					if ((mask >> j) & 1) {
						res |= 1;
					}
				}
				for (int j = i; j >= 0; j--) {
					if ((musk[pos] >> j) & 1 ^ 1) break;
					if ((mask >> j) & 1) {
						res |= 1;
					}
				}
				ret += res * pw[i];
			}
		}
	}
	return ret;
}

main() {
	precalc();
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		getchar();
		for (int j = 0; j < m; j++) {
			a[i][j] = (getchar() == '.');
			musk[i] |= (a[i][j] << j);
		}
	}
	int asd = 0;
	for (int i = 0; i < m; i++) {
		asd *= 3;
		asd += 1;
	}
	for (int mask = 0; mask < (1 << m); mask++) {
		if (check(0, mask)) {
			dp[0][retmask(0, mask, asd)]++;
			int assd = retmask(0, mask, asd);
		}
	}
	for (int i = 0; i < n - 1; i++) {
		for (int mask = 0; mask < pw[m]; mask++) {
			int ok = dp[i][mask] > 0;
			for (int j = 0; j < m; j++) 
				if (((musk[i + 1] >> j) & 1 ^ 1) && mask / pw[j] % 3 == 0) 
					ok = 0;
			if (!ok) continue;
			for (int mask1 = 0; mask1 < (1 << m); mask1++) {
				if (!check(i + 1, mask1)) continue;
				ok = 1;
				for (int j = 0; j < m; j++) {
					if ((mask / pw[j]) % 3 == 2 && ((mask1 >> j) & 1))
						ok = 0;
				}
				if (!ok) continue;
				asd = retmask(i + 1, mask1, mask);
				// cout << mask << " -> " << asd << endl;
				dp[i + 1][asd] += dp[i][mask];
			}
		}
	}
	ll ans = 0;
	for (int mask = 0; mask < pw[m]; mask++) {
		bool ok = 1;
		for (int i = 0; i < m; i++) {
			if (mask / pw[i] % 3 == 0) ok = 0;
		}
		if (ok) {
			// cout << mask << ' ' << dp[n - 1][mask] << endl;
			ans += dp[n - 1][mask];
		}
	}
	cout << ans;
}
