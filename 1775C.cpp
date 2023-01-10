/*
 * A problem solving template
 * Written in 2022 by Na Jongwoo <njw1204@naver.com>
 *
 * Please visit: https://github.com/njw1204/problem-solving-template
 */

#if defined(__GNUC__)&&!defined(__llvm__)
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2")
#endif
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<ull, ull> pul;
#define __CC(a,b) a##b
#define $1 first
#define $2 second
#define endl '\n'
#define DINPUT(t,...) t __VA_ARGS__;INPUT(__VA_ARGS__)
#define REP(i,n) for(int i=0,__REP##i=0;__REP##i<(n);i=++__REP##i)
#define FOR(i,s,e) for(auto i=(s),__FOR##i=(s);__FOR##i<=(e);i=++__FOR##i)
#define TESTCASE(t) DINPUT(int,__TESTCASE##t);FOR(t,1,__TESTCASE##t)
#define MEMZERO(a) memset((a),0,sizeof(a))
#define MEMNEG(a) memset((a),-1,sizeof(a))
#define FILL(c,x) for(auto &__FILL:(c))__FILL=(x)
#define ALL(c) (c).begin(),(c).end()
#define UNSYNC ios_base::sync_with_stdio(false);cin.tie(nullptr)
#ifdef LOCAL_ALGO
#define READTXT for(__CC(ifst,ream) __READTXT(STDIN);__READTXT&&__READTXT.get()!=-1&&__CC(freo,pen)(STDIN,"r",stdin);)__READTXT.close()
#define DEBUG(...) cerr << "[" << #__VA_ARGS__ << "]:", __DEBUG_OUT(__VA_ARGS__)
#else
#define READTXT
#define DEBUG(...)
#endif
#define STDIN "_input.txt"
string to_string(const string& s) { return '"' + s + '"'; } string to_string(bool b) { return b ? "true" : "false"; } string to_string(char c) { string s; s += c; return s; }
template <typename A, typename B> string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename A, typename B, typename C> string to_string(tuple<A, B, C> p) { return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")"; }
template <typename A> string to_string(A v) { bool f = true; string r = "{"; for (const auto& x : v) { if (!f) r += ", "; f = false; r += to_string(x); } r += "}"; return r; }
void __DEBUG_OUT() { cerr << endl; } template <typename H, typename... T> void __DEBUG_OUT(H h, T... t) { cerr << " " << to_string(h); __DEBUG_OUT(t...); }
template<typename T> const T& MIN(const T& arg) { return arg; } template<typename T, typename... Ts> const T& MIN(const T& arg, const Ts&... args) { return min(arg, MIN(args...)); }
template<typename T> const T& MAX(const T& arg) { return arg; } template<typename T, typename... Ts> const T& MAX(const T& arg, const Ts&... args) { return max(arg, MAX(args...)); }
template<typename T> void INPUT(T& arg) { cin >> arg; } template<typename T, typename... Ts> void INPUT(T& arg, Ts&... args) { cin >> arg; INPUT(args...); }
template<typename T> void PRINT(const T& arg) { cout << arg << '\n'; } template<typename T, typename... Ts> void PRINT(const T& arg, const Ts&... args) { cout << arg << ' '; PRINT(args...); }
ull GCD(ull a, ull b) { while (b != 0) { ull t = a % b; a = b; b = t; } return a; }
ull LCM(ull a, ull b) { return a * b > 0 ? a * b / GCD(a, b) : 0; }
ull POW(ull a, ull b, ull m = ULLONG_MAX) { ull r = 1; while (b) { if (b & 1) r = r * a % m; b >>= 1; a = a * a % m; } return r; }

ll n, x;
int bits[2][100];

void clear() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 100; j++) {
            bits[i][j] = 0;
        }
    }
}

int main() {
    UNSYNC; READTXT;
    TESTCASE(T) {
        clear();
        cin >> n >> x;
        ll savedn = n;
        ll savedx = x;

        for (int i = 0; n; i++) {
            bits[0][i] = n % 2;
            n /= 2;
        }

        for (int i = 0; x; i++) {
            bits[1][i] = x % 2;
            x /= 2;
        }

        bool ok = true;
        vector<int> needToOff;
        vector<int> needToRemain;

        for (int i = 0; i < 100; i++) {
            if (bits[1][i] && !bits[0][i]) {
                ok = false;
                break;
            }

            if (!bits[1][i] && bits[0][i]) {
                needToOff.push_back(i);
                continue;
            }

            if (bits[1][i] && bits[0][i]) {
                needToRemain.push_back(i);
                continue;
            }
        }

        sort(ALL(needToOff), greater<int>());
        sort(ALL(needToRemain), greater<int>());

        int toBits[100] = {0};

        if (!needToOff.empty()) {
            toBits[needToOff[0] + 1] = 1;

            for (int i : needToRemain) {
                if (i < needToOff[0]) {
                    ok = false;
                    break;
                }
            }
        }

        for (int i : needToRemain) {
            toBits[i] = 1;
        }

        ll finalVal = 0;
        ll base = 1;

        for (int i = 0; i < 64; i++) {
            if (toBits[i]) {
                finalVal += base;
            }

            base *= 2;
        }

        if (!ok || (savedn & finalVal) != savedx || finalVal < savedn) {
            PRINT(-1);
            continue;
        }

        PRINT(finalVal);
        continue;
    }
}