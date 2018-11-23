#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = (int)107;
const int inf = (int)2e9 + 7;

int n, k;
int w[N], pr[N], d[N];
vector < int > gr[N];
int last[N], prv[N];
int F[N][N][N], G[N][N][N];

int f(int, int, int, int);
int g(int, int, int, int);

int g(int v, int k, int lst, int dist) {
	if (v < 0) return 0;
	int &val = G[v][k][lst];
	if (val != -1) return val;
	if (prv[v] == -1) {
		val = f(v, k, lst, dist);
		return val;
	}
	val = inf;
	for (int j = 0; j <= k; j++) {
		val = min(val, g(prv[v], k - j, lst, dist) + f(v, j, lst, dist));
	}
	return val;
}

int f(int v, int k, int lst, int dist) {
	int &val = F[v][k][lst];
	if (val != -1) return val;
	dist += d[v];
	
	val = (k ? min(g(last[v], k, lst, dist) + dist * w[v], g(last[v], k - 1, v, 0)) : g(last[v], k, lst, dist) + dist * w[v]);
	
	return val;
}

void dfs(int v) {
	int lst = -1;
	for (int i = 0; i < gr[v].size(); i++) {
		int to = gr[v][i];
		prv[to] = lst;
		lst = to;
		dfs(to);
	}
	last[v] = lst;
}

main () {
	memset(F, -1, sizeof F);
	memset(G, -1, sizeof G);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d", w + i, pr + i, d + i);
		gr[pr[i]].push_back(i);
	}
	dfs(0);
	cout << f(0, k, 0, 0);
}
