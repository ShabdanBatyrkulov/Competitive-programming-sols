#include <bits/stdc++.h>
  
using namespace std;

const int N = (int)250000 + 7;
const int inf = (int)1e9 + 7;

int n, X;
int pref[N], a[N];

struct st {
	int to[2], pr, val;
	st() {
		to[0] = to[1] = 0;
		pr = 0;
		val = inf;
	}
};
st bor[N * 60];
int siz = 1;

void add(int x, int pos) {
	int v = 1;
	for (int i = 30; i >= 0; i--) {
		if (!bor[v].to[(x >> i) & 1]) {
			bor[v].to[(x >> i) & 1] = ++siz;
			bor[bor[v].to[(x >> i) & 1]].pr = v;
		}
		v = bor[v].to[(x >> i) & 1];
	}
	bor[v].val = min(pos, bor[v].val);
	v = bor[v].pr;
	while (v > 0) {
		int res = inf;
		if (bor[v].to[0]) {
			res = min(res, bor[bor[v].to[0]].val);
		}
		if (bor[v].to[1]) {
			res = min(res, bor[bor[v].to[1]].val);
		}
		bor[v].val = min(bor[v].val, res);
		v = bor[v].pr;
	}
}

int get(int x) {
	int res = inf;
	int v = 1;
	for (int i = 30; i >= 0 && v > 0; i--) {
		int tto = (x >> i) & 1;
		if ((X >> i) & 1 ^ 1) {
			if (bor[v].to[tto ^ 1]) {
				res = min(res, bor[bor[v].to[tto ^ 1]].val);
			}
			v = bor[v].to[tto];
		} else {
			if (tto)
				v = bor[v].to[0];
			else 
				v = bor[v].to[1];
		}
	}
	res = min(res, bor[v].val);
	return res;
}

main() {
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
	scanf("%d %d", &n, &X);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		pref[i] = pref[i - 1] ^ a[i];
	}
	pair < int, int > ans;
	ans = {0, 0};
	add(0, 0);
	for (int i = 1; i <= n; i++) {
		int asd = get(pref[i]);
		//cout << asd << ' ' << endl;
		int len = i - asd;
		if (len > ans.second) {
			ans.second = len;
			ans.first = i - len + 1;
		}
		add(pref[i], i);
	}
	printf("%d %d\n", ans.first, ans.second);
	
}
