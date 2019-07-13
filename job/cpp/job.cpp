#include <bits/stdc++.h>
#include "job.h"
#include "grader.cpp"

using namespace std;

#define ll long long

const int maxn = 2e5 + 7;

vector <int> gr[maxn];
vector <int> p, u, d;
int n;
ll ans;
ll U[maxn];

bool check(int a, int b) {
  return d[a] * U[b] <= d[b] * U[a]; 
}

ll scheduling_cost(vector<int> _p, vector<int> _u, vector<int> _d) {
	n = _p.size();
  p = _p; u = _u; d = _d;
  for (int i = 1; i < n; i++) {
    gr[p[i]].push_back(i);
  }
  for (int i = n - 1; i >= 0; i--) {
    U[i] += u[i];
    for (int to : gr[i]) {
      U[i] += U[to];
    }
    ans += d[i] * U[i];
  }
  if (gr[0].size() == 1) return ans;
  vector <int> vec[2];
  int cur = gr[0][0];
  while (cur != -1) {
    vec[0].push_back(cur);
    cur = ((!gr[cur].empty()) ? gr[cur][0] : -1);
  }
  cur = gr[0][1];
  while (cur != -1) {
    vec[1].push_back(cur);
    cur = ((!gr[cur].empty()) ? gr[cur][0] : -1);
  }
  for (int i = 0; i < 2; i++) {
    reverse(vec[i].begin(), vec[i].end());
  }
  while (!vec[0].empty() && !vec[1].empty()) {
    cout << d[vec[0].back()] * U[vec[1].back()] << ' ' << d[vec[1].back()] * U[vec[0].back()] << '\n';
    if (check(vec[0].back(), vec[1].back())) {
      ans += d[vec[0].back()] * U[vec[1].back()];
      vec[0].pop_back();
    } else {
      ans += d[vec[1].back()] * U[vec[0].back()];
      vec[1].pop_back();
    }
  }
  return ans;
}
