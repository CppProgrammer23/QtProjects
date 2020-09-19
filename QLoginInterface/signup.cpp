#include "signup.h"
#include "ui_signup.h"
#include <QSqlQuery>
#include "logininterface.h"
#include <QMessageBox>

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_cancelbutton_clicked()
{
    QDialog::close();
}

void SignUp::on_okbutton_clicked()
{
    QString mail = ui->lineEmailEdit->text();
    if(ui->linePassEdit->text()=="")
    {
        QMessageBox::information(this,"State","There is no password, please enter one");
        return;
    }
    QString pass = ui->linePassEdit->text();
    QString name = ui->lineNameEdit->text();
    QString surn = ui->lineSurnmeEdit->text();
    if(ui->linePassEdit->text()!=ui->linePassAgainEdit->text())
    {
        QMessageBox::information(this,"State","Please enter the same password");
        return;
    }
    QSqlQuery qsr(LoginInterface::db);
    if(qsr.exec("SELECT * FROM subscribers WHERE email='"+mail+"';"))
    {
        int c=0;
        while(qsr.next())
            c++;
        if(c==0)
        {
            QString query = "INSERT INTO subscribers (name, surname, email, password) VALUES (:name, :surname, :email, :password);";
            qsr.prepare(query);
            qsr.bindValue(":email",mail);
            qsr.bindValue(":password",pass);
            qsr.bindValue(":name",name);
            qsr.bindValue(":surname",surn);
            if(qsr.exec())
                QMessageBox::information(this,"Info","User created successfully",QMessageBox::Ok);
            else
                QMessageBox::information(this,"Info","failed",QMessageBox::Ok);
        }
        else
            QMessageBox::information(this,"Error","User already exist",QMessageBox::Ok);

    }

}
