#include "header.h"

inline long long f(long long k) {
	return 1ll << k;
}

vector<int> solve(int k) {
	if (k == 1) {
		vector<int> res = { 1, 2 };
		return res;
	}
	else if (k == 2) {
		vector<int> res = { 1, 4, 3, 2 };
		return res;
	}

	vector<int> res(f(k), 0);
	vector<int> prev = solve(k - 1);

	for (int i = 0, j = 0; j < prev.size();) {
		res[i] = prev[j++];
		i += 3;
		res[i] = prev[j++];
		i++;
	}

	vector<int> pprev = solve(k - 2); // bad

	bool side = true;
	int j = f(k - 1) + 1;
	for (int i = 0; i < pprev.size(); i++, j++, side = !side) {
		int x = pprev[i];
		
		res[1 + 4 * (x - 1) + side] = j;
	}

	for (int i = pprev.size() - 1; i >= 0; i--, j++, side = !side) {
		int x = pprev[i];

		res[1 + 4 * (x - 1) + side] = j;
	}

	return res;
}

int main() {
	int k;
	cin >> k;

	vector<int> res = solve(k);

	for (int x : res)
		cout << x << " ";

	return 0;
}