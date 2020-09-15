#ifndef MACHINEHEALTH_H
#define MACHINEHEALTH_H

#include <QMainWindow>
#include <chrono>
#include <QDateTimeEdit>
#include <QTimer>
#include<QtSql/QSqlDatabase>
#include "addtable.h"


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

    void on_pushButton_clear_clicked();



    void on_pushButton_clicked();

    void on_actionClose_triggered();

    void on_actionVersion_triggered();

    void on_pushButton_save_clicked();

    bool State_Ok();

    void Incheck_Boxes();

    void on_actionSave_triggered();

    void on_actionContact_SOS_triggered();

    void update();

    void on_database_button_clicked();

    void on_actionOpen_2_triggered();

    void on_actionNew_file_triggered();

    void on_actionCreate_new_table_triggered();

    void paintEvent(QPaintEvent*);

private:

    Ui::MachineHealth *ui;
    QTimer* updateTime=new QTimer;

    bool set12;
    QList<QString> l;

public:
    class AddTable *at;
    static QSqlDatabase db;
    static QVector <QString> TableContains;


};
#endif // MACHINEHEALTH_H
