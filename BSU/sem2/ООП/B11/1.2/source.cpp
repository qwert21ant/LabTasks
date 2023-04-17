#include "header.h"

int select() {
	cout << "Select mode (1 - generate f & g files, 2 - read files, 3 - solve task): ";

	int mode = 0;
	cin >> mode;
	while (mode < 1 || mode > 3) {
		cout << "Incorrect. Try again: ";
		cin >> mode;
	}

	return mode;
}

bool input(ifstream& f, ifstream& g, ofstream& out) {
	f.open("f.bin", ios::binary);
	if (!f) {
		cout << "Unable to open f.bin" << endl;
		return false;
	}

	g.open("g.bin", ios::binary);
	if (!f) {
		cout << "Unable to open f.bin" << endl;
		return false;
	}

	out.open("out.bin", ios::binary);
	if (!f) {
		cout << "Unable to open f.bin" << endl;
		return false;
	}

	return true;
}

double read_value(istream& in) {
	double value;
	in.read((char*) &value, sizeof(value));

	return value;
}

void write_value(ostream& out, double value) {
	char* arr = (char*) &value;
	out.write(arr, sizeof(value));
}

void write_file(ostream& out, const vector<double>& vec) {
	for (auto& value : vec)
		write_value(out, value);
}

void read_file(istream& in, vector<double>& vec) {
	double value = read_value(in);
	while (in) {
		vec.push_back(value);
		value = read_value(in);
	}
}

void generate_test(int len, vector<double>& vec1, vector<double>& vec2) {
	while (len--) {
		double value = (rand() % 10000) / 100.;
		vec1.push_back(value);
		if (rand() % 2)
			vec2.push_back(value);
	}

	for(int i = 0; i < 5; i++)
		vec2.push_back((rand() % 10000) / 100.);

	sort(vec1.begin(), vec1.end());
	sort(vec2.begin(), vec2.end());
}

void print_vector(const vector<double>& vec) {
	for (auto& value : vec)
		cout << value << " ";
	cout << endl;
}

void generate() {
	int len = 0;
	cout << "Enter array length: ";
	cin >> len;

	vector<double> vec_f, vec_g;
	generate_test(len, vec_f, vec_g);

	ofstream f("f.bin", ios::binary);
	if (f) {
		cout << "f: ";
		print_vector(vec_f);

		write_file(f, vec_f);
	}
	else
		cout << "Unable to open f.bin" << endl;

	ofstream g("g.bin", ios::binary);
	if (g) {
		cout << "g: ";
		print_vector(vec_g);

		write_file(g, vec_g);
	}
	else
		cout << "Unable to open g.bin" << endl;
}

void read_files() {
	ifstream f("f.bin", ios::binary);
	if (f) {
		vector<double> vec_f;
		read_file(f, vec_f);

		cout << "f: ";
		print_vector(vec_f);
	}
	else
		cout << "Unable to open f.bin" << endl;

	ifstream g("g.bin", ios::binary);
	if (g) {
		vector<double> vec_g;
		read_file(g, vec_g);

		cout << "g: ";
		print_vector(vec_g);
	}
	else
		cout << "Unable to open g.bin" << endl;

	ifstream out("out.bin", ios::binary);
	if (out) {
		vector<double> vec_out;
		read_file(out, vec_out);

		cout << "out: ";
		print_vector(vec_out);
	}
	else
		cout << "Unable to open out.bin" << endl;
}

void solve() {
	ifstream f("f.bin", ios::binary);
	ifstream g("g.bin", ios::binary);
	ofstream out("out.bin", ios::binary);

	if (!f) cout << "Unable to open f.bin" << endl;
	if (!g) cout << "Unable to open g.bin" << endl;
	if (!out) cout << "Unable to open out.bin" << endl;

	if (!f || !g || !out) return;

	double f_val, g_val;
	f_val = read_value(f);
	g_val = read_value(g);

	while (f) {
		while (g && f_val > g_val)
			read_value(g);
		if (f_val != g_val)
			write_value(out, f_val);
		f_val = read_value(f);
	}
}