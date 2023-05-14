#include "header.h"

inline void ignore_line() {
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

const string fname = "tasklist.json";

int main() {
	srand(time(0));

	ifstream fin(fname);

	if (!fin.is_open()) {
		cout << "Unable to open file. Trying create file." << endl;
		ofstream fout(fname);

		fout << "{}";

		fout.close();

		fin.open(fname);
	}

	if (!fin.is_open()) {
		cout << "Unable to open file" << endl;
		return 0;
	}

	JsonObject* json = nullptr;
	try {
		json = read_json(fin);
	} catch (JsonException e) {
		cout << e.what() << endl;
		return 0;
	} catch (...) {
		cout << "Something went wrong" << endl;
		return 0;
	}

	fin.close();

	TaskList tl = TaskList::fromJSON(json);

	print_usage();

	string command = "";
	while (true) {
		cout << ">> ";
		cin >> command;
		ignore_line();

		if (command == "generate") {
			cout << "   amount: ";

			int amount;
			cin >> amount;
			ignore_line();

			if (cin.fail()) {
				cout << "Incorrect input" << endl;
				cin.clear();
				ignore_line();
				continue;
			}

			if (amount < 1) {
				cout << "Incorrect input" << endl;
				continue;
			}

			for (int i = 0; i < amount; i++)
				tl.append(gen_task());

			cout << "Generated " << amount << " tasks" << endl;
		}
		else if (command == "remove") {
			cout << "   index: ";

			int index;
			cin >> index;
			ignore_line();

			if (cin.fail()) {
				cout << "Incorrect input" << endl;
				cin.clear();
				ignore_line();
				continue;
			}

			if (index < 0 || index >= tl.size()) {
				cout << "Incorrect input" << endl;
				continue;
			}

			tl.remove(index);

			cout << index << "-nth task removed" << endl;
		}
		else if (command == "clear") {
			tl.clear();
			cout << "All tasks removed" << endl;
		}
		else if (command == "print") {
			cout << tl;
		}
		else if (command == "exit")
			break;
		else
			cout << "Unknown command" << endl;
	}

	JsonObject* output = tl.toJSON();

	ofstream fout(fname);

	if (!fout.is_open()) {
		cout << "Unable open file for writing" << endl;
		return 0;
	}

	print_json(fout, output);

	return 0;
}