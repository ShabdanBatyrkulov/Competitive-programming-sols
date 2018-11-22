#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = (int)50000 + 7;

int m, k;
ll r;
string s;
ll dp[12][5][N];

int turn(char c) {
	if (c == 'A') return 1;
	if (c == 'C') return 2;
	if (c == 'G') return 3;
	return 4;
}

char turn(int c) {
	if (c == 1) return 'A';
	if (c == 2) return 'C';
	if (c == 3) return 'G';
	return 'T';
}

ll calc(int form, int ch, int pos) {
	if (form == 0) return 0;
	if (pos == m) {
		return 1;
	}
	ll &res = dp[form][ch][pos];
	if (res != -1) return res;
	res = 0;
	for (int i = 1; i <= 4; i++) {
		if (s[pos] != 'N' && s[pos] != turn(i)) 
			continue;
		int newform = form;
		if (ch > i)
			newform--;
		res += calc(newform, i, pos + 1);
	}
	return res;
}

main() {
	memset(dp, -1, sizeof dp);
	scanf("%d %d %lld", &m, &k, &r);
	cin >> s;
	int form = k;
	int last = 1;
	for (int i = 0; i < m; i++) {
		if (s[i] == 'N') {
			for (int j = 1; j <= 4; j++) {
				int newform = form;
				if (j < last) 
					newform--;
				//cout << newform << ' ' << turn(j) << ' '<< i << ' ' << calc(newform, j, i + 1) << '\n';
				if (calc(newform, j, i + 1) < r) {
					r -= calc(newform, j, i + 1);
				} else {
					s[i] = turn(j);
					break;
				}
			}
		}
		if (s[i] < turn(last)) 
			form--;
		last = turn(s[i]);
	}	
	cout << s;
}
