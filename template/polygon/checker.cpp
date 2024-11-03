#include "bits/stdc++.h"
#include <unordered_map>
#include <unordered_set>
#include "testlib.h"
using namespace std;
#define endl "\n"
#define ll long long
#define sz(s) (int)(s.size())
#define INF 0x3f3f3f3f3f3f3f3fLL
#define all(v) v.begin(),v.end()
#define watch(x) cout<<(#x)<<" = "<<x<<endl
const int dr[] { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dc[] { 0, 1, 1, 1, 0, -1, -1, -1 };
#if __cplusplus >= 201402L
template<typename T>
vector<T> create(size_t n) {
	return vector<T>(n);
}
template<typename T, typename ... Args>
auto create(size_t n, Args ... args) {
	return vector<decltype(create<T>(args...))>(n, create<T>(args...));
}
#endif

#define INPUT inf
#define OUTPUT ouf
#define MainSolution ans

vector<string> readTokens(InStream &in) {
	vector<string> tmp;
	while (!in.seekEof())
		tmp.push_back(in.readWord());
	return tmp;
}

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	registerTestlibCmd(argc, argv);
}
