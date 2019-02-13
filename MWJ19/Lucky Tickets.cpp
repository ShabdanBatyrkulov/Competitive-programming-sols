#include <bits/stdc++.h>

#define ll long long

using namespace std;

int n;
int can[10];
vector < int > vec;
string s;
// dp[pos][2][3][5][7]
ll dp[10][40][30][20][20];

void make(int x, int &A, int &B, int &C, int &D) {
	while (x % 2 == 0) {
		x /= 2;
		A++;
	}
	while (x % 3 == 0) {
		x /= 3;
		B++;
	}
	while (x % 5 == 0) {
		x /= 5;
		C++;
	}
	while (x % 7 == 0) {
		x /= 7;
		D++;
	}
}

ll sqr(ll x) {
	return x * x;
}

ll binpow(ll a, int n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * a;
		}
		a = a * a;
		n >>= 1;
	}
	return res;
}

ll fact[12];

ll cnk(int n, int k) {
	return fact[n] / fact[k] / fact[n - k];
}

main() {
	cin >> n;
	cin >> s;
	for (int i = 0; i < s.size(); i++) {
		can[s[i] - '0'] = 1;
		vec.push_back(s[i] - '0');
	}
	ll ans = 0;
	dp[0][0][0][0][0] = 1;
	for (int pos = 0; pos < n; pos++) {
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 20; j++) {
				for (int k = 0; k < 10; k++) {
					for (int l = 0; l < 10; l++) {
						for (int to : vec) {
							if (to == 0) continue;
							int a, b, c, d;
							a = b = c = d = 0;
							make(to, a, b, c, d);
							dp[pos + 1][i + a][j + b][k + c][l + d] += dp[pos][i][j][k][l];
						}
					}
				}
			}
		}
	}
	vector < int > v;
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 20; j++) {
			for (int k = 0; k < 10; k++) {
				for (int l = 0; l < 10; l++) {
					ans += sqr(dp[n][i][j][k][l]);
				}
			}
		}
	}
	fact[0] = 1;
	for (int i = 1; i < 12; i++) {
		fact[i] = fact[i - 1] * i;
	}
	if (can[0]) {
		ll res = 0;
		for (int i = 1; i <= n; i++) {
			res += binpow(vec.size() - 1, n - i) * cnk(n, i);
		}
		ans += sqr(res);
	}
	cout << ans;
}
