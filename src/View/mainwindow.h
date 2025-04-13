// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  // Доступ к graphWidget
  QCustomPlot* getCustomPlot() const;
  // Методы доступа к элементам интерфейса
  QString getResultShowText() const;
  QString getXShowText() const;
  QString getXminShowText() const;
  QString getXmaxShowText() const;
  QString getYminShowText() const;
  QString getYmaxShowText() const;

  void setController(QObject* controller);
  void insertText(const QString& mess);

 private slots:

  void input_text();
  void pushButton_AC_clicked();
  void pushButton_X_clicked();
  void pushButton_Xmin_clicked();
  void pushButton_Xmax_clicked();
  void pushButton_Ymin_clicked();
  void pushButton_Ymax_clicked();

 signals:

  void pushButton_equals_clicked();
  void pushButton_graf_clicked();
  void pushButton_credit_clicked();

 private:
  Ui::MainWindow* ui;
  QLabel* activeLabel;
};

#endif  // MAINWINDOW_H
