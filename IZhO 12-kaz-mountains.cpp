#include <bits/stdc++.h>

using namespace std;

#define ok puts("ok");
#define ll long long

const int N = (int)1e6 + 7;

int n, k;
int a[N];
ll od, nw;

struct Data {
	int l, r, len, val;
	Data() {
		l = r = len = val = 0;
	}
	Data(int _l, int _r, int _len, int _val) {
		l = _l;
		r = _r;
		len = _len;
		val = _val;
	}
	bool operator < (const Data& o) const {
		if (len == o.len) return l < o.l;
		return len < o.len;
	}
	bool operator == (const Data& o) const {
		return l == o.l;
	}
};

struct DSU {
	int pr[N];
	Data dt[N];
	int sz[N];
	DSU() {
		iota(pr, pr + N, 0);
		for (int i = 0; i < N; i++) {
			sz[i] = 1;
		}
	}
	int getpar(int a) {
		return (pr[a] == a) ? a : pr[a] = getpar(pr[a]);
	}
	void connect(int a, int b) {
		a = getpar(a);
		b = getpar(b);
		if (a != b) {
			pr[a] = b;
			sz[b] += sz[a];
			dt[b].val = max(dt[b].val, dt[a].val);
			dt[b].len += dt[a].len;
			if (dt[b].l == dt[a].r + 1) {
				dt[b].l = dt[a].l;
			} else if (dt[b].r == dt[a].l - 1) {
				dt[b].r = dt[a].r;
			} else {
				if (dt[b].l == 1 && dt[a].r == n) {
					dt[b].l = dt[a].l;
				} else if (dt[b].r == n && dt[a].l == 1) {
					dt[b].r = dt[a].r;
				} else {
					assert(false);
				}
			}
		}
	}
};
DSU dsu;

main () {
	freopen("g.in", "r", stdin);
	freopen("g.out", "w", stdout);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		assert(a[i] <= (int)1e9);
	}
	a[0] = a[n];
	a[n + 1] = a[1];
	multiset < Data > s;
	for (int i = 1; i <= n; i++) {
		od += abs(a[i] - a[i - 1]);
		dsu.dt[i].len = 1;
		dsu.dt[i].l = dsu.dt[i].r = i;
		dsu.dt[i].val = a[i];
		ll mn = min(a[i - 1], a[i + 1]);
		if (a[i] <= mn) {
			s.insert(dsu.dt[i]);
		}
	}
	// code goes here
	while (!s.empty() && dsu.dt[dsu.getpar(1)].len < n) {
		auto v = *s.begin();
		s.erase(s.begin());
		if (k < v.len) {
			break;
		}
		auto left = Data();
		auto right = Data();
		if (v.l == 1) {
			left = dsu.dt[dsu.getpar(n)];
		} else {
			left = dsu.dt[dsu.getpar(v.l - 1)];
		}
		if (v.r == n) {
			right = dsu.dt[dsu.getpar(1)];
		} else {
			right = dsu.dt[dsu.getpar(v.r + 1)];
		}
		//{
			//puts("current");
			//cout << v.l << ' ' << v.r << ' ' << v.val << ' ' << v.len << '\n';
			//puts("left");
			//cout << left.l << ' ' << left.r << ' ' << left.val << ' ' << left.len << '\n';
			//puts("right");
			//cout << right.l << ' ' << right.r << ' ' << right.val << ' ' << right.len << '\n';
		//}
		ll mn = min(left.val, right.val);
		if (v.val < mn) {
			if ((mn - v.val) * 1LL * v.len <= k) {
				k -= ((mn - v.val) * 1LL * v.len);
				v.val = mn;
			} else {
				ll res = k / v.len;
				v.val += res;
				k %= v.len;
				dsu.dt[dsu.getpar(v.l)].val += res;
				break;
			}
		} else if (v.val == mn) {
			if (v.val == left.val) 
				s.erase(left);
			if (v.val == right.val)
				s.erase(right);
		}
		if (v.val == left.val) {
			dsu.connect(v.l, left.r);
		}
		if (v.val == right.val) {
			dsu.connect(v.r, right.l);
		}
		v = dsu.dt[dsu.getpar(v.l)];
		if (v.l == 1) {
			left = dsu.dt[dsu.getpar(n)];
		} else {
			left = dsu.dt[dsu.getpar(v.l - 1)];
		}
		if (v.r == n) {
			right = dsu.dt[dsu.getpar(1)];
		} else {
			right = dsu.dt[dsu.getpar(v.r + 1)];
		}
		mn = min(left.val, right.val);
		if (v.val <= mn)
			s.insert(dsu.dt[dsu.getpar(v.l)]);
	}
	
	for (int i = 1; i <= n; i++) {
		a[i] = dsu.dt[dsu.getpar(i)].val;
		//cout << a[i] << ' ';
	}
	//cout << endl;
	
	// finish
	a[0] = a[n];
	for (int i = 1; i <= n; i++) {
		nw += abs(a[i] - a[i - 1]);
	}
	printf("%lld\n", od - nw);
}
/*
8 3
2 3 4 4 4 4 2 2

7 1000000000
5 4 3 4 5 4 6

8 7
8 3 1 1 1 3 8 1

I will put to the set only segments which are surrounded by bigger elements 
a[i] <= min(a[i - 1], a[i + 1]);
Take smallest segment
merge with neighboring segments and check
*/
