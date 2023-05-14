#include "header.h"

int main() {
	srand(time(0));

	int n;
	cout << "Enter amount of tasks: ";
	cin >> n;

	vector<Task*> tasks(n, nullptr);

	for (auto& el : tasks)
		el = gen_task();

	for (auto el : tasks)
		cout << *el << endl << endl;

	return 0;
}