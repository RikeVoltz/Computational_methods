#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef unsigned long long  ull;
typedef vector<int> vi;

struct pp { ll x, y; };

const int base = 1000 * 1000 * 1000;
const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int inf = (int)1e9;
const int mod = 1e9 + 7;
int main() {
	//freopen("rsq.in","r",stdin);
	//freopen("rsq.out","w",stdout);
	ll l, r;
	cin >> l >> r;
	ll cnt = 1, cnt2 = 1;
	vector<int> v;
	for (ll i = 0; i<50; i++) {
		for (ll j = 0; j<50; j++) {
			v.push_back(cnt2*cnt);
			cnt2 *= 3;
			if (cnt2*cnt>2e9)break;
		}
		cnt2 = 1;
		cnt *= 2;
		if (cnt>2e9)break;
	}
	sort(v.begin(), v.end());
	cnt = 0;
	for (auto i : v)if (i >= l && i <= r)cnt++;
	cout << cnt;
	return 0;
}