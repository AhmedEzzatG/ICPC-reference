#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> adj, par;
// adj[i][j] = oo , adj[i][i] = 0 
// par[i][j] = i

void init(int n) {
	par = adj = vector<vector<int>>(n + 1, vector<int>(n + 1, oo));
	for (int i = 1; i <= n; i++)
		adj[i][i] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			par[i][j] = i;
}

void floyd() {
	for (int k = 1; k < adj.size(); k++)
		for (int i = 1; i < adj.size(); i++)
			for (int j = 1; j < adj.size(); j++)
				if (adj[i][j] > adj[i][k] + adj[k][j]) {
					adj[i][j] = adj[i][k] + adj[k][j];
					par[i][j] = par[k][j];
				}
}

void buildPath(int src, int dest) {
	vector<int> path;
	while (src != dest) {
		path.push_back(dest);
		dest = par[src][dest];
	}
	path.push_back(src);
	reverse(path.begin(), path.end());
}
