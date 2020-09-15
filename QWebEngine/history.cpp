#include "history.h"
#include "ui_history.h"
#include "mywebengine.h"


History::History(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);

}

History::~History()
{
    delete ui;
}

void History::paintEvent(QPaintEvent *)
{
    QString s;
    if(QDialog::isVisible())
    {
        for(auto i=myWebEngine::ls.begin(); i != myWebEngine::ls.end();++i)
             s+=*i+"<br>";
        ui->textBrowser->setText(s);
    }

}

void History::on_pushButton_clicked()
{
    QDialog::close();
}

void History::on_pushButton_2_clicked()
{
    ui->textBrowser->clear();
    myWebEngine::ls.clear();
}
