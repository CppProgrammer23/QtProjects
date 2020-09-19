#include "logininterface.h"
#include "ui_logininterface.h"
#include <QtSql>
#include <QSqlQuery>
#include <QMessageBox>
#include <QUrl>

LoginInterface::LoginInterface(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginInterface), visible(false)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL3");  //this is the driver for SQL Lite
    db.setPort(3306);
    db.setHostName("yourHost");
    db.setPassword("YourPass");
    db.setUserName("DBName");
    db.setDatabaseName("DBName");
    if(db.open())
        ui->testConnection->setChecked(true);
    else
        ui->testConnection->setChecked(false);

}

LoginInterface::~LoginInterface()
{
    delete ui;
}

QSqlDatabase LoginInterface::db;
void LoginInterface::on_Login_button_clicked()
{
    QString email = ui->email_text->text();
    QString pass = ui->passText->text();
    QSqlQuery q(db);
    if(ui->Error_connection->text()!="")
        ui->Error_connection->clear();
    if(!ui->testConnection->isChecked())
        ui->Error_connection->setText("<font color='red'>&nbsp;&nbsp;&nbsp;&nbsp;Cannot connection, please verify your connection.</font>");

    if(q.exec("SELECT * FROM subscribers WHERE email='"+email+"' AND password='"+pass+"';"))
    {
        int c=0;
        while(q.next())
            c++;
        if(c==1)
            ui->Error_connection->setText("<font color ='green'> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Connection..."
                                      "</font>");
        else
            ui->Error_connection->setText("<font color='red'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Please verify your e-mail or your password.</font>");

    }
}

void LoginInterface::on_visiblepass_clicked()
{
    if(visible==false)
    {
        visible=true;
        ui->passText->setEchoMode(QLineEdit::Normal);
        ui->visiblepass->setStyleSheet("image: url(:/imag/not visible.png);");
    }
    else
    {
        visible=false;
        ui->passText->setEchoMode(QLineEdit::Password);
        ui->visiblepass->setStyleSheet("image: url(:/imag/visible.png);");
    }
}

void LoginInterface::on_createbutton_clicked()
{
    SignUp *s = new SignUp;
    s->open();
}
