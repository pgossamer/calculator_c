#include "mainwindow.h"

#include "ui_mainwindow.h"

extern "C" double s21_smart_calc(char *str_s, double x);
extern "C" int validation(char *str);
extern "C" int are_you_have_x(char *str);
extern "C" int len_str(char *str);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_clear, SIGNAL(released()), this,
          SLOT(on_pushButton_clear_clicked()));
  connect(ui->pushButton_cos, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_sin, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_tan, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_acos, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_asin, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_atan, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_ln, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_log, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_minus, SIGNAL(released()), this,
          SLOT(digit_pressed()));
  connect(ui->pushButton_plus, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_div, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_mul, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_point, SIGNAL(released()), this,
          SLOT(digit_pressed()));
  connect(ui->pushButton_mod, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_sqrt, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_ck_o, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_ck_z, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_x, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_e, SIGNAL(released()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_stepen, SIGNAL(released()), this,
          SLOT(digit_pressed()));
  connect(ui->pushButton_res, SIGNAL(released()), this,
          SLOT(digit_result_pressed()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digit_pressed() {
  ui->widget->clearGraphs();
  ui->widget->replot();
  QPushButton *button = (QPushButton *)sender();

  _stringPrint.push_back(button->text());
  if (button->text() == "sin" || button->text() == "cos" ||
      button->text() == "tan" || button->text() == "sqrt" ||
      button->text() == "asin" || button->text() == "acos" ||
      button->text() == "atan" || button->text() == "log" ||
      button->text() == "ln" || button->text() == "mod") {
    _stringPrint.push_back("(");
  }
  ui->label->setText(_stringPrint);
  transformStringToChar(button->text());
}

void MainWindow::on_pushButton_clear_clicked() {
  _stringPrint.clear();
  ui->label->clear();
  _stringCalculate.clear();
  ui->widget->clearGraphs();
  ui->widget->replot();
}

void MainWindow::digit_result_pressed() {
  QByteArray str_bit = _stringCalculate.toLocal8Bit();
  char *res_str = str_bit.data();
  int error = validation(res_str);
  int len = len_str(res_str);
  if (error != 1 && len) {
    double x = ui->doubleSpinBox_just_x->value();
    double res = s21_smart_calc(res_str, x);
    QString res_s = QString::number(res, 'g', 7);
    ui->label->setText(res_s);
  } else {
    ui->label->setText("TRY AGAIN");
  }
  ui->doubleSpinBox_just_x->clear();
  _stringPrint.clear();
  _stringCalculate.clear();
}

void MainWindow::transformStringToChar(QString giveString) {
  if (giveString == "cos") {
    _stringCalculate.push_back("c(");
  } else if (giveString == "sin") {
    _stringCalculate.push_back("s(");
  } else if (giveString == "tan") {
    _stringCalculate.push_back("t(");
  } else if (giveString == "acos") {
    _stringCalculate.push_back("#(");
  } else if (giveString == "asin") {
    _stringCalculate.push_back("$(");
  } else if (giveString == "atan") {
    _stringCalculate.push_back("!(");
  } else if (giveString == "mod") {
    _stringCalculate.push_back("m(");
  } else if (giveString == "ln") {
    _stringCalculate.push_back("n(");
  } else if (giveString == "log") {
    _stringCalculate.push_back("g(");
  } else if (giveString == "sqrt") {
    _stringCalculate.push_back("q(");
  } else {
    _stringCalculate.push_back(giveString);
  }
}

void MainWindow::on_pushButton_stroit_graf_clicked() {
  QByteArray str_bit = _stringCalculate.toLocal8Bit();
  char *res_str = str_bit.data();

  int error = validation(res_str);
  int len = len_str(res_str);
  int have_x = are_you_have_x(res_str);

  if (!error && len && have_x) {
    ui->widget->clearGraphs();
    double x_min = ui->doubleSpinBox_x_min->value();
    double x_max = ui->doubleSpinBox_x_max->value();
    double y_min = ui->doubleSpinBox_y_min->value();
    double y_max = ui->doubleSpinBox_y_max->value();
    ui->widget->xAxis->setRange(x_min, x_max);
    ui->widget->yAxis->setRange(y_min, y_max);
    double h;
    if (x_min > -1000 && x_max < 1000 && y_min > -1000 && y_max < 1000)
      h = 0.006;
    else if (x_min > -10000 && x_max < 10000 && y_min > -10000 && y_max < 10000)
      h = 0.009;
    else
      h = 0.68;
    double y_tmp = 0.0;

    for (double i = x_min; i < x_max; i += h) {
      y_tmp = s21_smart_calc(res_str, i);
      if (y_tmp > y_min && y_tmp < y_max) {
        x.push_back(i);
        y.push_back(y_tmp);
      }
    }
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen(Qt::black));
    ui->widget->graph(0)->addData(x, y);
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssDisc, 2));
    ui->widget->replot();
    x.clear();
    y.clear();
  } else {
    ui->label->setText("TRY AGAIN");
  }
  ui->label->clear();
  _stringPrint.clear();
  _stringCalculate.clear();
}
