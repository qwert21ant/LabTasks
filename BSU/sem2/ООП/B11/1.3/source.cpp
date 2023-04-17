#include "header.h"

template <class T>
T read(istream& in) {
	T res;
	in.read((char*) &res, sizeof(T));
	return res;
}

template <class T>
void write(ostream& out, T value) {
	out.write((char*) &value, sizeof(T));
}

void read_student(istream& in, Student& student) {
	int name_len = read<int>(in);

	char* buf = new char[name_len + 1];
	in.read(buf, name_len);
	buf[name_len] = 0;

	student.name = buf;
	delete[] buf;

	student.age = read<int>(in);
	student.male = read<bool>(in);
	student.course = read<int>(in);
	student.grade = read<double>(in);
}

void write_student(ostream& out, const Student& student) {
	write<int>(out, student.name.length());
	out.write((char*) student.name.c_str(), student.name.length());
	write(out, student.age);
	write(out, student.male);
	write(out, student.course);
	write(out, student.grade);
}

void read_students(istream& in, vector<Student>& students) {
	in.peek();
	while (!in.eof()) {
		Student student;
		read_student(in, student);
		students.push_back(student);
		in.peek();
	}
}

double count_avg_grade(vector<Student>& students, int course) {
	double sum = 0.;
	int cnt = 0;
	for (auto& student : students) {
		if (student.course != course)
			continue;

		sum += student.grade;
		cnt++;
	}

	return cnt ? sum / cnt : 0.;
}

void write_students(ostream& out, vector<Student>& students) {
	for (auto& student : students)
		write_student(out, student);
}

void solve(vector<Student>& students, int course, vector<Student>& result) {
	double avg = count_avg_grade(students, course);

	for (auto& student : students) {
		if (student.course != course)
			continue;

		if (student.grade <= avg)
			continue;

		result.push_back(student);
	}
}