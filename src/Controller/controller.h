// controller.h
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector>
#include <string>

#include "calc_model.h"
#include "mainwindow.h"

class Controller : public QObject {
  Q_OBJECT

 public:
  Controller(CALC_Model *calc_model, MainWindow *view);

 public slots:

  void onPushButtonEqualsClicked();
  void onPushButtonGrafClicked();
  void onPushButtonCreditClicked();

 private:
  CALC_Model *calc_model;
  MainWindow *view;
};

#endif  // CONTROLLER_H
