#include "header.h"

int main() {
	List<Student> list;

	Student s[] = {
		{"E", "0", 2, 120},
		{"F", "0", 2, 80},
		{"G", "0", 3, 90},
		{"H", "0", 3, 120},
		{"A", "0", 1, 80},

		{"B", "0", 1, 90},
		{"C", "0", 1, 100},
		{"D", "0", 2, 110},
		
		{"I", "0", 3, 130}
	};
	int len = extent<decltype(s)>::value;

	for (auto& x : s)
		add(list, x);

	print(list, "\n");

	for (int i = 1; i <= 3; i++) {
		cout << "Course " << i << ":" << endl;
		double avg = get_avg(list, i);
		cout << "  Avg: " << avg << endl;

		List<Student> lf = filter(list, i, avg);
		print(lf, "\n");
	}

	print(list, "\n");

	return 0;
}