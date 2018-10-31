#include "grader.cpp"
#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int N = (int)1e5 + 7;
const int inf = (int)1e9 + 7;

int dp[N];
deque < int > dq[100];

ll conta(int S, int s[], int P, int p[])  {
	for (int i = 0; i < P; i++) {
		dp[i] = inf;
	}
	for (int i = 0; i < P; i++) 
		dq[p[i]].push_front(i);
	ll ans = 0;
	for (int i = 0; i < S; i++) {
		for (int j : dq[s[i]]) {
			if (j == 0) {
				dp[j] = i;
			} else {
				dp[j] = dp[j - 1];
			}
		}
		if (dp[P - 1] != inf)
			ans += dp[P - 1] + 1;
	}
	return ans;
}
