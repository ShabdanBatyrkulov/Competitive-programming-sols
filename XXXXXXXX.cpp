/*
Offline
https://www.spoj.com/problems/XXXXXXXX/
*/

#include <bits/stdc++.h>
  
using namespace std;

#define ll long long
#define int long long

const int N = (int)2e6 + 7;

struct Q {
	int tp, x, y, val, id, pos;
	Q() {}
	Q(int _tp, int _x, int _y, int _val, int _id, int _pos) {
		tp = _tp;
		x = _x;
		y = _y;
		val = _val;
		id = _id;
		pos = _pos;
	}
};

struct fen {
	ll tree[N];
	fen() {
		memset(tree, 0, sizeof tree);
	}
	void upd(int pos, int val) {
		while (pos < N) {
			tree[pos] += val;
			pos = pos | (pos + 1);
		}
	}
	ll get(int r) {
		ll res = 0;
		while (r >= 0) {
			res += tree[r];
			r = (r & (r + 1)) - 1;
		}
		return res;
	}
};
fen tr;

int a[N];
int n, tot, cnt;
vector < Q > q, q1;
int restore[N];
set < int > s[N];
ll ans[N];
vector < pair < char, pair < int, int > > > q2;

void make(int l, int r) {
	if (l >= r) return ;
	int mid = (l + r) >> 1;
	for (int i = l; i <= r; i++) {
		if (q[i].tp == 0 && q[i].pos <= mid) {
			tr.upd(q[i].y, q[i].val);
		} else if (q[i].tp == 1 && q[i].pos > mid) {
			ans[q[i].id] += q[i].val * tr.get(q[i].y);
		}
	}
	for (int i = l; i <= r; i++) {
		if (q[i].tp == 0 && q[i].pos <= mid) {
			tr.upd(q[i].y, -q[i].val);
		}
	}
	int l1, l2;
	l1 = l;
	l2 = mid + 1;
	for (int i = l; i <= r; i++) {
		if (q[i].pos <= mid) {
			q1[l1++] = q[i];
		} else {
			q1[l2++] = q[i];
		}
	}
	for (int i = l; i <= r; i++) {
		q[i] = q1[i];
	}
	make(l, mid);
	make(mid + 1, r);
}

main() {
	vector < int > vec;
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		vec.push_back(a[i]);
	}
	int qq;
	scanf("%lld", &qq);
	int lst;
	while (qq--) {
		char c;
		c = getchar();
		if (c == '\n') c = getchar();
		int l, r;
		scanf("%lld %lld", &l, &r);
		if (c == 'U')
			vec.push_back(r);
		q2.push_back({c, {l, r}});
	}
	sort(vec.begin(), vec.end());
	vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
	for (int i = 1; i <= n; i++) {
		int old = a[i];
		a[i] = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin();
		restore[a[i]] = old;
		s[a[i]].insert(i);
	}
	for (int i = 0; i < q2.size(); i++) {
		if (q2[i].first == 'Q') continue;
		int old = q2[i].second.second;
		q2[i].second.second = lower_bound(vec.begin(), vec.end(), q2[i].second.second) - vec.begin();
		restore[q2[i].second.second] = old;
	}
	for (int i = 1; i <= n; i++) {
		auto it = s[a[i]].lower_bound(i);
		lst = 0;
		if (it != s[a[i]].begin()) lst = *(--it);
		q.push_back(Q(0, i, lst, restore[a[i]], 0, cnt++));
	}
	for (int i = 0; i < q2.size(); i++) {
		char c = q2[i].first;
		int l, r;
		l = q2[i].second.first;
		r = q2[i].second.second;
		if (c == 'U') {
			auto it = s[a[l]].lower_bound(l);
			it++;
			if (it != s[a[l]].end()) {
				lst = *it;
				q.push_back(Q(0, lst, l, -restore[a[l]], 0, cnt++));
				int prv = 0;
				it--;
				if (it != s[a[l]].begin()) prv = *(--it);
				q.push_back(Q(0, lst, prv, restore[a[l]], 0, cnt++));
				if (prv != 0) it++;
			} else {
				it--;
			}
			lst = 0;
			if (it != s[a[l]].begin()) lst = *(--it);
			//cout << l << ' ' << lst << ' ' << a[l] << endl;
			q.push_back(Q(0, l, lst, -restore[a[l]], 0, cnt++));
			s[a[l]].erase(l);
			a[l] = r;
			
			it = s[a[l]].lower_bound(l);
			if (it != s[a[l]].end()) {
				int prv = 0;
				if (it != s[a[l]].begin()) prv = *(--it);
				if (prv != 0) {
					it++;
				} 
				q.push_back(Q(0, *it, prv, -restore[a[l]], 0, cnt++));
				q.push_back(Q(0, *it, l, restore[a[l]], 0, cnt++));
			}
			
			s[a[l]].insert(l);
			it = s[a[l]].lower_bound(l);
			lst = 0;
			if (it != s[a[l]].begin()) lst = *(--it);
			q.push_back(Q(0, l, lst, restore[a[l]], 0, cnt++));
		} else {
			q.push_back(Q(1, r, l - 1, 1, ++tot, cnt++));
			q.push_back(Q(1, l - 1, l - 1, -1, tot, cnt++));
		}
	}
	sort(q.begin(), q.end(), [](Q A, Q B) {
		if (A.x != B.x)
			return A.x < B.x;
		return A.pos < B.pos;
	});
	q1.resize(q.size());
	make(0, q.size() - 1);
	for (int i = 1; i <= tot; i++) {
		printf("%lld\n", ans[i]);
	}
}
/*
5
1 2 3 4 5
7
Q 1 5
U 3 2
Q 1 4
U 1 2
Q 1 4
Q 1 3
Q 3 5
*/
