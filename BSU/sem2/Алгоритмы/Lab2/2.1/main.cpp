#include "header.h"

using graph = vector<vector<int>>;

void add(graph& g, int from, int to) { // indexing from 1 for parameters
	if (g.size() <= from - 1 || g.size() <= to - 1)
		throw std::out_of_range("");

	g[from - 1].push_back(to - 1);
}

void print(graph& g) {
	for (int i = 0; i < g.size(); i++) {
		cout << i + 1 << ": ";
		for (int j = 0; j < g[i].size(); j++)
			cout << g[i][j] + 1 << " ";
		cout << endl;
	}
}

graph init(int n) {
	return vector<vector<int>>(n, vector<int>());
}

void dfs(graph& g, vector<char>& u, int v) {
	u[v] = 1;

	for (int i = 0; i < g[v].size(); i++) {
		if (u[g[v][i]])
			continue;

		dfs(g, u, g[v][i]);
	}
}

vector<int> get_unavaliable(graph& g, int start) {
	vector<int> res;

	vector<char> used(g.size(), 0);
	
	dfs(g, used, start);

	for (int i = 0; i < used.size(); i++) {
		if (used[i])
			continue;

		res.push_back(i);
	}
	return res;
}

int main() {
	//ifstream fin("input.txt");

	istream& in = cin;

	int n, m, k; // number of vertex, number of edges, start vertex
	in >> n >> m >> k;

	graph g = init(n);

	for (int i = 0; i < m; i++) {
		int a, b;
		in >> a >> b;
		add(g, a, b);
	}

	cout << "Graph: " << endl;
	print(g);
	cout << endl;

	auto ans = get_unavaliable(g, k - 1);

	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] + 1 << " ";
	cout << endl;

	return 0;
}