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

int n;
bool isNotPrime[300005];
vector<int> ants[300005];
vector<int> myPrimeGroups[300005];
vector<int> primeGroups[30005];
int visited[300005];
int from, to;

int main() {
    UNSYNC; READTXT;
    cin >> n;

    FOR(i, 1, n) {
        DINPUT(int, x);
        ants[x].push_back(i);
    }

    cin >> from >> to;

    isNotPrime[1] = true;
    int idx = 0;
    for (int i = 2; i <= 300000; i++) {
        if (isNotPrime[i]) {
            continue;
        }

        for (int ant : ants[i]) {
            primeGroups[idx].push_back(ant);
            myPrimeGroups[ant].push_back(idx);
        }

        for (int j = i * 2; j <= 300000; j += i) {
            isNotPrime[j] = true;

            for (int ant : ants[j]) {
                primeGroups[idx].push_back(ant);
                myPrimeGroups[ant].push_back(idx);
            }
        }

        idx++;
    }

    queue<int> Q;
    visited[from] = -1;
    Q.push(from);

    while (!Q.empty()) {
        int node = Q.front();
        Q.pop();

        if (node == to) {
            break;
        }

        for (int primeGroup : myPrimeGroups[node]) {
            for (int nextAnt : primeGroups[primeGroup]) {
                if (visited[nextAnt] || nextAnt == node) {
                    continue;
                }

                visited[nextAnt] = node;
                Q.push(nextAnt);
            }

            primeGroups[primeGroup].clear();
        }
    }

    if (!visited[to]) {
        PRINT(-1);
        return 0;
    }

    vector<int> ans;
    int cur = to;
    ans.push_back(cur);

    while (cur != from) {
        cur = visited[cur];
        ans.push_back(cur);
    }

    reverse(ALL(ans));
    PRINT(ans.size());

    for (int i : ans) {
        cout << i << ' ';
    }

    return 0;
}