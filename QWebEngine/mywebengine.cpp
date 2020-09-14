#include "mywebengine.h"
#include "ui_mywebengine.h"
#include <QFileDialog>
#include <QMessageBox>

myWebEngine::myWebEngine(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::myWebEngine)
{
    ui->setupUi(this);
    ui->nextbutton->setEnabled(false);
    ui->back_button->setEnabled(false);
    ui->refresbutton->setEnabled(false);
    ui->searchbutton->setEnabled(false);
    ui->nextbutton->setToolTip("Click to go forward");
    ui->back_button->setToolTip("Click to go back");
    ui->refresbutton->setToolTip("Refresh");
    ui->searchbutton->setToolTip("Click to search");
    ui->print->setToolTip("Print");
    ui->history->setToolTip("Go to history");
    webview=new QWebEngineView(ui->webviewFrame);
    webview->load(QUrl("https://qt.io"));
    connect(webview, &QWebEngineView::loadProgress, ui->viewwebLoading, &QProgressBar::setValue);
    //webview->setEnabled(false);
}

myWebEngine::~myWebEngine()
{
    delete ui;
}

void myWebEngine::paintEvent(QPaintEvent *event)
{
    webview->resize(ui->webviewFrame->size());
    if(ui->viewwebLoading->value()==100)
    {
        ui->viewwebLoading->setValue(0);
    }
    if(forward>0)
    {
        ui->back_button->setEnabled(true);
        ui->refresbutton->setEnabled(true);
    }
    else if(forward==0)
    {
        ui->back_button->setEnabled(false);
        ui->nextbutton->setEnabled(true);
    }
    if(back>0)
    {
        ui->nextbutton->setEnabled(true);
    }
    else
        ui->nextbutton->setEnabled(false);
    if(ui->lineEdit->text()!="")
        ui->searchbutton->setEnabled(true);
    else
        ui->searchbutton->setEnabled(false);
}


void myWebEngine::on_back_button_clicked()
{
    back++;
    forward--;
    webview->back();
}

void myWebEngine::on_nextbutton_clicked()
{
    forward++;
    back--;
    webview->forward();
}

void myWebEngine::on_refresbutton_clicked()
{
    webview->reload();
}

void myWebEngine::on_searchbutton_clicked()
{
    forward++;
    Loading();
    webview->load(QUrl(str));
}

void myWebEngine::on_viewwebLoading_valueChanged(int value)
{
    ui->viewwebLoading->setValue(value);
}
void myWebEngine::Loading()
{
    str="";
    if(ui->lineEdit->text().startsWith("http://") || ui->lineEdit->text().startsWith("https://"))
        str+=ui->lineEdit->text();
    else
        str="https://"+ui->lineEdit->text();
}

void myWebEngine::on_print_clicked()
{
    webview->page()->printToPdf(QFileDialog::getSaveFileName(nullptr,QString(),QString(),"Text files (*.pdf)",nullptr));
}

void myWebEngine::on_history_clicked()
{
    QList<QWebEngineHistoryItem> l = history->items();
}

void myWebEngine::on_actionSearch_triggered()
{
    on_searchbutton_clicked();
}

void myWebEngine::on_actionBack_triggered()
{
    on_back_button_clicked();
}

void myWebEngine::on_actionForward_triggered()
{
    on_nextbutton_clicked();
}

void myWebEngine::on_actionVersion_triggered()
{
    QMessageBox::information(this,"Version","The current version is: 1.2.4",QMessageBox::Ok);
}
