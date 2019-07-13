#include <bits/stdc++.h>
#include "job.h"
#include "grader.cpp"

using namespace std;

#define ll long long

const int maxn = 2e5 + 7;

vector <int> gr[maxn];
vector <int> p, u, d;
int n;
ll ans = 0;

ll scheduling_cost(vector<int> _p, vector<int> _u, vector<int> _d) {
	n = _p.size();
  p = _p; u = _u; d = _d;
  vector <int> pos(n);
  iota(pos.begin(), pos.end(), 0);
  ans = d[0] * u[0];
  int s = d[0];
  sort(pos.begin() + 1, pos.end(), [&](const int &A, const int &B) {
    return _u[A] > _u[B];
  });
  for (int i = 1; i < n; i++) {
    s += d[pos[i]];
    ans += s * 1LL * u[pos[i]];
  }
  return ans;
}
