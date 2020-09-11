#ifndef MACHINEHEALTH_H
#define MACHINEHEALTH_H

//#pragma warning(disable:4996)
#include <QMainWindow>
#include <chrono>
#include <QDateTimeEdit>
#include <QTimer>
#include<QtSql/QSqlDatabase>


QT_BEGIN_NAMESPACE
namespace Ui { class MachineHealth; }
QT_END_NAMESPACE

class MachineHealth : public QMainWindow
{
    Q_OBJECT

public:
    MachineHealth(QWidget *parent = nullptr);
    ~MachineHealth();

private slots:

    void on_comboBox_currentTextChanged(const QString &arg1);

    void set12hour();

    void set24hour();

    void on_pushButton_clear_clicked();



    void on_pushButton_clicked();

    void on_actionNew_2_triggered();

    void on_actionClose_triggered();

    void on_actionVersion_triggered();

    void on_pushButton_save_clicked();

    bool State_Ok();

    void Incheck_Boxes();

    void on_actionSave_triggered();

    void on_actionContact_SOS_triggered();

    void update();

private:
    Ui::MachineHealth *ui;
    bool Format=false;
    QDate iD, myD;
    QTime iT, myT;
    int t;
    QTimer* updateTime=new QTimer;

    bool set12=true, set24=false;
    QSqlDatabase db;
};
#endif // MACHINEHEALTH_H
