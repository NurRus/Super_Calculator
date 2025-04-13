// controller.cpp
#include "controller.h"

Controller::Controller(CALC_Model *calc_model, MainWindow *view)
    : calc_model(calc_model), view(view) {
  connect(view, &MainWindow::pushButton_equals_clicked, this,
          &Controller::onPushButtonEqualsClicked);
  connect(view, &MainWindow::pushButton_graf_clicked, this,
          &Controller::onPushButtonGrafClicked);
  connect(view, &MainWindow::pushButton_credit_clicked, this,
          &Controller::onPushButtonCreditClicked);
}

void Controller::onPushButtonEqualsClicked() {
  std::string expr = view->getResultShowText().toStdString();
  std::string argument = view->getXShowText().toStdString();

  QString message;
  // Используем существующий объект model
  calc_model->calculation(expr, argument);
  // код ошибки
  CALC_Model::ErrorCode err = calc_model->getError();

  if (err != CALC_Model::ERROR_NO_ERROR) {
    message = QString::fromStdString(calc_model->getErrorMessage(err));
  } else {
    double y = calc_model->getResult();
    // Преобразуем double в QString с 7 знаками после запятой
    message = QString::number(y, 'f', 7);
  }
  view->insertText(message);
}

void Controller::onPushButtonGrafClicked() {
  double x_min, x_max, y_min, y_max;
  double h = 0.01;
  double X = 0;
  double Y = 0;
  QVector<double> x, y;
  int N = 0;

  QCustomPlot *customPlot = view->getCustomPlot();
  customPlot->clearGraphs();
  x.clear();
  y.clear();

  x_min = view->getXminShowText().toDouble();
  x_max = view->getXmaxShowText().toDouble() + h;
  y_min = view->getYminShowText().toDouble();
  y_max = view->getYmaxShowText().toDouble();

  customPlot->xAxis->setRange(x_min - h, x_max + h);
  customPlot->yAxis->setRange(y_min - h, y_max + h);

  std::string expr = view->getResultShowText().toStdString();
  X = x_min;
  std::string arg = std::to_string(X);

  calc_model->calculation(expr, arg);
  CALC_Model::ErrorCode err;

  while (X <= x_max) {
    arg = std::to_string(X);
    Y = calc_model->getResult(arg);
    err = calc_model->getError();
    if (err > 0) {
      if (N > 0) {
        customPlot->addGraph();
        customPlot->graph(0)->addData(x, y);
        customPlot->replot();
      }
      x.clear();
      y.clear();
      N = 0;
      X += h;
      arg = std::to_string(X);
      calc_model->calculation(expr, arg);
    } else {
      y.push_back(Y);
      x.push_back(X);
      if (N == 0) N = 1;
      X += h;
    }
  }

  customPlot->addGraph();
  customPlot->graph(0)->addData(x, y);
  customPlot->replot();
}

void Controller::onPushButtonCreditClicked() {
  // Реализация обработки нажатия кнопки "кредит"
}