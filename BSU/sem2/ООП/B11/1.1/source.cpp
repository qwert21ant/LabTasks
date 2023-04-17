#include "header.h"

void input(ifstream& f, ifstream& g, ofstream& out) {
	string name;
	do {
		cout << "Enter f file name: ";
		cin >> name;
		f.open(name);
	} while (!f);

	do {
		cout << "Enter g file name: ";
		cin >> name;
		g.open(name);
	} while (!g);

	do {
		cout << "Enter out file name: ";
		cin >> name;
		out.open(name);
	} while (!out);
}

void solve(istream& f, istream& g, ostream& out) {
	double f_val, g_val;
	f >> f_val;
	g >> g_val;

	while (f) {
		while (g && f_val > g_val)
			g >> g_val;
		if (f_val != g_val)
			out << f_val << " ";
		f >> f_val;
	}
}