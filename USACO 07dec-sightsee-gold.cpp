#include <bits/stdc++.h>
 
using namespace std;

#define ll long long

const int N = (int)1e3 + 7;
const double inf = (ll)1e18 + 7;

struct edge {
	int a, b, c;
};

int n, m;
int f[N];
vector < edge > vec;

bool check(double x) {
	vector < double > d(n + 1);
	int X;
	for (int i = 1; i <= n; i++) {
		X = -1;
		for (int j = 0; j < vec.size(); j++) {
			int v, to;
			double cost;
			v = vec[j].a;
			to = vec[j].b;
			cost = vec[j].c;
			cost = -f[v] + x * cost;
			if (d[to] > d[v] + cost) {
				d[to] = max(-inf, d[v] + cost);
				X = to;
			}
		}
	}
	return X != -1;
}

main() {
	freopen("sightsee.in", "r", stdin);
	freopen("sightsee.out", "w", stdout);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &f[i]);
		//f[i] *= 100;
	}
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		vec.push_back({u, v, w});
	}
	double l = 0;
	double r = 1e6;
	while (r - l > 0.00001) {
		double mid = (l + r) / 2;
		if (check(mid)) {
			l = mid;
		} else {
			r = mid;
		}
	}
	cout << fixed << setprecision(2) << r;
}
