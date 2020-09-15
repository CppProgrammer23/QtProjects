#include "addtable.h"
#include "ui_addtable.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

AddTable::AddTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTable)
{
    ui->setupUi(this);
}

AddTable::~AddTable()
{
    delete ui;
}

QString AddTable::TableName;
void AddTable::on_Ok_clicked()
{
    QSqlQuery newqsr(MachineHealth::db);
    TableName = ui->lineEdit_text->text();
    if(TableName!="")
    {
        QString myString = "CREATE TABLE ";
        myString+=TableName;
        myString+=" (operator_id varchar(5), machine_id varchar(3), time varchar(12), date varchar(20), oil_test tinyint(1), LED_test tinyint(1)"
                  ", eth_test tinyint(1), rs485_test tinyint(1), "
                  "volt_test tinyint(1), pression_test tinyint(1), sw_test tinyint(1), urg_button_test tinyint(1), button_test tinyint(1)"
                  ", test tinyint(1));";
        //MachineHealth::db.open();
        if(newqsr.exec(myString))
        {
            QMessageBox::information(this,"state","Table created",QMessageBox::Ok);
            MachineHealth::TableContains.push_back(TableName);
        }
        else
            QMessageBox::information(this, "State", newqsr.lastError().text(),QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(this, "Error","No text found!",QMessageBox::Ok);
        return;
    }
    QDialog::close();
}

void AddTable::on_Cancel_clicked()
{
    QDialog::close();
}
