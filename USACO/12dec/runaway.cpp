#include <bits/stdc++.h>

#define ll long long

/*
binary lifting with sum and prefix sum
we can imagine this problem as "we have segments and queries, query is such that they give you point 
	and you must find a number of how many segments lay in this point"
if we have some left and right.
I put to pref[r + 1] = -1, pref[l] = 1;(it is well known problem)
and our answer is sum of (i = 1...x(x is our point)) pref[i];
in this problem I do the same
*/

using namespace std;

const int N = (int)2e5 + 7;

ll l;
int n;
int lc[18][N], pr[N];
ll lcsum[18][N], d[N];
vector < int > gr[N];
int pref[N];

void dfs(int v) {
	for (int i = 1; i <= 17; i++) {
		lc[i][v] = lc[i - 1][lc[i - 1][v]];
		lcsum[i][v] = lcsum[i - 1][v] + lcsum[i - 1][lc[i - 1][v]];
	}
	int cur = v;
	ll sum = 0;
	for (int i = 17; i >= 0; i--) {
		if (sum + lcsum[i][cur] <= l) {
			sum += lcsum[i][cur];
			cur = lc[i][cur];
		}
	}
	//cout << v << ' ' << cur << endl;
	cur = lc[0][cur];
	pref[cur]--;
	pref[v]++;
	for (int to : gr[v]) {
		dfs(to);
	}
}

void dfs1(int v) {
	for (int to : gr[v]) {
		dfs1(to);
		pref[v] += pref[to];
	}
}

main() {
	freopen("runaway.in", "r", stdin);
	freopen("runaway.out", "w", stdout);
	scanf("%d %lld", &n, &l);
	for (int i = 2; i <= n; i++) {
		scanf("%d %lld", &lc[0][i], &lcsum[0][i]);
		gr[lc[0][i]].push_back(i);
	}
	dfs(1);
	dfs1(1);
	for (int i = 1; i <= n; i++) {
		printf("%d\n", pref[i]);
	}
}
