#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

/*
dp one order of nodes
dp[i][j] = means
i = till what time nodes are processed
j = number of nodes which were taken
if we don't take the node dp[i][j] = max(dp[i][j], dp[i - 1][j]);
else dp[i][j] = max(dp[i][j], dp[left - 1][j - 1] + w[v]);
*/

const int N = (int)2e5 + 7;
const int M = (int)500 + 7;

int n, m;
int pr[N], w[N];
vector < int > gr[N];
vector < int > order;
int tiktak = 1;
int tin[N], tout[N];
int dp[N][M];

void dfs(int v) {
	if (gr[v].empty()) tiktak++;
	tin[v] = tiktak;
	for (int to : gr[v]) {
		dfs(to);
	}
	order.push_back(v);
	tout[v] = tiktak;
}

main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> pr[i] >> w[i];
		gr[pr[i]].push_back(i);
	}
	dfs(gr[0][0]);
	for (int i = 0; i < n; i++) {
		int v = order[i];
		int l = tin[v];
		int r = tout[v];
		for (int j = 0; j <= m; j++) {
			dp[r][j] = max(dp[r][j], dp[r - 1][j]);
		}
		for (int j = 1; j <= min(l, m); j++) {
			dp[r][j] = max(dp[r][j], dp[l - (l == r)][j - 1] + w[v]);
		}
	}
	int res = 0;
	for (int i = 0; i <= tiktak; i++) {
		res = max(res, dp[i][m]);
	}
	cout << res;
}

