#include<bits/stdc++.h>
using namespace std;

class trie {
	struct trie_node {
		bool is_leaf = false;
		map<char, int> next;
		bool have_next(char ch) {
			return next.find(ch) != next.end();
		}
		int& operator[](char ch) {
			return next[ch];
		}
	};
	vector<trie_node> t;
public:
	trie() {
		t.push_back(trie_node());
	}
	void insert(const string &s) {
		int root = 0;
		for (const char &ch : s) {
			if (!t[root].have_next(ch)) {
				t.push_back(trie_node());
				t[root][ch] = t.size() - 1;
			}
			root = t[root][ch];
		}
		t[root].is_leaf = true;
	}
	bool find(const string &s) {
		int root = 0;
		for (const char &ch : s) {
			if (!t[root].have_next(ch))
				return false;
			root = t[root][ch];
		}
		return t[root].is_leaf;
	}
};
