#include "header.h"

enum Expect {
	Digit = 1,
	Sign  = 2,
	Point = 4,
	E     = 8,
	End   = 16
};

enum Part {
	A = 1, // before point
	B = 2, // after point, before e
	C = 3  // after e
};

bool is_int(string str) {
	bool res = false;

	char expect = Expect::Sign | Expect::Digit;
	for (char ch : str) {
		if (isdigit(ch) && expect & Expect::Digit) {
			expect = Expect::Digit | Expect::End;
			res = true;
		} else if(ch == '-' && expect & Expect::Sign){
			expect = Expect::Digit;
		} else {
			res = false;
			break;
		}
	}

	if (!(expect & Expect::End))
		res = false;

	return res;
}

bool is_float(string str) {
	bool res = false;

	char part = Part::A;
	char expect = Expect::Digit | Expect::Sign | Expect::Point;

	for (char ch : str) {
		if (isdigit(ch) && expect & Expect::Digit) {
			if (part == Part::A) {
				expect = Expect::Digit | Expect::Point | Expect::E;
				res = true;
			}
			else if (part == Part::B) {
				expect = Expect::Digit | Expect::E | Expect::End;
				res = true;
			}
			else {
				expect = Expect::Digit | Expect::End;
				res = true;
			}
		}
		else if (ch == '-' && expect & Expect::Sign) {
			expect = Expect::Digit;
		}
		else if (ch == '.' && expect & Expect::Point) {
			part = Part::B;
			expect = Expect::Digit | Expect::End;
		}
		else if ((ch == 'e' || ch == 'E') && expect & Expect::E) {
			part = Part::C;
			expect = Expect::Digit | Expect::Sign;
		}
		else {
			res = false;
			break;
		}
	}

	if (!(expect & Expect::End))
		res = false;

	return res;
}