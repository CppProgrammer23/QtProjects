#include "signup.h"
#include "ui_signup.h"
#include <QSqlQuery>
#include "logininterface.h"
#include <QMessageBox>
#include <QPaintEvent>

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp),visible(false)
{
    ui->setupUi(this);
    this->setFixedSize(395,300);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_cancelbutton_clicked()
{
    clearAll();
    QDialog::close();
}

void SignUp::on_okbutton_clicked()
{
    QString mail = ui->lineEmailEdit->text();
    if(ui->labelEmailInfo->text()!="")
        ui->labelEmailInfo->clear();
    if(!verifyMail(mail))
    {
        ui->labelEmailInfo->setText("<font color='red'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
                                    "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
                                    "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
                                    "Mail format not recognized.</font>");
        return;
    }
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
    clearAll();
}

bool SignUp::verifyMail(const QString& str)
{
    if(str.endsWith("@outlook.com") || str.endsWith("@yahoo.com") || str.endsWith("@hotmail.com") || str.endsWith("@gmail.com"))
        return true;
    return false;
}

bool SignUp::verifyPass(const QString& str)
{
    bool up=false, num=false, low=false;
    for(auto i:str)
    {
        if(i <91 && i>64)
            up = true;
        else if(i<58 && i>47)
            num=true;
        else if(i<123 && i>96)
            low =true;
    }
    if(up && num && low)
        return true;
    return false;
}

void SignUp::clearAll()
{
    ui->labelEmailInfo->clear();
    ui->lineNameEdit->clear();
    ui->linePassEdit->clear();
    ui->linePassAgainEdit->clear();
    ui->lineEmailEdit->clear();
    ui->lineSurnmeEdit->clear();
    ui->labelPass->clear();
}

void SignUp::paintEvent(QPaintEvent *)
{
    if(verifyPass(ui->linePassEdit->text()))
    {
        if(ui->linePassEdit->text()==ui->linePassAgainEdit->text() && ui->linePassEdit->text()!="")
            ui->labelPass->setText("<font color='green'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
                                   "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
                                   "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
                                   "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
                                   "Same password.</font>");
        else
            ui->labelPass->clear();
    }
    else
    {
        if(ui->linePassEdit->text()!="")
            ui->labelPass->setText("<font color='red'>&nbsp;Password doesn't contain upper, lower and numeric characters.</font>");
        else
            ui->labelPass->clear();
        }
}



void SignUp::on_visible_clicked()
{
    if(visible==false)
    {
        visible=true;
        ui->linePassEdit->setEchoMode(QLineEdit::Normal);
        ui->visible->setStyleSheet("image: url(:/imag/not visible.png);");
    }
    else
    {
        visible=false;
        ui->linePassEdit->setEchoMode(QLineEdit::Password);
        ui->visible->setStyleSheet("image: url(:/imag/visible.png);");
    }
}
