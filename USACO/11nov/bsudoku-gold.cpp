#include <iostream>
#include <memory.h>

using namespace std;

const int inf = (int)1e9 + 7;

/*
dp[r][c][mc][mb][p] = minimum invertion we can make to make mc(parity of columns) and mb(parity of board 3x3), and current row even.
*/

int a[9][9];
int dp[9][9][1 << 9][1 << 3][2];

int solve(int r, int c, int mc, int mb, int p) {
	if (r == 9) {
		return (mc ? inf : 0);
	}
	if (c == 9) {
		if (p) return inf;
		if (r % 3 == 2 && mb) {
			return inf;
		}
		return solve(r + 1, 0, mc, mb, 0);
	}
	int &res = dp[r][c][mc][mb][p];
	if (res != -1) return res;
	res = !a[r][c] + solve(r, c + 1, mc ^ (1 << c), mb ^ (1 << (c / 3)), p ^ 1);
	res = min(res, a[r][c] + solve(r, c + 1, mc, mb, p));
	return res;
}

int main() {
	ios::sync_with_stdio(0);
  cin.tie(0);
  memset(dp, -1, sizeof dp);
  for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			a[i][j] = getchar() == '1';
		}
		getchar();
  }
	cout << solve(0, 0, 0, 0, 0);
}
