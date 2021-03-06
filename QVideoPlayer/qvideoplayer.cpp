#include "qvideoplayer.h"
#include "ui_qvideoplayer.h"
#include <QMessageBox>

QVideoPlayer::QVideoPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QVideoPlayer), play(false), mute(false), full(false)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    QVideoWidget *videowidget = new QVideoWidget(this);
    player->setVideoOutput(videowidget);
    ui->movieLayout->addWidget(videowidget);

    linearVolume=QAudio::convertVolume(50 / qreal(100.0),
                                       QAudio::LogarithmicVolumeScale,
                                       QAudio::LinearVolumeScale);

    player->setVolume(qRound(linearVolume*100));
    player->setMedia(QUrl::fromLocalFile("D:/Users/idris/Videos/AlmostReadyGame.MP4"));
    //connect(player,&QMediaPlayer::positionChanged, ui->horizontalSlider, &QSlider::setSliderPosition);
    connect (player, &QMediaPlayer::positionChanged, this, &QVideoPlayer::timeChanged);
    connect(player, &QMediaPlayer::positionChanged, ui->horizontalSlider_time, &QSlider::valueChanged);
    //connect (player, &QMediaPlayer::durationChanged, this, &QVideoPlayer::durationChanged);
    QTime t(0,0,0);
    ui->lineEdit_time->setText(t.toString());
    QString filename = "D:/Users/idris/Videos/AlmostReadyGame.MP4";
    QString ftemp =filename;
    ftemp.remove(filename.size()-4,4);
    QFileInfo fileInfo(ftemp);
    avSongs.insert(filename,fileInfo.fileName());
    ui->movieTitle->setText(fileInfo.fileName());
    it = avSongs.begin();

}

QVideoPlayer::~QVideoPlayer()
{
    delete ui;
    delete player;
}

void QVideoPlayer::timeChanged(qint64 progress)
{
    if(ui->horizontalSlider_time->maximum()!=player->duration())
        ui->horizontalSlider_time->setMaximum(player->duration());
    ui->horizontalSlider_time->setValue(progress);
    int sec = progress/1000 %60;
    int min = (progress/60000)%60;
    int hour = (progress/360000)%60;
    QTime time(hour, min,sec);
    ui->lineEdit_time->setText(time.toString());
}


void QVideoPlayer::on_play_pausebutton_clicked()
{
    if(play==false)
    {
        play=true;
        ui->play_pausebutton->setStyleSheet("image: url(:/images/pause.png);"
                                            "background-color: rgb(190,190,190);"
                                            "border-style: outset;"
                                            "border-width: 0px;"
                                            "border-radius: 10px;"
                                            "font: bold 15px;"
                                            "min-width: 2em;"
                                            "padding: 6px;");
        player->play();
    }
    else
    {
        play=false;
        ui->play_pausebutton->setStyleSheet("image: url(:/images/play.png);"
                                            "background-color: rgb(190,190,190);"
                                            "border-style: outset;"
                                            "border-width: 0px;"
                                            "border-radius: 10px;"
                                            "font: bold 15px;"
                                            "min-width: 2em;"
                                            "padding: 6px;");
        player->pause();
    }

}


void QVideoPlayer::on_horizontalSlider_time_sliderMoved(int position)
{
    player->setPosition(position);
}


void QVideoPlayer::on_soundSlider_sliderMoved(int position)
{
    qreal linearVolume = QAudio::convertVolume(position / qreal(100.0),
                                                  QAudio::LogarithmicVolumeScale,
                                                  QAudio::LinearVolumeScale);

       player->setVolume(qRound(linearVolume * 100));
}

void QVideoPlayer::on_soundSlider_valueChanged(int value)
{
    qreal linearVolume = QAudio::convertVolume(value / qreal(100.0),
                                                  QAudio::LogarithmicVolumeScale,
                                                  QAudio::LinearVolumeScale);

       player->setVolume(qRound(linearVolume * 100));
}

void QVideoPlayer::on_pushButton_clicked()
{
    if(mute==false)
    {
        mute=true;
        ui->pushButton->setStyleSheet("image: url(:/images/sound_off.png);"
                                      "background-color: rgb(190,190,190);"
                                      "border-style: outset;"
                                      "border-width: 0px;"
                                      "border-radius: 10px;"
                                      "font: bold 15px;"
                                      "min-width: 2em;"
                                      "padding: 6px;");
        ui->soundSlider->setEnabled(false);
        player->setMuted(true);
    }
    else
    {
        mute=false;
        ui->pushButton->setStyleSheet("image: url(:/images/sound_on.png);"
                                      "background-color: rgb(190,190,190);"
                                      "border-style: outset;"
                                      "border-width: 0px;"
                                      "border-radius: 10px;"
                                      "font: bold 15px;"
                                      "min-width: 2em;"
                                      "padding: 6px;");
        ui->soundSlider->setEnabled(true);
        player->setMuted(false);
    }
}

void QVideoPlayer::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName();
    QString filetemp =file;
    filetemp.remove(file.size()-4,4);
    if(file!=nullptr)
    {
        for(auto i:avSongs)
        {
            if(file==i)
            {
                QMessageBox::information(this,"Error","This playlist already exists.",QMessageBox::Ok);
                goto L;
            }
        }
        QFileInfo fileinfo(filetemp);
        avSongs.insert(file,fileinfo.fileName());
    }
L:

    QMessageBox::information(this,"State","The playlist contains: "+(QString)(avSongs.size()+48)+" video(s)",QMessageBox::Ok);

}

void QVideoPlayer::on_actionQuit_triggered()
{
    QApplication::quit();
}

void QVideoPlayer::on_nextbutton_clicked()
{
    it++;
    if(avSongs.size()==1)
    {
        QMessageBox::information(this,"Error","No palylist to display",QMessageBox::Ok);
        it--;
        return;
    }
    if(it != avSongs.end())
    {
        player->setMedia(QUrl(it.key()));
        ui->movieTitle->setText(it.value());
        if(play!=true)
            player->pause();
        else
            player->play();
    }
    else
    {
        it=avSongs.begin();
        player->setMedia(QUrl(it.key()));
        ui->movieTitle->setText(it.value());
        player->pause();
        play=false;
        ui->play_pausebutton->setStyleSheet("image: url(:/images/play.png);"
                                            "background-color: rgb(190,190,190);"
                                            "border-style: outset;"
                                            "border-width: 0px;"
                                            "border-radius: 10px;"
                                            "font: bold 15px;"
                                            "min-width: 2em;"
                                            "padding: 6px;");
    }
}

void QVideoPlayer::on_actionJump_to_begin_triggered()
{
    play=false;
    if(it!=avSongs.begin())
        it=avSongs.begin();

     player->setMedia(QUrl(it.key()));
     player->pause();
     ui->movieTitle->setText(it.value());
     ui->play_pausebutton->setStyleSheet("image: url(:/images/play.png);"
                                          "background-color: rgb(190,190,190);"
                                          "border-style: outset;"
                                          "border-width: 0px;"
                                          "border-radius: 10px;"
                                          "font: bold 15px;"
                                          "min-width: 2em;"
                                          "padding: 6px;");
}

void QVideoPlayer::on_actionJump_to_end_triggered()
{
    play=false;
    if(it!=avSongs.end())
    {
        it=avSongs.end();
        it--;
    }
    player->setMedia(QUrl(it.key()));
    player->pause();
    ui->movieTitle->setText(it.value());
    ui->play_pausebutton->setStyleSheet("image: url(:/images/play.png);"
                                        "background-color: rgb(190,190,190);"
                                        "border-style: outset;"
                                        "border-width: 0px;"
                                        "border-radius: 10px;"
                                        "font: bold 15px;"
                                        "min-width: 2em;"
                                        "padding: 6px;");
}

void QVideoPlayer::on_back_button_clicked()
{
    if(avSongs.size()==1)
    {
        QMessageBox::information(this,"Error","No palylist to display",QMessageBox::Ok);
        return;
    }
    if(it==avSongs.begin())
    {
        it=avSongs.end();
        it--;
        player->setMedia(QUrl(it.key()));
        ui->movieTitle->setText(it.value());
        player->pause();
        play=false;
        ui->play_pausebutton->setStyleSheet("image: url(:/images/play.png);"
                                            "background-color: rgb(190,190,190);"
                                            "border-style: outset;"
                                            "border-width: 0px;"
                                            "border-radius: 10px;"
                                            "font: bold 15px;"
                                            "min-width: 2em;"
                                            "padding: 6px;");
    }
    else
    {
        it--;
        player->setMedia(QUrl(it.key()));
        ui->movieTitle->setText(it.value());
        if(play!=true)
            player->pause();
        else
            player->play();
    }
}
// pressed and released button.
void QVideoPlayer::on_play_pausebutton_pressed()
{
    if(play==false)
        ui->play_pausebutton->setStyleSheet("image: url(:/images/pause.png);"
                                            "background-color: rgb(160,160,160);"
                                            "border-style: outset;"
                                            "border-width: 0px;"
                                            "border-radius: 10px;"
                                            "font: bold 15px;"
                                            "min-width: 2em;"
                                            "padding: 6px;");
    else
        ui->play_pausebutton->setStyleSheet("image: url(:/images/play.png);"
                                            "background-color: rgb(160,160,160);"
                                            "border-style: outset;"
                                            "border-width: 0px;"
                                            "border-radius: 10px;"
                                            "font: bold 15px;"
                                            "min-width: 2em;"
                                            "padding: 6px;");
}

void QVideoPlayer::on_play_pausebutton_released()
{
    ui->play_pausebutton->setStyleSheet("background-color: rgb(190,190,190);"
                                        "border-style: outset;"
                                        "border-width: 0px;"
                                        "border-radius: 10px;"
                                        "font: bold 15px;"
                                        "min-width: 2em;"
                                       "padding: 6px;");
}

void QVideoPlayer::on_nextbutton_pressed()
{
    ui->nextbutton->setStyleSheet("image: url(:/images/next.png);"
                                  "background-color: rgb(160,160,160);"
                                  "border-style: outset;"
                                  "border-width: 0px;"
                                  "border-radius: 10px;"
                                  "font: bold 15px;"
                                  "min-width: 2em;"
                                 "padding: 6px;");
}

void QVideoPlayer::on_nextbutton_released()
{
    ui->nextbutton->setStyleSheet("image: url(:/images/next.png);"
                                  "background-color: rgb(190,190,190);"
                                  "border-style: outset;"
                                   "border-width: 0px;"
                                   "border-radius: 10px;"
                                   "font: bold 15px;"
                                   "min-width: 2em;"
                                   "padding: 6px;");
}

void QVideoPlayer::on_back_button_pressed()
{
    ui->back_button->setStyleSheet("image: url(:/images/back.png);"
                                   "background-color: rgb(160,160,160);"
                                   "border-style: outset;"
                                   "border-width: 0px;"
                                   "border-radius: 10px;"
                                   "font: bold 15px;"
                                   "min-width: 2em;"
                                  "padding: 6px;");
}

void QVideoPlayer::on_back_button_released()
{
    ui->back_button->setStyleSheet("image: url(:/images/back.png);"
                                   "background-color: rgb(190,190,190);"
                                   "border-style: outset;"
                                   "border-width: 0px;"
                                   "border-radius: 10px;"
                                   "font: bold 15px;"
                                   "min-width: 2em;"
                                  "padding: 6px;");
}

void QVideoPlayer::on_fullScreen_clicked()
{
    if(full==false)
    {
        showFullScreen();
        full=true;
    }
    else
    {
        showNormal();
        full=false;
    }
}
