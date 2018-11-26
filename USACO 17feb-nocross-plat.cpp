#include <iostream>
#include <bitset>
#include <algorithm>
#include <memory.h>
#include <utility>
#include <vector>
#include <cmath>
#include <math.h>
#include <time.h>
#include <assert.h>

#define ll long long

/*
dynamic programming on second array,
segment tree optimization
*/

using namespace std;

const int N = (int)1e5 + 7;

int a[N];
int n;

struct T {
	int tree[4 * N];
	T() {
		memset(tree, 0, sizeof tree);
	}
	void upd(int pos, int val, int v = 1, int tl = 1, int tr = n) {
		if (tl == tr) {
			tree[v] = val;
			return ;
		}
		int mid = (tl + tr) >> 1;
		if (pos <= mid)
			upd(pos, val, v + v, tl, mid);
		else
			upd(pos, val, v + v + 1, mid + 1, tr);
		tree[v] = max(tree[v + v], tree[v + v + 1]);
	}
	int get(int l, int r, int v = 1, int tl = 1, int tr = n) {
		if (tl > r || tr < l) return 0;
		if (l <= tl && tr <= r) return tree[v];
		int mid = (tl + tr) >> 1;
		return max(get(l, r, v + v, tl, mid), get(l, r, v + v + 1, mid + 1, tr));
	}
};
T tr;

int pos[N];

main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	freopen("nocross.in", "r", stdin);
	freopen("nocross.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		pos[x] = i;
	}
	for (int i = 1; i <= n; i++) {
		vector < int > vec;
		for (int j = max(1, a[i] - 4); j <= min(n, a[i] + 4); j++) {
			vec.push_back(pos[j]);
		  // positions of elements from second array which we can tie with position 'i' in first array
    }
		sort(vec.begin(), vec.end());
		for (int j = vec.size() - 1; j >= 0; j--) {
      // they don't have to intersect so I take maximum from (1 ... vec[j] - 1), add 1 and update position vec[j]; 
			tr.upd(vec[j], tr.get(1, vec[j] - 1) + 1);
		}
	}
	cout << tr.get(1, n);
}	

