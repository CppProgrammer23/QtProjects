#include "calculator.h"
#include "ui_calculator.h"
#include <QVBoxLayout>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    this->setFixedSize(380,530);
    minus=mul=plus=div=sc=false;
    val=val1=0.;
    //digit connection
    connect(ui->button0, SIGNAL(released()), this,SLOT(digitClicked()));
    connect(ui->button1, SIGNAL(released()), this,SLOT(digitClicked()));
    connect(ui->button2, SIGNAL(released()), this,SLOT(digitClicked()));
    connect(ui->button3, SIGNAL(released()), this,SLOT(digitClicked()));
    connect(ui->button4, SIGNAL(released()), this,SLOT(digitClicked()));
    connect(ui->button5, SIGNAL(released()), this,SLOT(digitClicked()));
    connect(ui->button6, SIGNAL(released()), this,SLOT(digitClicked()));
    connect(ui->button7, SIGNAL(released()), this,SLOT(digitClicked()));
    connect(ui->button8, SIGNAL(released()), this,SLOT(digitClicked()));
    connect(ui->button9, SIGNAL(released()), this,SLOT(digitClicked()));
    connect(ui->buttonpoint, SIGNAL(released()), this,SLOT(digitClicked()));

    //operator connection
    connect(ui->buttonmult,SIGNAL(released()),this, SLOT(operatorClicked()));
    connect(ui->buttonminus,SIGNAL(released()),this, SLOT(operatorClicked()));
    connect(ui->buttondivide,SIGNAL(released()),this, SLOT(operatorClicked()));
    connect(ui->buttonplus,SIGNAL(released()),this, SLOT(operatorClicked()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::createButton()
{
    QVBoxLayout *layout=new QVBoxLayout();
    pblog = new QPushButton("log2",this);
    pbsqrt = new QPushButton("√x",this);
    pbfact = new QPushButton("x!",this);
    pbinv = new QPushButton("1/x",this);
    pbpi = new QPushButton("𝛑",this);
    pbsin = new QPushButton("sin", this);
    pbcos = new QPushButton("cos",this);
    pbtang = new QPushButton("tan",this);
    pbexp = new QPushButton("e",this);
    pb10 = new QPushButton("10",this);
    pbln = new QPushButton("ln",this);
    pbrand = new QPushButton("Rand",this);

    pblog->setStyleSheet("QPushButton{"
                      "color: rgb(255, 255, 255);"
                      "border: 1px solid gray;border-radius: 25px;}"

                      "QPushButton:pressed {"
                      "color: rgb(100,100,100);"
                         " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                            "stop: 0 #dadbde, stop: 1 #f6f7fa);"
                      "}");
    pbsqrt->setStyleSheet("QPushButton{"
                      "color: rgb(255, 255, 255);"
                      "border: 1px solid gray;border-radius: 25px;}"

                      "QPushButton:pressed {"
                      "color: rgb(100,100,100);"
                         " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                            "stop: 0 #dadbde, stop: 1 #f6f7fa);"
                      "}");
    pbfact->setStyleSheet("QPushButton{"
                          "color: rgb(255, 255, 255);"
                          "border: 1px solid gray;border-radius: 25px;}"

                          "QPushButton:pressed {"
                          "color: rgb(100,100,100);"
                             " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                                "stop: 0 #dadbde, stop: 1 #f6f7fa);"
                          "}");
    pbinv->setStyleSheet("QPushButton{"
                         "color: rgb(255, 255, 255);"
                         "border: 1px solid gray;border-radius: 25px;}"

                         "QPushButton:pressed {"
                         "color: rgb(100,100,100);"
                            " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                               "stop: 0 #dadbde, stop: 1 #f6f7fa);"
                         "}");
    pbpi->setStyleSheet("QPushButton{"
                        "color: rgb(255, 255, 255);"
                        "border: 1px solid gray;border-radius: 25px;}"

                        "QPushButton:pressed {"
                        "color: rgb(100,100,100);"
                           " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                              "stop: 0 #dadbde, stop: 1 #f6f7fa);"
                        "}");
    pbsin->setStyleSheet("QPushButton{"
                         "color: rgb(255, 255, 255);"
                         "border: 1px solid gray;border-radius: 25px;}"

                         "QPushButton:pressed {"
                         "color: rgb(100,100,100);"
                            " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                               "stop: 0 #dadbde, stop: 1 #f6f7fa);"
                         "}");
    pbcos->setStyleSheet("QPushButton{"
                         "color: rgb(255, 255, 255);"
                         "border: 1px solid gray;border-radius: 25px;}"

                         "QPushButton:pressed {"
                         "color: rgb(100,100,100);"
                            " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                               "stop: 0 #dadbde, stop: 1 #f6f7fa);"
                         "}");
    pbtang->setStyleSheet("QPushButton{"
                          "color: rgb(255, 255, 255);"
                          "border: 1px solid gray;border-radius: 25px;}"

                          "QPushButton:pressed {"
                          "color: rgb(100,100,100);"
                             " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                                "stop: 0 #dadbde, stop: 1 #f6f7fa);"
                          "}");
    pbexp->setStyleSheet("QPushButton{"
                         "color: rgb(255, 255, 255);"
                         "border: 1px solid gray;border-radius: 25px;}"

                         "QPushButton:pressed {"
                         "color: rgb(100,100,100);"
                            " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                               "stop: 0 #dadbde, stop: 1 #f6f7fa);"
                         "}");
    pb10->setStyleSheet("QPushButton{"
                        "color: rgb(255, 255, 255);"
                        "border: 1px solid gray;border-radius: 25px;}"

                        "QPushButton:pressed {"
                        "color: rgb(100,100,100);"
                           " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                              "stop: 0 #dadbde, stop: 1 #f6f7fa);"
                        "}");
    pbln->setStyleSheet("QPushButton{"
                        "color: rgb(255, 255, 255);"
                        "border: 1px solid gray;border-radius: 25px;}"

                        "QPushButton:pressed {"
                        "color: rgb(100,100,100);"
                           " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                              "stop: 0 #dadbde, stop: 1 #f6f7fa);"
                        "}");
    pbrand->setStyleSheet("QPushButton{"
                          "color: rgb(255, 255, 255);"
                          "border: 1px solid gray;border-radius: 25px;}"

                          "QPushButton:pressed {"
                          "color: rgb(100,100,100);"
                             " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                                "stop: 0 #dadbde, stop: 1 #f6f7fa);"
                          "}");

    layout->addWidget(pblog);
    layout->addWidget(pbsqrt);
    layout->addWidget(pbfact);
    layout->addWidget(pbinv);
    layout->addWidget(pbpi);
    layout->addWidget(pbsin);
    layout->addWidget(pbcos);
    layout->addWidget(pbtang);
    layout->addWidget(pbexp);
    layout->addWidget(pb10);
    layout->addWidget(pbln);
    layout->addWidget(pbrand);

    pblog->setGeometry(190,195,50,50);
    pbsqrt->setGeometry(130,195,50,50);
    pbfact->setGeometry(70,195,50,50);
    pbinv->setGeometry(10,195,50,50);
    pbpi->setGeometry(190,260,50,50);
    pbsin->setGeometry(130,260,50,50);
    pbcos->setGeometry(70,260,50,50);
    pbtang->setGeometry(10,260,50,50);
    pbexp->setGeometry(190,320,50,50);
    pb10->setGeometry(130,320,50,50);
    pbln->setGeometry(70,320,50,50);
    pbrand->setGeometry(10,320,50,50);

    pblog->show();
    pbsqrt->show();
    pbfact->show();
    pbinv->show();
    pbpi->show();
    pbsin->show();
    pbcos->show();
    pbtang->show();
    pbexp->show();
    pb10->show();
    pbln->show();
    pbrand->show();
}

void Calculator::digitClicked()
{
    QPushButton* button = (QPushButton*)sender();
    if(ui->label->text()=="nan" || ui->label_2->text().endsWith("="))
        ui->label_2->clear();
    if(ui->label->text()=="0" || ui->label->text()=="nan" || ui->label_2->text().endsWith("="))
        ui->label->clear();

    QString lab = ui->label->text() + button->text();
    lab1=ui->label_2->text() + button->text();
    if(minus || plus || mul || div)
        val1=lab.toDouble();

    else
        val = lab.toDouble();
    ui->label->setText(lab);
    ui->label_2->setText(lab1);
}

void Calculator::operatorClicked()
{
    QPushButton* button = (QPushButton*)sender();
    if(button->text()=="/")
        div=true;
    else if(button->text()=="x")
        mul=true;
    else if(button->text()=="+")
        plus=true;
    else
        minus=true;
    ui->label->setText("0");
    lab1+=button->text();
    ui->label_2->setText(lab1);
}


void Calculator::on_buttonAC_clicked()
{
    ui->label->setText("0");
    ui->label_2->clear();
    minus=mul=plus=div=false;
    val=val1=0.;
}

void Calculator::on_buttonequal_clicked()
{
    double res{};
    ui->label_2->setText(lab1+"=");
    if(div)
    {
        if(val1==0.)
        {
            ui->label->setText("nan");
            return;
        }
        res=val/val1;
    }
    else if(mul)
        res=val*val1;
    else if(plus)
        res = val+val1;
    else
        res = val-val1;

    ui->label->setNum(res);
    minus=mul=plus=div=false;
    val1=0.;
    val=res;
}

void Calculator::on_buttonscientific_clicked()
{

    QFont f;

    if(sc==false)
    {
        this->setFixedSize(500,530);
        f.setStrikeOut(true);
        ui->buttonscientific->setGeometry(450,10,50,50);
        ui->buttonscientific->setFont(f);
        {
        ui->buttondivide->setGeometry(440,195,50,50);
        ui->buttonmult->setGeometry(440,260,50,50);
        ui->buttonminus->setGeometry(440,320,50,50);
        ui->buttonplus->setGeometry(440,390,50,50);
        ui->buttonequal->setGeometry(440,450,50,50);
        ui->buttonpercent->setGeometry(375,195,50,50);
        ui->button9->setGeometry(375,260,50,50);
        ui->button6->setGeometry(375,325,50,50);
        ui->button3->setGeometry(375,390,50,50);
        ui->buttonpoint->setGeometry(375,450,50,50);
        ui->buttonplus_minus->setGeometry(315,195,50,50);
        ui->button8->setGeometry(315,260,50,50);
        ui->button5->setGeometry(315,320,50,50);
        ui->button2->setGeometry(315,390,50,50);
        ui->button1->setGeometry(250,390,50,50);
        ui->button4->setGeometry(250,320,50,50);
        ui->button7->setGeometry(250,260,50,50);
        ui->button0->setGeometry(250,450,120,50);
        ui->buttonAC->setGeometry(250,195,50,50);
        ui->label->setGeometry(70,30,400,200);
        }
        createButton();
        sc=true;
    }
    else
    {
        this->setFixedSize(380,530);
        f.setStrikeOut(false);
        ui->buttonscientific->setGeometry(330,10,50,50);
        ui->buttonscientific->setFont(f);
        delete pblog;
        delete pbsqrt;
        delete pbfact;
        delete pbinv;
        delete pbpi;
        delete pbsin;
        delete pbcos;
        delete pbtang;
        delete pbexp;
        delete pb10;
        delete pbln;
        delete pbrand;
        {
            ui->buttondivide->setGeometry(310,195,50,50);
            ui->buttonmult->setGeometry(310,260,50,50);
            ui->buttonminus->setGeometry(310,325,50,50);
            ui->buttonplus->setGeometry(310,390,50,50);
            ui->buttonequal->setGeometry(310,450,50,50);
            ui->buttonpercent->setGeometry(230,195,50,50);
            ui->button9->setGeometry(230,260,50,50);
            ui->button6->setGeometry(230,325,50,50);
            ui->button3->setGeometry(230,390,50,50);
            ui->buttonpoint->setGeometry(230,450,50,50);
            ui->buttonplus_minus->setGeometry(140,195,50,50);
            ui->button8->setGeometry(140,260,50,50);
            ui->button5->setGeometry(140,320,50,50);
            ui->button2->setGeometry(140,390,50,50);
            ui->button1->setGeometry(50,390,50,50);
            ui->button4->setGeometry(50,320,50,50);
            ui->button7->setGeometry(50,260,50,50);
            ui->button0->setGeometry(50,450,140,50);
            ui->buttonAC->setGeometry(50,195,50,50);
            ui->label->setGeometry(110,40,180,150);
        }
        sc=false;
    }
}

void Calculator::on_buttonpercent_clicked()
{
    double s = ui->label->text().toDouble();
    s/=100;
    lab1+="%=";
    ui->label_2->setText(lab1);
    ui->label->setNum(s);

}

void Calculator::on_buttonplus_minus_clicked()
{
    double s = ui->label->text().toDouble();
    s*=-1;
    ui->label->setNum(s);
}

