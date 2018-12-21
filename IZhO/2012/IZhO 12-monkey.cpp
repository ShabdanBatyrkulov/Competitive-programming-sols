#include <bits/stdc++.h>

using namespace std;

#define ok puts("ok");
#define ll long long

const int inf = (int)1e9;

struct T {
	int val, add, l, r;
	T() {
		val = add = l = r = 0;
	}
};
T tree[(int)5e6];
int siz = 1;

void push(int v, int l, int r) {
	if (tree[v].add && v) {
		if (l != r) {
			tree[tree[v].l].add = tree[v].add;
			tree[tree[v].r].add = tree[v].add;
		}
		tree[v].val = (r - l + 1);
	}
}

void upd(int v, int l, int r, int tl, int tr) {
	//cout << v << ' ' << tl << ' ' << tr << endl;
	push(v, tl, tr);
	if (tl > r || tr < l) return ;
	if (l <= tl && tr <= r) {
		tree[v].add = 1;
		push(v, tl, tr);
		return ;
	}
	if (!tree[v].l) {
		tree[v].l = ++siz;
	}
	if (!tree[v].r) {
		tree[v].r = ++siz;
	}
	push(v, tl, tr);
	int mid = (tl + tr) >> 1;
	upd(tree[v].l, l, r, tl, mid);
	upd(tree[v].r, l, r, mid + 1, tr);
	tree[v].val = tree[tree[v].l].val + tree[tree[v].r].val;
	//cout << v << ' ' << tl << ' ' << tr << ' ' << tree[v].val << ' ' << tree[tree[v].l].val << ' ' << tree[tree[v].r].val << endl;
}

int get(int v, int l, int r, int tl, int tr) {
	if (tl > r || tr < l) return 0;
	push(v, tl, tr);
	if (l <= tl && tr <= r) return tree[v].val;
	int mid = (tl + tr) >> 1;
	if (!tree[v].l) {
		tree[v].l = ++siz;
	}
	if (!tree[v].r) {
		tree[v].r = ++siz;
	}
	push(v, tl, tr);
	return get(tree[v].l, l, r, tl, mid) + get(tree[v].r, l, r, mid + 1, tr);
}

main () {
	freopen("f.in", "r", stdin);
	freopen("f.out", "w", stdout);
  int m; scanf("%d", &m);
  int c = 0;
  while (m--) {
    int tp; scanf("%d", &tp);
    int l, r; scanf("%d %d", &l, &r);
    l += c;
    r += c;
    if (tp == 1) {
      c = get(1, l, r, 1, inf);
      printf("%d\n", c);
    } else {
      upd(1, l, r, 1, inf);
    }
  }
}
