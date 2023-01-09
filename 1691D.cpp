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

int N;
vector<ll> arr;
ll dp[200055];
ll dprev[200055];
pi rangeBound[200055];
pl segtree[800055];

void reset(int N) {
    arr.clear();
    
    for (int i = 0; i < N + 5; i++) {
        dp[i] = 0;
        dprev[i] = 0;
        rangeBound[i].$1 = 0;
        rangeBound[i].$2 = 0;
        segtree[i].$1 = 0;
        segtree[i].$2 = 0;
    }
}

void buildDp() {
    dp[0] = arr[0];

    for (int i = 1; i < N; i++) {
        dp[i] = dp[i - 1] + arr[i];
    }

    dprev[N - 1] = arr[N - 1];

    for (int i = N - 2; i >= 0; i--) {
        dprev[i] = dprev[i + 1] + arr[i];
    }
}

void buildRangeBound() {
    priority_queue<pl, vector<pl>, greater<pl>> minHeap;

    for (int i = 0; i < N; i++) {
        rangeBound[i].$2 = N;

        while (!minHeap.empty()) {
            const auto node = minHeap.top();

            if (node.$1 < arr[i]) {
                minHeap.pop();
                rangeBound[node.$2].$2 = i;
            }
            else {
                break;
            }
        }

        minHeap.push({arr[i], i});
    }

    while (!minHeap.empty()) {
        minHeap.pop();
    }

    for (int i = N - 1; i >= 0; i--) {
        rangeBound[i].$1 = -1;

        while (!minHeap.empty()) {
            const auto node = minHeap.top();

            if (node.$1 < arr[i]) {
                minHeap.pop();
                rangeBound[node.$2].$1 = i;
            }
            else {
                break;
            }
        }

        minHeap.push({arr[i], i});
    }
}

void initSegTree(int node, int curStart, int curEnd) {
    if (curStart == curEnd) {
        segtree[node].$1 = dp[curStart];
        segtree[node].$2 = dprev[curStart];
        return;
    }

    initSegTree(node * 2, curStart, (curStart + curEnd) / 2);
    initSegTree(node * 2 + 1, (curStart + curEnd) / 2 + 1, curEnd);
    segtree[node].$1 = max(segtree[node * 2].$1, segtree[node * 2 + 1].$1);
    segtree[node].$2 = max(segtree[node * 2].$2, segtree[node * 2 + 1].$2);
}

pl findSeg(int queryLeft, int queryRight, int node, int curStart, int curEnd) {
    if (queryRight < curStart || queryLeft > curEnd) {
        return {LLONG_MIN, LLONG_MIN};
    }

    if (curStart >= queryLeft && curEnd <= queryRight) {
        return segtree[node];
    }

    pl left = findSeg(queryLeft, queryRight, node * 2, curStart, (curStart + curEnd) / 2);
    pl right = findSeg(queryLeft, queryRight, node * 2 + 1, (curStart + curEnd) / 2 + 1, curEnd);
    return {max(left.$1, right.$1), max(left.$2, right.$2)};
}

int main() {
    UNSYNC; READTXT;
    TESTCASE(T) {
        cin >> N;
        reset(N);

        REP(i, N) {
            DINPUT(int, x);
            arr.push_back(x);
        }

        buildDp();
        buildRangeBound();
        initSegTree(1, 0, N - 1);

        bool ok = true;

        for (int i = 0; i < N; i++) {
            const pi& myRangeBound = rangeBound[i];

            int left = myRangeBound.$1 + 1;
            int right = i - 1;
            ll lsum = 0;
            ll rsum = 0;

            if (left <= right) {
                pl result = findSeg(left, right, 1, 0, N - 1);
                lsum = result.$2 - dprev[i];

                if (lsum < 0) {
                    lsum = 0;
                }
            }

            left = i + 1;
            right = myRangeBound.$2 - 1;

            if (left <= right) {
                pl result = findSeg(left, right, 1, 0, N - 1);
                rsum = result.$1 - dp[i];

                if (rsum < 0) {
                    rsum = 0;
                }
            }

            if (lsum + rsum > 0) {
                ok = false;
                break;
            }
        }

        PRINT(ok ? "YES" : "NO");
    }
}