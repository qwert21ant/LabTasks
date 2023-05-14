#include "header.h"

#include <stack>

const bool LOG = false;

ostream& operator <<(ostream& out, const Cycle& c) {
	if (c.type == CycleType::Do)
		out << "do";
	else if (c.type == CycleType::For)
		out << "for";
	else if (c.type == CycleType::While)
		out << "while";
	else
		out << "none";

	out << ": " << c.beginInd << " - " << c.endInd;
	return out;
}

struct MyStream {
	istream& in;
	char prev;
	char cur;
	int line;

	void next() {
		prev = cur;
		cur = in.get();

		if (LOG) if (cur != EOF) cout << cur;
	}
};

bool check_word(MyStream& ms, string str) {
	if (isalpha(ms.prev) || ms.prev == '_')
		return false;

	for (char ch : str) {
		if (ms.cur != ch)
			return false;

		ms.next();
	}

	if (isalpha(ms.cur))
		return false;

	return true;
}

void read_till(MyStream& ms, string str) {
	bool is_string = false;
	bool is_comment = false;
	bool is_line_comment = false;

	while (!ms.in.eof()) {
		if (ms.cur == '\n') {
			ms.line++;
			is_line_comment = false;
		}
		else if (ms.cur == '\"' && ms.prev != '\\') {
			if (!is_string)
				is_string = true;
			else
				is_string = false;
		}
		else if (ms.cur == '/' && ms.prev == '/') {
			is_line_comment = true;
		}
		else if (ms.cur == '*' && ms.prev == '/') {
			is_comment = true;
		}
		else if (ms.cur == '/' && ms.prev == '*') {
			is_comment = false;
		}
		else {
			if (!is_string && !is_line_comment && !is_comment && str.find(ms.cur) != string::npos)
				return;
		}

		ms.next();
	}
}

void skip_brace(MyStream& ms) {
	int cntr = 0;
	do {
		read_till(ms, "()");

		if (LOG) cout << "[meet brace]";

		if (ms.cur == '(') {
			cntr++;
		}
		else {
			cntr--;
		}

		ms.next();
	} while (cntr);
}

vector<Cycle> get_cycles(istream& in) {
	vector<Cycle> res;

	stack<Cycle> stack;

	MyStream ms{ in, 0, 0, 1 };

	CycleType last_cycle = CycleType::None;
	int cycle_begin = 0;

	bool skip_next_while = false;

	while (true) {
		read_till(ms, "wdf{};");

		if (in.eof())
			break;

		if (ms.cur == ';') {
			if (last_cycle != CycleType::None) {
				res.push_back({ last_cycle, cycle_begin, ms.line });

				last_cycle = CycleType::None;
			}

			ms.next();
		}
		else if (ms.cur == '{') {
			if (LOG) cout << "[meet {]";

			stack.push({ last_cycle, cycle_begin, 0 });
			last_cycle = CycleType::None;
			cycle_begin = 0;

			ms.next();
		}
		else if (ms.cur == '}') {
			if (LOG) cout << "[meet }]";

			Cycle c = stack.top();
			if (LOG) cout << "[" << c << "]";

			if (c.type != CycleType::None) {
				c.endInd = ms.line;
				res.push_back(c);

				if (c.type == CycleType::Do)
					skip_next_while = true;
			}

			stack.pop();

			ms.next();
		}
		else if (check_word(ms, "do")) {
			last_cycle = CycleType::Do;
			cycle_begin = ms.line;
		}
		else if (check_word(ms, "while")) {
			if (skip_next_while) {
				skip_next_while = false;
				continue;
			}

			if (LOG) cout << "[while]";

			last_cycle = CycleType::While;
			cycle_begin = ms.line;

			skip_brace(ms);

			if (LOG) cout << "[after braces]";
		}
		else if (check_word(ms, "for")) {
			last_cycle = CycleType::For;
			cycle_begin = ms.line;

			skip_brace(ms);
		}
		else
			ms.next();
	}

	return res;
}