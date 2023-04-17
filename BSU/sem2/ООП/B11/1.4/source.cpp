#include "header.h"

JsonObject* find_field(JsonObject* json, string field_name) {
	for (auto& field : json->fields)
		if (field.name == field_name)
			return field.value;
	return nullptr;
}

bool student_from_json(Student& student, JsonObject* json) {
	if (json->type != JsonObjectType::Object)
		return false;

	JsonObject* field = find_field(json, "name");
	if (!field || field->type != JsonObjectType::String)
		return false;
	student.name = get<string>(field->value);

	field = find_field(json, "age");
	if (!field || field->type != JsonObjectType::Number)
		return false;
	student.age = get<double>(field->value);

	field = find_field(json, "male");
	if (!field || (field->type != JsonObjectType::True && field->type != JsonObjectType::False))
		return false;
	student.male = field->type == JsonObjectType::True;

	field = find_field(json, "course");
	if (!field || field->type != JsonObjectType::Number)
		return false;
	student.course = get<double>(field->value);

	field = find_field(json, "grade");
	if (!field || field->type != JsonObjectType::Number)
		return false;
	student.grade = get<double>(field->value);

	return true;
}

JsonObject* json_from_student(const Student& student) {
	JsonObject* json = create_object();

	add_field(json, "name", create_string(student.name));
	add_field(json, "age", create_number(student.age));
	add_field(json, "male", create_bool(student.male));
	add_field(json, "course", create_number(student.course));
	add_field(json, "grade", create_number(student.grade));

	return json;
}

bool parse_students(JsonObject* json, vector<Student>& students, int& course) {
	if (!json)
		return false;

	JsonObject* n = find_field(json, "n");
	if (!n || n->type != JsonObjectType::Number)
		return false;

	course = get<double>(n->value);

	JsonObject* array = find_field(json, "students");
	if (!array || array->type != JsonObjectType::Array)
		return false;

	for (auto& field : array->fields) {
		Student student;
		if (!student_from_json(student, field.value))
			return false;

		students.push_back(student);
	}

	return true;
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

JsonObject* solve(vector<Student>& students, int course) {
	JsonObject* json = create_object();
	JsonObject* array = create_array();
	add_field(json, "students", array);

	double avg = count_avg_grade(students, course);
	add_field(json, "avg", create_number(avg));

	for (auto& student : students) {
		if (student.course != course)
			continue;

		if (student.grade <= avg)
			continue;

		add_value(array, json_from_student(student));
	}

	return json;
}