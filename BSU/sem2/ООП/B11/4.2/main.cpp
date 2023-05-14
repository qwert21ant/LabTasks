#include "header.h"

int main() {
	srand(time(0));

	TaskList tl;

	int n;
	cout << "Enter amount of tasks: ";
	cin >> n;

	for (int i = 0; i < n; i++)
		tl.append(gen_task());

	cout << "Tasks (" << tl.size() << "): " << endl;
	cout << tl;

	tl.remove((n - 1) / 2);

	cout << "After removing " << ((n - 1) / 2) << "-th task: " << endl;
	cout << tl;

	TaskList tl2 = tl;

	cout << "Copy: " << endl;
	cout << tl2;

	TaskList tl3;
	for (int i = 0; i < n; i++)
		tl3.append(gen_task());

	tl3 = tl2;

	cout << "Copy operator: " << endl;
	cout << tl3;

	return 0;
}