#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int n;

main() {
  n = uniform_int_distribution<int>(3, 5)(rng);
  cout << n << endl;
  cout << -1 << ' ' << 0 << ' ' << 0 << ' ';
  for (int i = 3; i < n; i++) {
    cout << uniform_int_distribution<int>(1, 2)(rng) << ' ';
  }
  cout << endl;
  for (int i = 0; i < n; i++) {
    cout << uniform_int_distribution<int>(1, 5)(rng) << ' ';
  }
  cout << endl;
  
  for (int i = 0; i < n; i++) {
    cout << uniform_int_distribution<int>(1, 5)(rng) << ' ';
  }
  cout << endl;
  
}
