#include "Test.h"

namespace Test {
	string single_test(string test) {
		try {
			istringstream ss(test);
			IExpression* exp = expression(ss);

			string res = print_val(exp->calc());
			delete_expression(exp);
			return res;
		}
		catch (...) {
			return string("error");
		}
	}

	bool run_tests_rec(ostream& out, JsonObject* json, int depth) {
		if (!is_object(json))
			throw;

		string offset(2 * depth, ' ');

		string group_name;
		JsonObject* jGroup = Json::get_field(json, "group");
		if (is_string(jGroup))
			group_name = std::get<string>(jGroup->value);

		if (group_name != "")
			out << offset << "Group \"" << group_name << "\":\n";

		JsonObject* jTests = Json::get_field(json, "tests");
		if (!is_array(jTests))
			return true;

		bool result = true;

		for (auto& field : jTests->fields) {
			JsonObject* jTest = field.value;

			if (!is_object(jTest))
				continue;

			if (get_field(jTest, "tests")) {
				result = result && run_tests_rec(out, jTest, depth + 1);
				continue;
			}

			JsonObject* jTestString = get_field(jTest, "test");
			JsonObject* jExpectedString = get_field(jTest, "expected");

			if (!is_string(jTestString) || !is_string(jExpectedString))
				continue;

			string test = get<string>(jTestString->value);
			string expected = get<string>(jExpectedString->value);

			string res = single_test(test);

			if (res == expected) {
				out << offset << "  [ OK ] " << test << "\n";
			}
			else {
				out << offset << "  [FAIL] " << test << "\n";
				out << offset << "  Expected: " << expected << "\n";
				out << offset << "       Get: " << res << "\n";
				result = false;
			}
		}

		if (result)
			out << offset << "Group tests passed\n";
		else
			out << offset << "Group tests failed\n";

		return result;
	}

	void run_tests(ostream& out, JsonObject* json) {
		try {
			run_tests_rec(out, json, 0);
		}
		catch (...) {
			out << "Incorrect json\n";
		}
	}
};