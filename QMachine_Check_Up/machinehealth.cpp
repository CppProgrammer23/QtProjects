#include "machinehealth.h"
#include "ui_machinehealth.h"
#include <qpixmap.h>
#include <QMessageBox>
#include <QUrl>
#include <QDesktopServices>
#include <QDateTime>


MachineHealth::MachineHealth(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MachineHealth)
{
    ui->setupUi(this);


    ui->timeEdit->setDisplayFormat("hh:mm A");

    ui->timeEdit->setTime(QTime::currentTime());
    ui->dateEdit->setDate(QDate::currentDate());


    connect(updateTime,&QTimer::timeout, this, &MachineHealth::update);
    updateTime->start(100);

    db = QSqlDatabase::addDatabase("QSQLITE");  //this is the driver for SQL Lite
    db.setPort(3306);
    db.setHostName("sql2.freemysqlhosting.net");
    db.setPassword("YourCode");
    db.setUserName("YourDBName");
    if(!db.open())
        ui->label->setText("<font color='red'>Failed to connect to database.</font>");
    else
        ui->label->setText("<font color='green'>Connected to database and Opened.</font>");

}

MachineHealth::~MachineHealth()
{
    delete ui;
}


void MachineHealth::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1=="12-hour")
    {
        set12hour();
        set12=true;
        set24=false;
    }
    else
    {
        set24hour();
        set24=true;
        set12=false;
    }
}

void MachineHealth::set12hour()
{
    QTime t;
    ui->comboBox_HFormat->setHidden(false);
    if(myT.hour()>12)
    {
        t.setHMS(myT.hour()-12,myT.minute(),myT.second());
        ui->timeEdit->setTime(t);
        Format=true;
    }
    else
        Format=false;
}

void MachineHealth::set24hour()
{
    ui->comboBox_HFormat->setHidden(true);
    ui->timeEdit->setTime(iT);
}

void MachineHealth::on_pushButton_clear_clicked()
{
    if(!ui->checkBox_7->isChecked() && !ui->checkBox_8->isChecked() && !ui->checkBox_9->isChecked() && !ui->checkBox_10->isChecked()
            && !ui->checkBox_Eth->isChecked() && !ui->checkBox_LED->isChecked() && !ui->checkBox_Oil->isChecked() && !ui->checkBox_Volt->isChecked()
            && !ui->checkBox_RS485->isChecked() && !ui->checkBox_pression->isChecked())
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
}



void MachineHealth::on_pushButton_clicked()
{
    QApplication::quit();
}

void MachineHealth::on_actionNew_2_triggered()
{
    on_pushButton_clear_clicked();
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

    qsr.prepare("INSERT INTO mytab (operator_id, machine_id) VALUES (:operator_id, :machine_id);");
    qsr.bindValue(":operator_id",41);
    qsr.bindValue(":machine_id",74);

    if(qsr.exec())
        QMessageBox::information(this, "State","Saved",QMessageBox::Ok);
    else
        QMessageBox::information(this, "State", qsr.lastError().text(),QMessageBox::Ok);

    Incheck_Boxes();
    ui->lineEdit->clear();
    ui->lineEdit_Operator_ID->clear();
    db.close();
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
    QTime t;
    if(set12==true)
    {
        if(myT.hour()>12)
        {
            t.setHMS(myT.hour()-12,myT.minute(),myT.second());
            ui->timeEdit->setTime(t);
        }
        else
        {
            ui->comboBox_HFormat->setCurrentIndex(0);
            ui->timeEdit->setTime(QTime::currentTime());
        }
    }
    else
        ui->timeEdit->setTime(QTime::currentTime());
    ui->dateEdit->setDate(QDate::currentDate());

}
