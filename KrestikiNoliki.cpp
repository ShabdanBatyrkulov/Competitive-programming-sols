/*
Link to the problem:
https://olymp.krsu.edu.kg/GeneralProblem.aspx?problem=114&format=html
*/

#include <bits/stdc++.h>

using namespace std;

int pw[10];
char c[3][3];
short dp[27*27*27 + 7];
/*
0 = draw
1 = X wins
2 = 0 wins
*/

int whose_turn(int state) {
	int res = 0;
	for (int i = 0; i < 9; i++) {
		res += (state % 3 == 0);
		state /= 3;
	}
	if (res == 0) return -1;
	return res % 2;
}

int getpos(int state, int pos) {
	return state / pw[pos] % 3;
}

int check(int state) {
	int who;
	for (int i = 0; i < 3; i++) {
		who = getpos(state, i * 3);
		if (who != 0 && who == getpos(state, i * 3 + 1) && who == getpos(state, i * 3 + 2)) return who;
		who = getpos(state, i);
		if (who != 0 && who == getpos(state, i + 3) && who == getpos(state, i + 6)) return who;
	}
	who = getpos(state, 4);
	if (who == 0) return 0;
	if (who == getpos(state, 0) && who == getpos(state, 8)) return who;
	if (who == getpos(state, 2) && who == getpos(state, 6)) return who;
	return 0;
}

void print(int state) {
	for (int i = 0; i < 9; i++) {
		if (getpos(state, i) == 0) {
			cout << '-';
		} else if (getpos(state, i) == 1) {
			cout << 'X';
		} else {
			cout << '0';
		}
		if (i % 3 == 2) {
			puts("");
		}
	}
	system("pause");
}

short calc(int state) {
	short &res = dp[state];
	if (res != -1) {
		return res;
	}
	// Does someone win?
	int who_win = check(state);
	if (who_win != 0) {
		return res = who_win;
	}
	//
	bool has_state[3] = {0, 0, 0};
	int wt = whose_turn(state);		 
	if (wt == -1) return res = 0;
	if (wt == 1) {		
		for (int i = 0; i < 9; i++) {
			if (getpos(state, i) == 0) {
				int next_state = calc(state + pw[i] * 1);
				has_state[next_state] = 1;
			}
		}
		if (has_state[1]) {
			res = 1;
		} else if (has_state[0]) {
			res = 0;
		} else {
			res = 2;
		}
	} else {
		for (int i = 0; i < 9; i++) {
			if (getpos(state, i) == 0) {
				int next_state = calc(state + pw[i] * 2);
				has_state[next_state] = 1;
			}
		}
		if (has_state[2]) {
			res = 2;
		} else if (has_state[0]) {
			res = 0;
		} else {
			res = 1;
		}
	}
	return res;
}

main() {
	pw[0] = 1;
	for (int i = 1; i < 10; i++) {
		pw[i] = pw[i - 1] * 3;
	}
	memset(dp, -1, sizeof dp);
	int final_state = 0;
	for (int i = 0; i < 3; i++) {
		int res;
		for (int j = 0; j < 3; j++) {
			c[i][j] = getchar();
			if (c[i][j] == '-') {
				res = 0;
			} else if (c[i][j] == 'X') {
				res = 1;
			} else {
				res = 2;
			}
			final_state += res * pw[j + i * 3];
		}
		getchar();
	}
	calc(0);
	assert(dp[final_state] != -1);
	if (dp[final_state]) {
		cout << "Yes";
	} else {
		cout << "No";
	}
}
