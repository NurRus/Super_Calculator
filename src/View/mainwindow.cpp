// mainwindow.cpp
#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  activeLabel = ui->result_show;

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_degree, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_abs, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_multiply, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_brackets_open, SIGNAL(clicked()), this,
          SLOT(input_text()));
  connect(ui->pushButton_brackets_close, SIGNAL(clicked()), this,
          SLOT(input_text()));
  connect(ui->pushButton_argument, SIGNAL(clicked()), this, SLOT(input_text()));
  connect(ui->pushButton_AC, SIGNAL(clicked()), this,
          SLOT(pushButton_AC_clicked()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this,
          SLOT(pushButton_X_clicked()));
  connect(ui->pushButton_Xmin, SIGNAL(clicked()), this,
          SLOT(pushButton_Xmin_clicked()));
  connect(ui->pushButton_Xmax, SIGNAL(clicked()), this,
          SLOT(pushButton_Xmax_clicked()));
  connect(ui->pushButton_Ymin, SIGNAL(clicked()), this,
          SLOT(pushButton_Ymin_clicked()));
  connect(ui->pushButton_Ymax, SIGNAL(clicked()), this,
          SLOT(pushButton_Ymax_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setController(QObject *controller) {
  connect(ui->pushButton_equals, SIGNAL(clicked()), controller,
          SLOT(onPushButtonEqualsClicked()));
  connect(ui->pushButton_graf, SIGNAL(clicked()), controller,
          SLOT(onPushButtonGrafClicked()));
  connect(ui->pushButton_credit, SIGNAL(clicked()), controller,
          SLOT(onPushButtonGrafClicked()));
}

QString MainWindow::getResultShowText() const {
  return ui->result_show->text();
}

QString MainWindow::getXShowText() const { return ui->X_show->text(); }

QString MainWindow::getXminShowText() const { return ui->Xmin_show->text(); }

QString MainWindow::getXmaxShowText() const { return ui->Xmax_show->text(); }

QString MainWindow::getYminShowText() const { return ui->Ymin_show->text(); }

QString MainWindow::getYmaxShowText() const { return ui->Ymax_show->text(); }

QCustomPlot *MainWindow::getCustomPlot() const { return ui->graphWidget; }

void MainWindow::input_text() {
  QPushButton *button = (QPushButton *)sender();
  QString buttonText = button->text();
  QString currentText = activeLabel->text();
  if (activeLabel != ui->result_show) {
    QRegularExpression pattern_1("[-0-9.]");
    QRegularExpression pattern_2("[.]");
    if (pattern_1.match(buttonText).hasMatch()) {
      if (buttonText == "." && !pattern_2.match(currentText).hasMatch())
        activeLabel->setText(currentText + ".");
      if (buttonText == "-" && currentText == "0") activeLabel->setText("-");
      if (buttonText != "." && buttonText != "-") {
        if (currentText == "0")
          activeLabel->setText(buttonText);
        else
          activeLabel->setText(currentText + buttonText);
      }
    }
  } else {
    if (currentText == "0" && buttonText != ".")
      activeLabel->setText(buttonText);
    else
      activeLabel->setText(currentText + buttonText);
  }
}

void MainWindow::pushButton_AC_clicked() {
  activeLabel = ui->result_show;
  activeLabel->setText("0");
}

void MainWindow::pushButton_X_clicked() {
  activeLabel = ui->X_show;
  activeLabel->setText("0");
}

void MainWindow::pushButton_Xmin_clicked() {
  activeLabel = ui->Xmin_show;
  activeLabel->setText("0");
}

void MainWindow::pushButton_Xmax_clicked() {
  activeLabel = ui->Xmax_show;
  activeLabel->setText("0");
}

void MainWindow::pushButton_Ymin_clicked() {
  activeLabel = ui->Ymin_show;
  activeLabel->setText("0");
}

void MainWindow::pushButton_Ymax_clicked() {
  activeLabel = ui->Ymax_show;
  activeLabel->setText("0");
}

void MainWindow::insertText(const QString &mess) {
  ui->result_show->setText(mess);
}
