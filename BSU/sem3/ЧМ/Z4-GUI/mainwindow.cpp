#include "mainwindow.h"

#include <iostream>
#include <vector>

#include "../Z4/LSApprox.hpp"

using namespace std;

QVector<double> vecToQVec(const vector<double>& vec) {
  QVector<double> qvec(vec.size());

  for (int i = 0; i < vec.size(); ++i) {
    qvec[i] = vec[i];
  }

  return qvec;
}

double calcPoly(const vector<double>& coefs, double x) {
  if (coefs.empty()) {
    throw LSApprox::InvalidArgument();
  }

  size_t nCoefs = coefs.size();

  double res = coefs[0];
  double curX = x;

  for (int i = 1; i < nCoefs; ++i) {
    res += coefs[i] * curX;
    curX *= x;
  }

  return res;
}

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent) {
  setFixedSize(600, 400);
  setWindowTitle("Приближение функции МНК");

  vector<double> x = { 2.4, 3.5, 5.0, 6.89, 10.0 };
  vector<double> y = { 0.0141, 0.0281, 0.0562, 0.1125, 0.225 };
  vector<double> coefs;

  try {
    coefs = LSApprox::findCoef(x, y, 2);
    cout << "All coefficients: " << coefs[0] << ", " << coefs[1] << ", " << coefs[2] << endl;
    cout << "Solution: P = " << coefs[0] << " + " << coefs[2] << " * v^2" << endl;

    double dev = LSApprox::countDeviation(x, y, coefs);
    cout << "Deviation: " << dev << endl;
  } catch (exception e) {
    cout << "Error: ";
    cout << e.what() << endl;

    return;
  }

  vector<double> x1(x.size() * 2);
  vector<double> y1(x1.size());

  for (int i = 0; i < x1.size(); ++i) {
    x1[i] = i * 10. / (x1.size() - 1);
    y1[i] = calcPoly(coefs, x1[i]);
  }

  QCustomPlot* plot = new QCustomPlot(this);

  this->setCentralWidget(plot);

  plot->addGraph();
  plot->graph(0)->setData(vecToQVec(x), vecToQVec(y));
  plot->graph(0)->setLineStyle(QCPGraph::lsNone);
  plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue, 7));
  plot->graph(0)->setName("Исходные значения");

  plot->addGraph();
  plot->graph(1)->setData(vecToQVec(x1), vecToQVec(y1));
  plot->graph(1)->setPen(QPen(Qt::red));
  plot->graph(1)->setName("Аппроксимация");

  plot->legend->setVisible(true);

  plot->xAxis->setLabel("x");
  plot->xAxis->setRange(x[0], x.back());

  plot->yAxis->setLabel("y");
  plot->yAxis->setRange(0, 0.3);

  plot->replot();
}

MainWindow::~MainWindow() {}
