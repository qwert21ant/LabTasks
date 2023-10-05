#include "NewtonSolver.hpp"

#include "../Z1/GaussSolver.hpp"

bool NewtonSolver::kDebug = true;
int NewtonSolver::nMaxIter = 100;
double NewtonSolver::eps1 = 1e-6;
double NewtonSolver::eps2 = 1e-6;
double NewtonSolver::kM = 0.01;

Matrix evalMatrix(NewtonSolver::FuncMatrixType mat, NewtonSolver::ArgType X) {
	Matrix res(mat.size(), mat.size());

	for (int i = 0; i < res.getNRows(); i++) {
		for (int j = 0; j < res.getNCols(); j++) {
			res.get(i, j) = mat[i][j](X);
		}
	}

	return res;
}

Matrix evalSystem(NewtonSolver::FuncSystemType system, NewtonSolver::ArgType X) {
	Matrix res(system.size(), 1);

	for (int i = 0; i < res.getNRows(); i++) {
		res.get(i, 0) = system[i](X);
	}

	return res;
}

double countDelta(Matrix Xnext, Matrix Xprev) {
	double res = 0;

	for (int i = 0; i < Xnext.getNRows(); i++) {
		if (abs(Xnext.get(i, 0)) < 1) {
			res = max(res, abs(Xnext.get(i, 0) - Xprev.get(i, 0)));
		} else {
			res = max(res, abs((Xnext.get(i, 0) - Xprev.get(i, 0)) / Xnext.get(i, 0)));
		}
	}

	return res;
}

Matrix countJ(NewtonSolver::FuncSystemType system, NewtonSolver::ArgType X, double M) {
	Matrix J(system.size(), system.size());

	for (int j = 0; j < J.getNCols(); j++) {
		double dx = M * X.get(j, 0);

		Matrix Xj = X;
		Xj.get(j, 0) += dx;

		Matrix Ft = evalSystem(system, Xj);
		Matrix F = evalSystem(system, X);

		for (int i = 0; i < J.getNRows(); i++) {
			J.get(i, j) = (Ft.get(i, 0) - F.get(i, 0)) / dx;
		}
	}

	return J;
}

Matrix NewtonSolver::solveWithJ(FuncSystemType system, ArgType X0, FuncMatrixType Jm) {
	int nIter = 1;
	double delta1 = 0;
	double delta2 = 0;

	Matrix X = X0;

	if (kDebug) {
		cout << "+------------+------------+------------+" << endl;
		cout << "|    iter    |   delta1   |   delta2   |" << endl;
		cout << "+------------+------------+------------+" << endl;
	}

	do {
		Matrix F = evalSystem(system, X);
		Matrix J = evalMatrix(Jm, X);

		Matrix dX;

		try {
			dX = GaussSolver::solve(ExMatrix(J, -F));
		} catch(exception e) {
			cout << "Caught exception: " << e.what() << endl;
			throw;
		}

		Matrix Xnext = X + dX;

		delta1 = F.norm();
		delta2 = countDelta(Xnext, X);

		X = Xnext;

		if (kDebug) {
			cout << "| " << setw(10) << nIter;
			cout << " | " << setw(10) << setprecision(6) << delta1;
			cout << " | " << setw(10) << setprecision(6) << delta2 << " |" << endl;
		}

		nIter++;
	} while (nIter <= nMaxIter && (delta1 > eps1 || delta2 > eps2));
	
	return X;
}

Matrix NewtonSolver::solve(FuncSystemType system, ArgType X0) {
	int nIter = 1;
	double delta1 = 0;
	double delta2 = 0;

	Matrix X = X0;

	if (kDebug) {
		cout << "+------------+------------+------------+" << endl;
		cout << "|    iter    |   delta1   |   delta2   |" << endl;
		cout << "+------------+------------+------------+" << endl;
	}

	do {
		Matrix F = evalSystem(system, X);
		Matrix J = countJ(system, X, kM);

		Matrix dX;

		try {
			dX = GaussSolver::solve(ExMatrix(J, -F));
		}
		catch (exception e) {
			cout << "Caught exception: " << e.what() << endl;
			throw;
		}

		Matrix Xnext = X + dX;

		delta1 = F.norm();
		delta2 = countDelta(Xnext, X);

		X = Xnext;

		if (kDebug) {
			cout << "| " << setw(10) << nIter;
			cout << " | " << setw(10) << setprecision(6) << delta1;
			cout << " | " << setw(10) << setprecision(6) << delta2 << " |" << endl;
		}

		nIter++;
	} while (nIter <= nMaxIter && (delta1 > eps1 || delta2 > eps2));

	return X;
}