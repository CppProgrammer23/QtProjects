#include "machinehealth.h"
#include "ui_machinehealth.h"
#include <qpixmap.h>
#include <QMessageBox>
#include <QUrl>
#include <QDesktopServices>
#include <QDateTime>
#include<QtSql/QSqlQuery>
#include<QtSql>



MachineHealth::MachineHealth(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MachineHealth), set12(true)
{
    ui->setupUi(this);


    ui->timeEdit->setDisplayFormat("hh:mm A");

    ui->timeEdit->setTime(QTime::currentTime());
    ui->dateEdit->setDate(QDate::currentDate());


    connect(updateTime,&QTimer::timeout, this, &MachineHealth::update);
    updateTime->start(100);

    db = QSqlDatabase::addDatabase("QMYSQL3");  //this is the driver for SQL Lite
    db.setPort(yourport);
    db.setHostName("your host");
    db.setPassword("yourpasswort");
    db.setUserName("username");
    db.setDatabaseName("username");
    if(!db.open())
        ui->label->setText("<font color='red'>Failed to connect to database.</font>");
    else
        ui->label->setText("<font color='green'>Connected to database and opened.</font>");
    l = db.tables();
    for(auto i=0;i<l.size();i++)
        ui->combo_Table->addItem(l.at(i));

    at = new AddTable;

}
QSqlDatabase MachineHealth::db;
QVector <QString> MachineHealth::TableContains;

MachineHealth::~MachineHealth()
{
    delete ui;
    delete updateTime;
    delete at;
}


void MachineHealth::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1=="12-hour")
        set12=true;
    else
        set12=false;
}

void MachineHealth::on_pushButton_clear_clicked()
{
    if(!ui->checkBox_7->isChecked() && !ui->checkBox_8->isChecked() && !ui->checkBox_9->isChecked() && !ui->checkBox_10->isChecked()
            && !ui->checkBox_Eth->isChecked() && !ui->checkBox_LED->isChecked() && !ui->checkBox_Oil->isChecked() && !ui->checkBox_Volt->isChecked()
            && !ui->checkBox_RS485->isChecked() && !ui->checkBox_pression->isChecked() && ui->lineEdit->text()==""
            && ui->lineEdit_Operator_ID->text()=="")
        return;
    ui->checkBox_7->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_8->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_9->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_10->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_Eth->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_LED->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_Oil->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_Volt->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_RS485->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_pression->setCheckState(Qt::CheckState::Unchecked);
    ui->lineEdit->clear();
    ui->lineEdit_Operator_ID->clear();
}



void MachineHealth::on_pushButton_clicked()
{
    QApplication::quit();
}

void MachineHealth::on_actionClose_triggered()
{
    on_pushButton_clicked();
}

void MachineHealth::on_actionVersion_triggered()
{
    QMessageBox::information(this,"Version","The current version is: 2.1.0\n\n"
                                            "Contact number: Your phone number\n\n"
                                            "Creator: Idriss Chaouch\n",QMessageBox::Ok);
}

void MachineHealth::on_pushButton_save_clicked()
{
    if(!db.open())
        db.open();
    QSqlQuery qsr(db);
    QString temp;
    QString Machine_ID = ui->lineEdit->text();
    QString Operator_ID =ui->lineEdit_Operator_ID->text();
    if(Machine_ID=="")
    {
         QMessageBox::information(this,"Error","Please enter the Machine's ID",QMessageBox::Ok);
         return;
    }
    if(Operator_ID=="")
    {
        QMessageBox::information(this,"Error","Please enter the Operator's ID",QMessageBox::Ok);
        return;
    }
    if(ui->combo_Table->currentText()=="")
    {
        QMessageBox::information(this,"Error","Please choose a table to save data",QMessageBox::Ok);
        return;
    }

    if(State_Ok())
        //send Machine State OK to DB
        QMessageBox::information(this,"Machine state","State verified",QMessageBox::Ok);
    else
    {
        //send Machine State Not OK, have to make a revision
        QMessageBox::StandardButton res = QMessageBox::information(this,"Machine state","State not verified.\n"
                                                                                        "Do you want to continue?",QMessageBox::Yes,QMessageBox::No);
        if(res == QMessageBox::No)
            return;
    }
    temp="INSERT INTO ";
    temp+=ui->combo_Table->currentText();
    temp+=" (operator_id, machine_id, time, date, oil_test, LED_test, eth_test, rs485_test"
          ", volt_test, pression_test, sw_test, urg_button_test, button_test, test) VALUES (:operator_id, :machine_id, :time, :date"
          ", :oil_test, :LED_test, :eth_test, :rs485_test, :volt_test, :pression_test, :sw_test, :urg_button_test, :button_test, :test);";
    qsr.prepare(temp);
    qsr.bindValue(":operator_id",ui->lineEdit_Operator_ID->text());
    qsr.bindValue(":machine_id",ui->lineEdit->text());
    qsr.bindValue(":time", QTime::currentTime().toString());
    qsr.bindValue(":date", QDate::currentDate().toString());
    qsr.bindValue(":oil_test", ui->checkBox_Oil->isChecked());
    qsr.bindValue(":LED_test",ui->checkBox_LED->isChecked());
    qsr.bindValue(":eth_test",ui->checkBox_Eth->isChecked());
    qsr.bindValue(":rs485_test", ui->checkBox_RS485->isChecked());
    qsr.bindValue(":volt_test", ui->checkBox_Volt->isChecked());
    qsr.bindValue(":pression_test",ui->checkBox_pression->isChecked());
    qsr.bindValue(":sw_test",ui->checkBox_7->isChecked());
    qsr.bindValue(":urg_button_test",ui->checkBox_8->isChecked());
    qsr.bindValue(":button_test",ui->checkBox_9->isChecked());
    qsr.bindValue(":test",ui->checkBox_10->isChecked());

    if(qsr.exec())
        QMessageBox::information(this, "State","Saved to: "+ui->combo_Table->currentText(),QMessageBox::Ok);
    else
        QMessageBox::information(this, "State", qsr.lastError().text(),QMessageBox::Ok);


    Incheck_Boxes();
    ui->lineEdit->clear();
    ui->lineEdit_Operator_ID->clear();
    db.close();
    ui->label->setText("DataBase closed.");
    QMessageBox::StandardButton res1 = QMessageBox::information(this,"State","Do you want to make an other check-up?",QMessageBox::Yes,QMessageBox::No);
    if(res1==QMessageBox::Yes)
    {
        if(db.open())
            ui->label->setText("<font color='green'>Database opened!</font>");
    }
    else
        QApplication::quit();
}

bool MachineHealth::State_Ok()
{
    if (ui->checkBox_7->isChecked() && ui->checkBox_8->isChecked() && ui->checkBox_9->isChecked() && ui->checkBox_10->isChecked()
            && ui->checkBox_Eth->isChecked() && ui->checkBox_Volt->isChecked() && ui->checkBox_LED->isChecked() && ui->checkBox_Oil->isChecked()
            && ui->checkBox_RS485->isChecked() && ui->checkBox_pression->isChecked())
        return true;
    return false;
}

void MachineHealth::Incheck_Boxes()
{
    ui->checkBox_7->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_8->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_9->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_10->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_Eth->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_LED->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_Oil->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_Volt->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_RS485->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_pression->setCheckState(Qt::CheckState::Unchecked);
}

void MachineHealth::on_actionSave_triggered()
{
    on_pushButton_save_clicked();
}

void MachineHealth::on_actionContact_SOS_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/CppProgrammer23"));
}

void MachineHealth::update()
{
    if(set12==true)
    {
        ui->timeEdit->setDisplayFormat("hh:mm A");

        ui->timeEdit->setTime(QTime::currentTime());
    }
    else
    {
        ui->timeEdit->setDisplayFormat("HH:mm");
        ui->timeEdit->setTime(QTime::currentTime());
    }
    ui->dateEdit->setDate(QDate::currentDate());
}

void MachineHealth::on_database_button_clicked()
{
    QDesktopServices::openUrl(QUrl("http://www.phpmyadmin.co"));
}

void MachineHealth::on_actionOpen_2_triggered()
{
    on_database_button_clicked();
}

void MachineHealth::on_actionNew_file_triggered()
{
    on_pushButton_clear_clicked();
}

void MachineHealth::on_actionCreate_new_table_triggered()
{
    at->open();
}

void MachineHealth::paintEvent(QPaintEvent *)
{
    if(ui->combo_Table->isVisible())
    {
        for(auto i=0;i<TableContains.size();i++)
            ui->combo_Table->addItem(TableContains.at(i));
        TableContains.clear();
    }
}
