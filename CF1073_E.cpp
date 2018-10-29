#include <stdio.h>
#include <algorithm>
#include <memory.h>

using namespace std;

#define ll long long

ll l, r;
int k, len;
int mod = 998244353;
int dp1[20][1 << 10][2];
int dp2[20][1 << 10][2];
char u1[20][1 << 10][2];
char u2[20][1 << 10][2];
int bt[1 << 10], num[20], pw[20];

int add(int a, int b) {
	return (a + b) % mod;
}

int mult(int a, int b) {
	return (a * 1LL * b) % mod;
}

int calcdp1(int pos, int mask, int f) {
	if (pos >= len) return 1;
	if (u1[pos][mask][f]) return dp1[pos][mask][f];
	int &res = dp1[pos][mask][f];
	u1[pos][mask][f] = 1;
	if (f) {
		for (int i = (pos == 0); i <= num[pos]; i++) {
			if (bt[mask | (1 << i)] <= k)
				res = add(res, calcdp1(pos + 1, mask | (1 << i), (i == num[pos])));
		}
	} else {
		for (int i = 0; i < 10; i++) {
			if (bt[mask | (1 << i)] <= k)
				res = add(res, calcdp1(pos + 1, mask | (1 << i), 0));
		}
	}
	return res;
	
}
int calcdp2(int pos, int mask, int f) {
	if (pos >= len) return 0;
	if (u2[pos][mask][f]) return dp2[pos][mask][f];
	// printf("%d %d %d\n", pos, mask, f);
	int &res = dp2[pos][mask][f];
	res = 0;
	u2[pos][mask][f] = 1;
	if (f) {
		for (int i = (pos == 0); i <= num[pos]; i++) {
			if (bt[mask | (1 << i)] <= k) {
				res = add(res, mult(calcdp1(pos + 1, mask | (1 << i), (i == num[pos])), mult(pw[len - pos - 1], i)));
				res = add(res, calcdp2(pos + 1, mask | (1 << i), (i == num[pos])));
			}
		}
	} else {
		for (int i = 0; i < 10; i++) {
			if (bt[mask | (1 << i)] <= k) {
				res = add(res, mult(calcdp1(pos + 1, mask | (1 << i), 0), mult(pw[len - pos - 1], i)));
				res = add(res, calcdp2(pos + 1, mask | (1 << i), 0));
			}
		}
	}
	return res;
}

int binpow(int a, int n) {
	int res = 1;
	while (n) {
		if (n & 1)
			res = mult(res, a);
		a = mult(a, a);
		n >>= 1;
	}
	return res;
}


int solve(int x) {
	memset(dp1, 0, sizeof dp1);
	memset(dp2, 0, sizeof dp2);
	memset(u1, 0, sizeof u1);
	memset(u2, 0, sizeof u2);
	len = 0;
	while (x) {
		num[len] = x % 10;
		x /= 10;
		len++;
	}
	reverse(num, num + len);
	int res = calcdp2(0, 0, 1);
	res = add(res, mult(pw[len - 1], mult(add(pw[len - 1], mod - 1), binpow(2, mod - 2))));
	return res;
}

main() {
	for (int i = 0; i < (1 << 10); i++) {
		bt[i] = __builtin_popcount(i);
	}
	pw[0] = 1;
	for (int i = 1; i < 20; i++) {
		pw[i] = mult(pw[i - 1], 10);
	}
	scanf("%I64d %I64d %d", &l, &r, &k);
	printf("%d\n", add(solve(r), mod - solve(l - 1)));
}
