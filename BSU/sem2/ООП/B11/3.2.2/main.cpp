#include "header.h"

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