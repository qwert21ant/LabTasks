#include "header.h"
#include "matrix.h"
#include "complex.h"

template <class T>
void print(const Matrix<T>& mat) {
	auto dim = mat.GetDimensions();
	for (int i = 0; i < dim.first; i++) {
		for (int j = 0; j < dim.second; j++) {
			cout << setw(10) << mat[i][j] << " | ";
		}
		cout << endl;
	}
	cout << endl;
}

template <class T>
void gen_rand(Matrix<T>& mat, int max_val) {
	auto dim = mat.GetDimensions();
	for (int i = 0; i < dim.first; i++) {
		for (int j = 0; j < dim.second; j++) {
			mat[i][j] = rand() % max_val;
		}
	}
}

void gen_rand(Matrix<Complex>& mat, int max_val) {
	auto dim = mat.GetDimensions();
	for (int i = 0; i < dim.first; i++) {
		for (int j = 0; j < dim.second; j++) {
			mat[i][j] = Complex::Rand(max_val);
		}
	}
}

template <class T>
Matrix<T> square(const Matrix<T>& m) {
	return m * m;
}

int main() {
	srand(time(0));

	int n;
	cout << "Enter matrix size: ";
	cin >> n;

	Matrix<Complex> mat(n, n);
	gen_rand(mat, 10);

	print(mat);
	
	cout << "Result:" << endl;
	print(square(mat));
	return 0;
}