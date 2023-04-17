#include "header.h"

template <class T>
void printv(vector<vector<T>>& v) {
	for (auto& a : v) {
		for (auto& b : a) {
			cout << int(b) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

/*
8 10
1 2 51
1 3 51
2 4 41
3 4 10
1 5 51
1 6 51
5 7 20
6 7 31
4 8 30
7 8 21
*/

int main() {
	int n, x;
	cin >> n >> x;

	vector<vector<int>> m(n, vector<int>(n, 0));

	for (int i = 0; i < x; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		m[a - 1][b - 1] = c;
	}

	vector<vector<char>> res(n, vector<char>(n, 0));

	vector<vector<int>> tmp;

	bool changes = true;

	while (changes) {
		changes = false;

		//printv(res);

		tmp = m;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (!res[i][j])
					continue;

				for (int k = 0; k < n; k++)
					tmp[i][k] += m[j][k];
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (tmp[i][j] > 50 && !res[i][j]) {
					res[i][j] = 1;
					changes = true;
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!res[i][j])
				continue;

			cout << i + 1 << " " << j + 1 << endl;
		}
	}

	return 0;
}