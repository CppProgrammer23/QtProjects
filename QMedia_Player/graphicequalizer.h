#ifndef FREQUENCY_H
#define FREQUENCY_H

#include <QDialog>
#include <cmath>
#include <QRadioTuner>
#include "myapp.h"

namespace Ui {
class Frequency;
}

class Frequency : public QDialog
{
    Q_OBJECT

public:
    explicit Frequency(QWidget *parent = nullptr);
    ~Frequency();

private slots:
    void on_checkBox_clicked();

    void on_pushButton_2_clicked();

    void on_verticalSlider_4_sliderMoved(int position);

    void on_pushButton_3_clicked();

    void on_verticalSlider_3_sliderMoved(int position);

    void on_verticalSlider_2_sliderMoved(int position);

    void on_verticalSlider_sliderMoved(int position);

    void on_horizontalSlider_fr_sliderMoved(int position);

    void on_horizontalSlider_fr_valueChanged(int value);

private:
    Ui::Frequency *ui;
    bool check=false;
    int val=50;
};

#endif // FREQUENCY_H
