#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString _stringPrint;
    QString _stringCalculate;
    QVector<double> x, y;

    void transformStringToChar(QString);

private slots:
    void digit_pressed();

    void on_pushButton_clear_clicked();

    void digit_result_pressed();
    void on_pushButton_stroit_graf_clicked();
};
#endif // MAINWINDOW_H
