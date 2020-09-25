#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QPushButton>

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
    void createButton();

    void digitClicked();

    void specialClicked();

    void operatorClicked();

    void on_buttonAC_clicked();

    void on_buttonequal_clicked();

    void on_buttonscientific_clicked();

    void on_buttonpercent_clicked();

    void on_buttonplus_minus_clicked();

private:
    Ui::Calculator *ui;
    bool div, mul, plus, minus, sc;
    double val1, val;
    QString lab1;
    QPushButton *pblog2, *pbsqrt, *pbfact, *pbinv, *pbpi, *pbsin, *pbcos, *pbtang, *pbexp, *pb10, *pbln, *pbrand, *pbpow2, *pbpow3, *pblog10, *pbE,
    *pbsin1, *pbcos1, *pbtan1, *pbxy;
};
#endif // CALCULATOR_H
