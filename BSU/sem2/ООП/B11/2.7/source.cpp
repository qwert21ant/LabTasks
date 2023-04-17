#include "header.h"

void gen_rand(Matrix<Complex>& mat, int max_val) {
	for (int i = 0; i < mat.get_cols(); i++) {
		for (int j = 0; j < mat.get_rows(); j++) {
			mat[i][j] = Complex::Rand(max_val);
		}
	}
}