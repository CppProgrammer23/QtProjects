#include "frequency.h"
#include "ui_frequency.h"


Frequency::Frequency(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Frequency)
{
    ui->setupUi(this);
    ui->checkBox->setCheckable(true);
    ui->labelvaluepercent->setNum(0);
    ui->horizontalSlider_fr->setEnabled(false);
    //connect(ui->checkBox, &QCheckBox::setChecked, ui->horizontalSlider, &QSlider::setEnabled);
    connect(ui->horizontalSlider_fr, SIGNAL(valueChanged(int)), ui->labelvaluepercent, SLOT(setValue(int)));
    connect(ui->verticalSlider, SIGNAL(valueChanged(int)), ui->label_60hzdb, SLOT(setValue((int-50)/(10*log(60)))));

    MyApp m;
    connect(ui->horizontalSlider_fr,&QSlider::valueChanged, m.player, &QMediaPlayer::volumeChanged);




}

Frequency::~Frequency()
{
    delete ui;
}

void Frequency::on_checkBox_clicked()
{
    MyApp m;
    if(check==false)
    {
        check=true;
        ui->checkBox->setChecked(true);
        ui->horizontalSlider_fr->setEnabled(true);
    }
    else
    {
        check=false;
        ui->checkBox->setChecked(false);
        ui->horizontalSlider_fr->setEnabled(false);
    }
}



void Frequency::on_pushButton_2_clicked()
{
    QDialog::close();
}

void Frequency::on_verticalSlider_4_sliderMoved(int position)
{
    ui->label_60hzdb->setNum(position/(10*log(40)));
}

void Frequency::on_pushButton_3_clicked()
{
    ui->label_60hzdb->setText("0.0");
    ui->label_120db->setText("0.0");
    ui->label_1khzdb->setText("0.0");
    ui->label_3khzdb->setText("0.0");
    ui->verticalSlider->setValue(0);
    ui->verticalSlider_2->setValue(0);
    ui->verticalSlider_3->setValue(0);
    ui->verticalSlider_4->setValue(0);
    ui->checkBox->setChecked(false);
    check=false;
    ui->horizontalSlider_fr->setValue(0);
    ui->horizontalSlider_fr->setEnabled(false);
    ui->labelvaluepercent->setNum(0);

}

void Frequency::on_verticalSlider_3_sliderMoved(int position)
{
    ui->label_120db->setNum(position/(10*log(60)));
}


void Frequency::on_verticalSlider_2_sliderMoved(int position)
{
    ui->label_1khzdb->setNum(position/(10*log(60)));
}


void Frequency::on_verticalSlider_sliderMoved(int position)
{
    ui->label_3khzdb->setNum(position/(10*log(60)));
}

void Frequency::on_horizontalSlider_fr_sliderMoved(int position)
{

    ui->labelvaluepercent->setNum(position);

}
void Frequency::on_horizontalSlider_fr_valueChanged(int value)
{
    MyApp m;
    m.linearVolume+=QAudio::convertVolume(value / qreal(100.0),
                                          QAudio::LogarithmicVolumeScale,
                                          QAudio::LinearVolumeScale);
    m.on_verticalSlider_valueChanged(m.linearVolume);

}
