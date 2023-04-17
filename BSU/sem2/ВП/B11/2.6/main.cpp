#include "header.h"

int main() {
	srand(time(0));

	int n;
	cout << "Enter n: ";
	cin >> n;

	List<int> list;
	for (int i = 0; i < 2 * n; i++) {
		list.push(rand() % 100);
	}

	print(list);

	int ans = -1;
	auto it1 = list.begin(), it2 = --list.end();
	for (int i = 0; i < n; i++, ++it1, --it2) {
		ans = max(ans, min(*it1, *it2));
	}

	cout << "Result: " << ans;

	return 0;
}