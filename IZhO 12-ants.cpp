#include <bits/stdc++.h>

using namespace std;

#define ok puts("ok");

const int N = (int)1e2 + 7;

int w, h, k, t;
int x[N], y[N], d[N];
vector < int > ver[101], gor[101];
int ans[101][3];

main () {
	freopen("e.in", "r", stdin);
	freopen("e.out", "w", stdout);
	scanf("%d %d %d %d", &w, &h, &k, &t);
	for (int i = 1; i <= k; i++) {
		scanf("%d %d %d", &x[i], &y[i], &d[i]);
		if (d[i] == 1 || d[i] == 3) {
			gor[y[i]].push_back(i);
		} else {
			ver[x[i]].push_back(i);
		}
	}
	int add = t % (2 * w);
	for (int i = 0; i <= h; i++) {
		sort(gor[i].begin(), gor[i].end(), [&](const int &A, const int &B) {
			return x[A] < x[B];
		});
		for (int to : gor[i]) {
			if (d[to] == 1) {
				x[to] += add;
				if (x[to] >= w) {
					x[to] = (2 * w - x[to]);
					d[to] ^= 2;
				}
				if (x[to] <= 0) {
					x[to] *= -1;
					d[to] ^= 2;
				}
			} else {
				x[to] -= add;
				if (x[to] <= 0) {
					x[to] *= -1;
					d[to] ^= 2;
				}
				if (x[to] >= w) {
					x[to] = (2 * w - x[to]);
					d[to] ^= 2;
				}
			}
		}
		vector < pair < int, int > > temp;
		for (int to : gor[i]) {
			temp.push_back({x[to], d[to]});
		}
		sort(temp.begin(), temp.end(), [&](pair < int, int > &A, pair < int, int > &B) {
			if (A.first == B.first) {
				return A.second > B.second;
			}
			return A.first < B.first;
		});
		for (int j = 0; j < temp.size(); j++) {
			ans[gor[i][j]][0] = temp[j].first;
			ans[gor[i][j]][1] = i;
			ans[gor[i][j]][2] = temp[j].second;
		}
	}
	add = t % (2 * h);
	for (int i = 0; i <= w; i++) {
		sort(ver[i].begin(), ver[i].end(), [&](const int &A, const int &B) {
			return y[A] < y[B];
		});
		for (int to : ver[i]) {
			if (d[to] == 2) {
				y[to] += add;
				if (y[to] >= h) {
					y[to] = (2 * h - y[to]);
					d[to] = (d[to] % 4) + 2;
				}
				if (y[to] <= 0) {
					y[to] *= -1;
					d[to] = (d[to] % 4) + 2;
				}
			} else {
				y[to] -= add;
				if (y[to] <= 0) {
					y[to] *= -1;
					d[to] = (d[to] % 4) + 2;
				}
				if (y[to] >= h) {
					y[to] = h + h - y[to];
					d[to] = (d[to] % 4) + 2;
				}
			}
		}
		vector < pair < int, int > > temp;
		for (int to : ver[i]) {
			temp.push_back({y[to], d[to]});
		}
		sort(temp.begin(), temp.end(), [&](pair < int, int > &A, pair < int, int > &B) {
			if (A.first == B.first) {
				return A.second > B.second;d
			}
			return A.first < B.first;
		});
		for (int j = 0; j < temp.size(); j++) {
			ans[ver[i][j]][0] = i;
			ans[ver[i][j]][1] = temp[j].first;
			ans[ver[i][j]][2] = temp[j].second;
		}
	}
	for (int i = 1; i <= k; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", ans[i][j]);
		}
		puts("");
	}
}
