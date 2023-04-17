#include "header.h"

int main() {
	ifstream fin("students.bin", ios::binary);
	if (!fin) {
		cout << "Unable to open file students.bin" << endl;
		return 0;
	}

	int course;
	cout << "Course: ";
	cin >> course;

	vector<Student> students;
	read_students(fin, students);

	vector<Student> result;
	solve(students, course, result);

	ofstream fout("result.bin", ios::binary);
	if (!fout) {
		cout << "Unable to open file result.bin" << endl;
		return 0;
	}

	write_students(fout, result);

	return 0;
}