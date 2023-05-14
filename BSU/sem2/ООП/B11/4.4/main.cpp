#include "header.h"

int main() {
	srand(time(0));

	TaskList tl;

	int n;
	cout << "Enter amount of tasks: ";
	cin >> n;

	for (int i = 0; i < n; i++)
		tl.push_front(gen_task());

	cout << "Tasks:" << endl;
	cout << tl;

	tl.pop_front();

	cout << "After removing:" << endl;
	cout << tl;

	TaskList tl2 = tl;

	cout << "Copy: " << endl;
	cout << tl2;

	TaskList tl3;
	for (int i = 0; i < n; i++)
		tl3.push_front(gen_task());

	tl3 = tl2;

	cout << "Copy operator: " << endl;
	cout << tl3;

	TaskList tl4 = move(tl3);

	cout << "Move:" << endl;
	cout << tl4;

	TaskList tl5;
	for (int i = 0; i < n; i++)
		tl5.push_front(gen_task());

	tl5 = move(tl4);

	cout << "Move operator:" << endl;
	cout << tl5;
	
	tl5.clear();

	cout << "After clear: " << endl;
	cout << tl5;

	return 0;
}