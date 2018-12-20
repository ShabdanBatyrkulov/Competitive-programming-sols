#include <bits/stdc++.h>
  
using namespace std;

const int N = (int)8e5 + 7;
const int inf = (int)1e9 + 7;

int a[N];
int n, m;
vector < int > ans;
int pos[N], pr[N], used[N], col[N];

struct T {
	int tree[N * 4];
	int tre1[N * 4];
	T() {
		for (int i = 0; i < N * 4; i++) {
			tree[i] = 0;
			tre1[i] = inf;
		}
	}
	void clear() {
		for (int i = 0; i < N * 4; i++) {
			tree[i] = 0;
			tre1[i] = inf;
		}
	}
	void upd(int pos, int val, int v = 1, int l = 1, int r = n) {
		if (l == r) {
			if (val == -1) {
				tree[v] = 0;
				tre1[v] = inf;
			} else {
				tree[v] = val;
				tre1[v] = val;
			}
			return ;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			upd(pos, val, v + v, l, mid);
		} else {
			upd(pos, val, v + v + 1, mid + 1, r);
		}
		tree[v] = max(tree[v + v], tree[v + v + 1]);
		tre1[v] = min(tre1[v + v], tre1[v + v + 1]);
	}
	int getmax(int r, int pos, int v = 1, int tl = 1, int tr = n) {
		if (tl > r || tre1[v] > pos) return 0;
		if (tl == tr) return tl;
		int mid = (tl + tr) >> 1;
		int res = 0;
		if (tre1[v + v + 1] <= pos) {
			res = getmax(r, pos, v + v + 1, mid + 1, tr);
		}
		if (res) return res;
		return getmax(r, pos, v + v, tl, mid);
	}
	int getmin(int l, int pos, int v = 1, int tl = 1, int tr = n) {
		if (tr < l || tree[v] < pos) return inf;
		if (tl == tr) return tl;
		int mid = (tl + tr) >> 1;
		int res = 0;
		if (tree[v + v] >= pos) {
			res = getmin(l, pos, v + v, tl, mid);
		}
		if (res) return res;
		return getmin(l, pos, v + v + 1, mid + 1, tr);
	}
};
T tr;

void makeSDS(vector < int > &vec, vector < int > &v1) {
	vector < int > d;
	d.resize(vec.size() + 1, inf);
	d[0] = -inf;
	int mx = 0;
	for (int i = 0; i < vec.size(); i++) {
		int x = vec[i];
		x *= -1;
		int pos = lower_bound(d.begin(), d.end(), x) - d.begin();
		d[pos] = x;
		if (pos > mx) {
			mx = pos;
		}
		x *= -1;
		pr[x] = d[pos - 1];
	}
	mx = d[mx];
	while (mx > -inf) {
		mx *= -1;
		v1.push_back(mx);
		mx = pr[mx];
	}
	reverse(v1.begin(), v1.end());
}

main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d %d", &n, &m);
	vector < int > vec;
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		vec.push_back(x);
		a[i] = x;
		pos[x] = i;
	}
	vector < int > v;
	makeSDS(vec, v);
	assert(v.size() <= m);
	int cnt = 0;
	for (int i = 0; i < v.size(); i++) {
		used[pos[v[i]]] = 2;
		col[v[i]] = ++cnt;
	}
	for (int i = 1; i <= n; i++) {
		if (used[i] == 2) {
			bool ok = 1;
			int prv = a[i];
			while (ok) {
				ok = 0;
				int gg = tr.getmax(prv - 1, pos[prv] - 1);
				if (gg) {
					used[pos[gg]] = 1;
					col[gg] = col[prv];
					tr.upd(gg, -1);
					prv = gg;
					ok = 1;
				}
			}
		}
		if (!used[i]) {
			tr.upd(a[i], i);
		}
	}
	tr.clear();
	for (int i = n; i >= 1; i--) {
		if (used[i] == 2) {
			bool ok = 1;
			int prv = a[i];
			while (ok) {
				ok = 0;
				int gg = tr.getmin(prv + 1, pos[prv] + 1);
				if (gg <= n) {
					used[pos[gg]] = 1;
					col[gg] = col[prv];
					tr.upd(gg, -1);
					prv = gg;
					ok = 1;
				}
			}
		} 
		if (!used[i]) {
			tr.upd(a[i], i);
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%d ", col[a[i]]);
	}
	puts("");
	for (int i = 1; i <= n; i++) {
		printf("%d ", col[i]);
	}
}
