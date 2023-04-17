#include "header.h"

int main() {
	ifstream fin("students.json", ios::binary);
	if (!fin) {
		cout << "Unable to open file students.json" << endl;
		return 0;
	}

	JsonObject* json = nullptr;
	try {
		json = read_json(fin);
	} catch(JsonException e) {
		cout << e.what() << endl;
		return 0;
	}

	vector<Student> students;
	int course;
	if (!parse_students(json, students, course)) {
		cout << "Incorrect data format" << endl;
		return 0;
	}

	JsonObject* res = solve(students, course);

	ofstream fout("result.json");
	if (!fout) {
		cout << "Unable to open file result.json" << endl;
		return 0;
	}

	print_json(fout, res);

	return 0;
}