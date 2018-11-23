#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = (int)50000 + 7;

int m, k;
ll r;
string s;
ll dp[12][5][N];
/*
dp[i][j][k] = means that how many ways to get a i-form string in which last symbol is j(1 == 'A', 2 == 'C' etc.), up to position k.
we can suppose that the k-form is k disjoint segments which cover whole string, and new segment starts when s[i - 1] > s[i]
*/

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
	/*
	transitions
	*/
	for (int i = 1; i <= 4; i++) {
		if (s[pos] != 'N' && s[pos] != turn(i)) 
			continue;
		int newform = form;
		/*
		when ch > i it means starting of new segment
		*/
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
				/* 
				if dp[newform][j][i + 1] < r means that the number of strings in which we put a symbol j to the position i i, 
				is less than we need, so it forces us to skip this symbol because out solution is not in this variants.
				*/
				if (calc(newform, j, i + 1) < r) {
					r -= calc(newform, j, i + 1);
				} else {
				/*
				but if we put symbol j, and the number of string is bigger, we should put that symbol there, and continue
				search next symbol
				*/
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
