#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void digitClicked();

    void operatorClicked();

    void on_buttonAC_clicked();

    void on_buttonequal_clicked();

    void on_buttonscientific_clicked();

private:
    Ui::Calculator *ui;
    bool div, mul, plus, minus;
    double val1, val;
};
#endif // CALCULATOR_H
