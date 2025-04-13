// main.cpp
#include <QApplication>

#include "calc_model.h"
#include "controller.h"
#include "mainwindow.h"
#include "qcustomplot.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  CALC_Model calc_model;
  MainWindow view;
  Controller controller(&calc_model, &view);

  view.setController(&controller);
  view.show();

  return a.exec();
}
