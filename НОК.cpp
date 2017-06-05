#include <bits/stdc++.h>

#define sz(s) ((int) s.size ())
#define pb push_back
#define fr first
#define sc second
    
using namespace std;

const int base = (int) 1e9;
                     
struct bignum {
	vector<int> n;
	int sign;
	bignum () {
		
	}
	friend bignum operator + (bignum a, bignum b);
	friend bignum operator - (bignum a, bignum b);
	friend bignum operator * (bignum a, bignum b);
	friend bool operator == (bignum a, bignum b);
	friend bool operator != (bignum a, bignum b);
	friend bool operator < (bignum a, bignum b);
	friend bool operator <= (bignum a, bignum b);
	friend bool operator > (bignum a, bignum b);	
	friend bool operator >= (bignum a, bignum b);
	friend void read (bignum &a);
	friend void print (bignum a);
	friend bool operator == (bignum a, bignum b) {
		if (sz (a.n) != sz (b.n)) {
			return false;
		}
		for (int i = 0; i < sz (a.n); i++) {
			if (a.n[i] != b.n[i]) {
				return false;
			}
		}
		return true;
	}
	friend bool operator != (bignum a, bignum b) {
		return !(a == b);
	}
	friend bool operator < (bignum a, bignum b) {
		if (sz (a.n) < sz (b.n)) {
			return true;
		} else if (sz (a.n) > sz (b.n)) {
			return false;
		} else {
			for (int i = sz (a.n) - 1; i >= 0; i--) {
				if (a.n[i] < b.n[i]) {
					return true;
				} else if (a.n[i] > b.n[i]) {
					return false;
				}
			}
			return false;
		}
	}
	friend bool operator <= (bignum a, bignum b) {
		return a < b || a == b;
	}
	friend bool operator > (bignum a, bignum b) {
		return !(a <= b);
	}
	friend bool operator >= (bignum a, bignum b) {
		return a > b || a == b;
	}
	friend bignum operator + (bignum a, bignum b) {
		for (int i = 0, carry = 0; i < max (sz (a.n), sz (b.n)) || carry > 0; i++) {
			int x = i < sz (a.n) ? a.n[i] : 0;
			int y = i < sz (b.n) ? b.n[i] : 0;
			int s = x + y + carry;
			if (s >= base) {
				s -= base;
				carry = 1;
			} else {
				carry = 0;
			}
			if (i < sz (a.n)) {
				a.n[i] = s;
			} else {
				a.n.push_back (0);
				a.n[i] = s;
			}					
		}
		return a; 				
	}
	friend bignum operator - (bignum a, bignum b) {
		for (int i = 0, carry = 0; i < sz (a.n) || carry > 0; i++) {
			int x = i < sz (b.n) ? b.n[i] : 0;
			int d = a.n[i] - x - carry;
			if (d < 0) {
				d += base;
				carry = 1;
			} else {
				carry = 0;
			}
			a.n[i] = d;					
		}
		while (sz (a.n) > 1 && a.n.back () == 0) {
			a.n.pop_back ();
		}               
		return a;
	}
	friend bignum operator * (bignum a, bignum b) {
		bignum c; c.n.resize (sz (a.n) + sz (b.n));
		for (int i = 0; i < sz (a.n); i++) {
			for (int j = 0, carry = 0; j < sz (b.n) || carry > 0; j++) {
				long long m = c.n[i + j] + a.n[i] * 1LL * (j < sz (b.n) ? b.n[j] : 0) + carry;
				c.n[i + j] = m % base;
				carry = m / base;								
			}    	
		}
		while (sz (c.n) > 1 && c.n.back () == 0) {
			c.n.pop_back ();
		}
		return c; 
	}
	friend bignum operator / (bignum a, bignum b) {
		int carry = 0;
		for (int i = sz(a.n) - 1; i >= 0; i--) {
			long long cur = a.n[i] + carry * 1LL * base;
			a.n[i] = cur / b.n[0];
			carry = cur % b.n[0];
		}
		while (sz(a.n) > 1 && a.n.back() == 0) {
			a.n.pop_back();
		}
		return a;

	}
	friend bignum operator % (bignum a, bignum b) {
		int carry = 0;
		bignum c; c.n.pb(0);
		for (int i = sz(a.n) - 1; i >= 0; i--) {
			long long cur = a.n[i] + carry * 1LL * base;
			a.n[i] = cur / b.n[0];
			carry = cur % b.n[0];
			c.n[0] = carry;
		}
		while (sz(a.n) > 1 && a.n.back() == 0) {
			a.n.pop_back();
		}        
		return c;
	}
	friend void read (bignum &a) {
		a.n.clear ();
		string s; cin >> s;
		if (s[0] == '-') {
			a.sign = -1;
		} else {
			a.sign = 1;
		}
		for (int i = sz (s); i > 0; i -= 9) {
			if (i >= 9) {
				a.n.push_back (atoi (s.substr (i - 9, 9).c_str ()));
			} else {
				a.n.push_back (atoi (s.substr (0, i).c_str ()));
			}			
		} 
	}
	friend void print (bignum a) {
		printf ("%d", a.n.back ());
		for (int i = sz (a.n) - 2; i >= 0; i--) {
			printf ("%09d", a.n[i]);
		}
	}
	friend bignum gcd (bignum a, bignum b) {
		bignum c, d; c.n.pb(0);
		if (b == c) {
			return a;
		}
		return gcd(b, a % b);
	}
	friend bignum lcm (bignum a, bignum b) {
		return a / gcd(a, b) * b;		
	} 
};
	
int main () {
	bignum a, b, c, d, e, f, ans;   
	int n; cin >> n;
	ans.n.pb(1);
	for (int i = 1; i <= n; i++) {
		read(a);
		ans = lcm(ans, a);				
	}                  
	print(ans);
}
