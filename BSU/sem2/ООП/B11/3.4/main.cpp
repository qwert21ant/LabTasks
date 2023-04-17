#include "header.h"

int main() {
	int mode = 0;
	while (mode != 1 && mode != 2) {
		cout << "Select mode (1 - testing, 2 - run): ";
		cin >> mode;
	}

	if (mode == 1) {

		string fname;
		cout << "Enter test's file name: "; // tests.json
		cin >> fname;

		try {
			ifstream fin(fname);

			if (!fin.is_open()) {
				cout << "Unable to open file" << endl;
				return 0;
			}

			Json::JsonObject* json = Json::read_json(fin);

			Test::run_tests(cout, json);
		}
		catch (exception e) {
			cout << e.what() << endl;
		}
	}
	else {
		string str_expr;
		cout << "Enter expression: ";
		cin.ignore();
		getline(cin, str_expr);

		istringstream ss(str_expr);

		try {
			Expression::IExpression* exp = Expression::expression(ss);

			cout << "Expression: " << exp->print() << endl;
			cout << "Result: ";
			cout << print_val(exp->calc());
			cout << endl;

			delete_expression(exp);
		}
		catch (exception e) {
			cout << e.what() << endl;
		}
	}
	
	return 0;
}