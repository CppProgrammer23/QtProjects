#ifndef MYAPP_H
#define MYAPP_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QProgressBar>
#include <QSlider>
#include <QMessageBox>
#include <QFileDialog>

#include "frequency.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MyApp; }
QT_END_NAMESPACE

class MyApp : public QMainWindow
{
    Q_OBJECT

public:
    MyApp(QWidget *parent = nullptr);
    ~MyApp();

public slots:
    void on_pushButton_prev_pressed();

    void on_pushButton_prev_released();

    void on_pushButton_play_pause_pressed();

    void on_pushButton_play_pause_released();

    void on_pushButton_next_pressed();

    void on_pushButton_next_released();

    void on_pushButton_play_pause_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_pushButton_next_clicked();

    void on_pushButton_prev_clicked();

    //void on_horizontalSlider_actionTriggered(int action);

    void on_horizontalSlider_sliderMoved(int position);

    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_verticalSlider_sliderPressed();

    void on_verticalSlider_sliderReleased();


    void on_actionClose_triggered();

    void on_actionOpen_triggered();

    void on_actionFrequency_triggered();

    void on_actionPause_triggered();

    void on_actionPrevious_triggered();

    void on_actionnext_triggered();

    void on_actionJump_to_begin_triggered();

    void on_actionJump_to_end_triggered();

    void on_actionVersion_triggered();

    void durationChanged(qint64 duration);

    void updateDurationInfo(void);

    void positionChanged(qint64 progress);

public:
    Ui::MyApp *ui;
    QMediaPlayer* player;
    std::list<QString>s{
        "D:/Users/idris/Music/Vicetone & Tony Igy - Astronomia.mp3",
        "D:/Users/idris/Music/Shindy Playerhater.mp3",
        "D:/Users/idris/Music/Balvin Mi-Gente.mp3",
        "D:/Users/idris/Music/BONEZ MC & RAF CAMORA feat. MAXWELL - Ohne mein Team.mp3"
    };
    std::vector<QChar>v;
    std::list<QString>::iterator it=s.begin();
    QMediaPlayer mp;
    QMessageBox Qb;
    QProgressBar* bar;
    int play_pause=0;
    bool mute=true;
    bool Isplaying=false;
    int cur_song=1;
    qreal linearVolume;
    QString name;
    int min,sec;
    qint64 m_duration;

};
#endif // MYAPP_H
