/*
https://codeforces.com/gym/100091
*/
#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >
#define fr first
#define sc second
#define pb push_back

const int N = (int)5e5 + 7;

int n, m;
int pr[N];
vector < int > gr[N];
vector < int > d, ind, pos(N + N);

struct sparse {
	pii table[20][N];
	int numlog[N];
	sparse() {		
	}
	pii mmin(pii &a, pii &b) {
		if (a.fr != b.fr) {
			if (a.fr < b.fr) {
				return a;
			}
		}
		return b;
	}
	void build() {
		for (int i = 2; i < N; i++) {
			numlog[i] = numlog[i / 2] + 1;
		}
		int n = d.size();
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < n; j++) {
				if (!i) {
					table[i][j].fr = d[j];
					table[i][j].sc = ind[j];
				} else {
					table[i][j] = mmin(table[i - 1][j], table[i - 1][min(j + (1 << (i - 1)), n - 1)]);
				}
			}
		}
	}
	pii getmin(int l, int r) {
		int lg = numlog[r - l + 1];
		return mmin(table[lg][l], table[lg][r - (1 << lg) + 1]);
	}
};
sparse tr;

void dfs(int v, int h = 0) {
	d.pb(h);
	ind.pb(v);
	pos[ind.back()] = ind.size() - 1;
	for (int to : gr[v]) {
		dfs(to, h + 1);
		d.pb(h);
		ind.pb(v);
		pos[ind.back()] = ind.size() - 1;
	}
}

int a[(int)2e7 + 7];

int mult(int a, int b) {
	return (a * 1LL * b) % n;
}

main() {
	freopen("lca_rmq.in", "r", stdin); freopen("lca_rmq.out", "w", stdout);                
	scanf("%d %d", &n, &m);
	for (int i = 1; i < n; i++) {
		scanf("%d", &pr[i]);
		gr[pr[i]].pb(i);
	}
	dfs(0);
	tr.build();
	scanf("%d %d", &a[1], &a[2]);
	int x, y, z;
	scanf("%d %d %d", &x, &y, &z);
	for (int i = 3; i <= 2 * m; i++) {
		a[i] = (mult(a[i - 2], x) + mult(a[i - 1], y) + z) % n;
	}
	int ans = 0;
	int l, r;
	l = pos[a[1]];
	r = pos[a[2]];
	if (l > r) swap(l, r);
	ans = tr.getmin(l, r).sc;
	long long ans1 = 0;
	ans1 += ans;
	for (int i = 2; i <= m; i++) {
		a[i * 2 - 1] = (a[i * 2 - 1] + ans) % n;
		l = pos[a[i * 2 - 1]];
		r = pos[a[i * 2]];
		if (l > r) swap(l, r);
		ans = tr.getmin(l, r).sc;
		ans1 += ans;
	}
	cout << ans1;
}
