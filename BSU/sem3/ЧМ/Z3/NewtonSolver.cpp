#include "NewtonSolver.hpp"

#include "../Z1/GaussSolver.hpp"

bool NewtonSolver::kDebug = true;
int NewtonSolver::nMaxIter = 100;
double NewtonSolver::eps1 = 1e-6;
double NewtonSolver::eps2 = 1e-6;
double NewtonSolver::kM = 0.01;

Matrix evalMatrix(const FuncMatrixType& mat, const DoubleData& X) {
	Matrix res(mat.size(), mat.size());

	for (int i = 0; i < res.getNRows(); i++) {
		for (int j = 0; j < res.getNCols(); j++) {
			res.get(i, j) = mat[i][j]->calc(X);
		}
	}

	return res;
}

Matrix funcArgsToMatrix(const DoubleData& x) {
	Matrix res(x.size(), 1);

	for (int i = 0; i < x.size(); ++i) {
		res.get(i, 0) = x[i];
	}

	return res;
}

DoubleData matrixToFuncArgs(const Matrix& mat) {
	DoubleData res(mat.getNRows());

	for (int i = 0; i < mat.getNRows(); ++i) {
		res[i] = mat.get(i, 0);
	}

	return res;
}

DoubleData addFuncArgs(const DoubleData& a, const DoubleData& b) {
	DoubleData res(a.size());

	for (int i = 0; i < a.size(); ++i) {
		res[i] = a[i] + b[i];
	}

	return res;
}

double countDelta(const DoubleData& Xnext, const DoubleData& Xprev) {
	double res = 0;

	for (int i = 0; i < Xnext.size(); i++) {
		if (abs(Xnext[i]) < 1) {
			res = max(res, abs(Xnext[i] - Xprev[i]));
		} else {
			res = max(res, abs((Xnext[i] - Xprev[i]) / Xnext[i]));
		}
	}

	return res;
}

Matrix countJ(const FuncSystemType& system, const DoubleData& X, double M) {
	Matrix J(system.size(), system.size());

	for (int j = 0; j < J.getNCols(); j++) {
		double dx = M * X[j];

		DoubleData Xj = X;
		Xj[j] += dx;

		DoubleData Ft = IFunction::evalSystem(system, Xj);
		DoubleData F = IFunction::evalSystem(system, X);

		for (int i = 0; i < J.getNRows(); i++) {
			J.get(i, j) = (Ft[i] - F[i]) / dx;
		}
	}

	return J;
}

Matrix NewtonSolver::solveWithJ(const FuncSystemType& system, const DoubleData& X0, const FuncMatrixType& Jm) {
	int nIter = 1;
	double delta1 = 0;
	double delta2 = 0;

	DoubleData X = X0;

	if (kDebug) {
		cout << "+------------+------------+------------+" << endl;
		cout << "|    iter    |   delta1   |   delta2   |" << endl;
		cout << "+------------+------------+------------+" << endl;
	}

	do {
		DoubleData F = IFunction::evalSystem(system, X);
		Matrix J = evalMatrix(Jm, X);

		DoubleData dX;

		try {
			dX = matrixToFuncArgs(GaussSolver::solve(ExMatrix(J, -funcArgsToMatrix(F))));
		} catch(exception e) {
			cout << "Caught exception: " << e.what() << endl;
			throw;
		}

		DoubleData Xnext = addFuncArgs(X, dX);

		delta1 = funcArgsToMatrix(F).norm();
		delta2 = countDelta(Xnext, X);

		X = Xnext;

		if (kDebug) {
			cout << "| " << setw(10) << nIter;
			cout << " | " << setw(10) << setprecision(6) << delta1;
			cout << " | " << setw(10) << setprecision(6) << delta2 << " |" << endl;
		}

		nIter++;
	} while (nIter <= nMaxIter && (delta1 > eps1 || delta2 > eps2));
	
	return funcArgsToMatrix(X);
}

Matrix NewtonSolver::solve(const FuncSystemType& system, const DoubleData& X0) {
	int nIter = 1;
	double delta1 = 0;
	double delta2 = 0;

	DoubleData X = X0;

	if (kDebug) {
		cout << "+------------+------------+------------+" << endl;
		cout << "|    iter    |   delta1   |   delta2   |" << endl;
		cout << "+------------+------------+------------+" << endl;
	}

	do {
		DoubleData F = IFunction::evalSystem(system, X);
		Matrix J = countJ(system, X, kM);

		DoubleData dX;

		try {
			dX = matrixToFuncArgs(GaussSolver::solve(ExMatrix(J, -funcArgsToMatrix(F))));
		}
		catch (exception e) {
			cout << "Caught exception: " << e.what() << endl;
			throw;
		}

		DoubleData Xnext = addFuncArgs(X, dX);

		delta1 = funcArgsToMatrix(F).norm();
		delta2 = countDelta(Xnext, X);

		X = Xnext;

		if (kDebug) {
			cout << "| " << setw(10) << nIter;
			cout << " | " << setw(10) << setprecision(6) << delta1;
			cout << " | " << setw(10) << setprecision(6) << delta2 << " |" << endl;
		}

		nIter++;
	} while (nIter <= nMaxIter && (delta1 > eps1 || delta2 > eps2));

	return funcArgsToMatrix(X);
}