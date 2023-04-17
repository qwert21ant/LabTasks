#include "header.h"

class Test {
public:
	Test() : val(counter++) {};

	Test(const Test&) = default;
	Test& operator =(const Test&) = default;

	Test(Test&&) = default;
	Test& operator =(Test&&) = default;

	~Test() {
		cout << "~" << val << endl;
	}

private:
	int val;
	static int counter;
};

int Test::counter = 0;

int main() {
	srand(time(0));

	int n;
	cout << "Enter matrix size: ";
	cin >> n;

	Matrix<Complex> mat(n, n);
	gen_rand(mat, 10);
	//mat[0][0] = Complex(1, 1);

	cout << mat << endl;

	cout << "Result:" << endl;
	cout << (mat ^ 2) << endl;

	return 0;
}