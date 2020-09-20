#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    this->setFixedSize(380,550);
    minus=mul=plus=div=false;
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

void Calculator::digitClicked()
{
    QPushButton* button = (QPushButton*)sender();
    if(ui->label->text()=="0")
        ui->label->clear();
    QString lab = ui->label->text() + button->text();
    if(minus || plus || mul || div)
        val1=lab.toDouble();

    else
        val = lab.toDouble();
    ui->label->setText(lab);
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
}


void Calculator::on_buttonAC_clicked()
{
    ui->label->setText("0");
    minus=mul=plus=div=false;
    val=val1=0.;
}

void Calculator::on_buttonequal_clicked()
{
    double res{};
    if(div)
        res=val/val1;
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
    this->setFixedSize(500,550);
}
