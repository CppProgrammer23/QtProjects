#include "myapp.h"
#include "ui_myapp.h"

#include<QTime>

MyApp::MyApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyApp)
{
    ui->setupUi(this);
     player=new QMediaPlayer(this);
     QMediaPlayer mp;
    QPixmap pic("$(YourDirectory)Doc/Qt Creator Projects/MyApp/mus.jpg");
    ui->label_pic->setPixmap(pic.scaled(1000,7000,Qt::KeepAspectRatio));

    //ui->verticalSlider->setValue(50);
    ui->label_tot_song->setNum(int(s.size()));
    ui->label_cur_song->setNum(cur_song);

    connect(ui->verticalSlider, SIGNAL(valueChanged(int)),ui->label_vol_cur, SLOT(setNum(int)));
    player->setMedia(QUrl::fromLocalFile(*it));
    for(int i=21;(i<it->length()-4);i++)
    {
        v.push_back(it->at(i));
    }
    for(auto i=0;i<(int)v.size();i++)
    {
        name+=v[i];
    }
    ui->label_titlesong->setText(name);

    connect(player, &QMediaPlayer::durationChanged, ui->horizontalSlider, &QSlider::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, ui->horizontalSlider, &QSlider::setValue);

    connect(player, &QMediaPlayer::durationChanged, this, &MyApp::durationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MyApp::positionChanged);



    linearVolume=QAudio::convertVolume(50 / qreal(100.0),
                                       QAudio::LogarithmicVolumeScale,
                                       QAudio::LinearVolumeScale);

    player->setVolume(qRound(linearVolume*100));
    updateDurationInfo();





}

MyApp::~MyApp()
{
    delete ui;
}

/*Pressed & released buttons */
void MyApp::on_pushButton_prev_pressed()
{
    ui->pushButton_prev->setStyleSheet("border: 10px;\
                                        color: rgb(50,50,50);\
                                        border-radius: 10px;\
                                        color: rgb(255, 25, 5);\
                                        background-color: rgb(16, 102, 177);");
}

void MyApp::on_pushButton_prev_released()
{
    ui->pushButton_prev->setStyleSheet("border: 10px;\
                                        color: rgb(50,50,50);\
                                        border-radius: 10px;\
                                        color: rgb(255, 25, 5);\
                                        background-color: rgb(5, 47, 79);");
}

void MyApp::on_pushButton_play_pause_pressed()
{
    ui->pushButton_play_pause->setStyleSheet("border: 10px;\
                                             color: rgb(50,50,50);\
                                             border-radius: 10px;\
                                             color: rgb(255, 25, 5);\
                                             background-color: rgb(16, 102, 177);");
}


void MyApp::on_pushButton_play_pause_released()
{
    ui->pushButton_play_pause->setStyleSheet("border: 10px;\
                                             color: rgb(50,50,50);\
                                             border-radius: 10px;\
                                             color: rgb(255, 25, 5);\
                                             background-color: rgb(5, 47, 79);");
}

void MyApp::on_pushButton_next_pressed()
{
    ui->pushButton_next->setStyleSheet("border: 10px;\
                                       color: rgb(50,50,50);\
                                       border-radius: 10px;\
                                       color: rgb(255, 25, 5);\
                                       background-color: rgb(16, 102, 177);");
}

void MyApp::on_pushButton_next_released()
{
    ui->pushButton_next->setStyleSheet("border: 10px;\
                                       color: rgb(50,50,50);\
                                       border-radius: 10px;\
                                       color: rgb(255, 25, 5);\
                                       background-color: rgb(5, 47, 79);");
}
/*Pressed & released buttons */


/* Clicked button */

void MyApp::on_pushButton_play_pause_clicked()
{
    play_pause++;
    if(play_pause==2)
        play_pause=0;

    if(play_pause==1) /*Play */
    {
        player->play();
        Isplaying=true;
    }
    else
    {
        player->pause();
        Isplaying=false;
    }

}




void MyApp::on_verticalSlider_valueChanged(int value)
{
    linearVolume = QAudio::convertVolume(value / qreal(100.0),
                                                  QAudio::LogarithmicVolumeScale,
                                                  QAudio::LinearVolumeScale);

       player->setVolume(qRound(linearVolume * 100));
}

void MyApp::on_pushButton_next_clicked()
{
    it++;
    if(it!=s.end())
    {
        player->setMedia(QUrl::fromLocalFile(*it));
        if(Isplaying==true)
            player->play();
        else
            player->pause();
        cur_song++;
        ui->label_cur_song->setNum(cur_song);
        v.clear();
        name="";
        for(int i=21;(i<it->length()-4);i++)
        {
            v.push_back(it->at(i));
        }
        for(auto i=0;i<(int)v.size();i++)
        {
            name+=v[i];
        }
        ui->label_titlesong->setText("");
        ui->label_titlesong->setText(name);

        updateDurationInfo();
    }
    else
    {
        it=s.begin();
        player->setMedia(QUrl::fromLocalFile(*it));
        play_pause=0;
        cur_song=1;
        ui->label_cur_song->setNum(cur_song);
        v.clear();
        name="";
        for(int i=21;(i<it->length()-4);i++)
        {
            v.push_back(it->at(i));
        }
        for(auto i=0;i<(int)v.size();i++)
        {
            name+=v[i];
        }
        ui->label_titlesong->setText("");
        ui->label_titlesong->setText(name);
        updateDurationInfo();
    }
}



void MyApp::on_pushButton_prev_clicked()
{
    if(ui->horizontalSlider->sliderPosition()>(ui->horizontalSlider->maximum()/70))
    {
        player->setMedia(QUrl::fromLocalFile(*it));
        if(Isplaying==true)
            player->play();
        else
            player->pause();
        v.clear();
        name="";
        for(int i=21;(i<it->length()-4);i++)
        {
            v.push_back(it->at(i));
        }
        for(auto i=0;i<(int)v.size();i++)
        {
            name+=v[i];
        }
        ui->label_titlesong->setText("");
        ui->label_titlesong->setText(name);
    }
    else
    {
        if(it==s.begin())
        {
          it=s.end();
          it--;
          player->setMedia(QUrl::fromLocalFile(*it));
          Isplaying=false;
          play_pause=0;
          cur_song=s.size();;
          ui->label_cur_song->setNum(cur_song);
          v.clear();
          name="";
          for(int i=21;(i<it->length()-4);i++)
          {
              v.push_back(it->at(i));
          }
          for(auto i=0;i<(int)v.size();i++)
          {
              name+=v[i];
          }
          ui->label_titlesong->setText("");
          ui->label_titlesong->setText(name);
        }
        else
        {
            it--;
            player->setMedia(QUrl::fromLocalFile(*it));
            if(Isplaying==true)
                player->play();
            else
                player->pause();
            cur_song--;
            ui->label_cur_song->setNum(cur_song);
            v.clear();
            name="";
            for(int i=21;(i<it->length()-4);i++)
            {
                v.push_back(it->at(i));
            }
            for(auto i=0;i<(int)v.size();i++)
            {
                name+=v[i];
            }
            ui->label_titlesong->setText("");
            ui->label_titlesong->setText(name);
        }
    }
}

/*
void MyApp::on_horizontalSlider_actionTriggered(int action)
{
    player->setPosition(action);
}
*/


void MyApp::on_horizontalSlider_sliderMoved(int position)
{
    player->setPosition(position);
}


void MyApp::on_pushButton_clicked()
{
    if(mute==true)
    {
        player->setMuted(true);
        mute=false;
    }
    else
    {
        player->setMuted(false);
        mute=true;
    }
}


void MyApp::on_horizontalSlider_valueChanged(int value)
{
    if(value==ui->horizontalSlider->maximum())
    {
        it++;
        if(it!=s.end())
        {
            player->setMedia(QUrl::fromLocalFile(*it));
            if(Isplaying==true)
                player->play();
            else
                player->pause();
            ui->label_cur_song->setNum(++cur_song);
            v.clear();
            name="";
            for(int i=21;(i<it->length()-4);i++)
            {
                v.push_back(it->at(i));
            }
            for(auto i=0;i<(int)v.size();i++)
            {
                name+=v[i];
            }
            ui->label_titlesong->setText("");
            ui->label_titlesong->setText(name);
        }
        else
        {
            it=s.begin();
            player->setMedia(QUrl::fromLocalFile(*it));
            play_pause=0;
            ui->label_cur_song->setNum(1);
            v.clear();
            name="";
            for(int i=21;(i<it->length()-4);i++)
            {
                v.push_back(it->at(i));
            }
            for(auto i=0;i<(int)v.size();i++)
            {
                name+=v[i];
            }
            ui->label_titlesong->setText("");
            ui->label_titlesong->setText(name);
        }


    }
}


void MyApp::on_verticalSlider_sliderPressed()
{
    ui->verticalSlider->setCursor(Qt::ClosedHandCursor);
}


void MyApp::on_verticalSlider_sliderReleased()
{
    ui->verticalSlider->setCursor(Qt::OpenHandCursor);
}


void MyApp::on_actionClose_triggered()
{
    QApplication::quit();
}

void MyApp::on_actionOpen_triggered()
{
    QString filename= QFileDialog::getOpenFileName(this,"Add a playlist","D:/Users/idris/Music");
    for(auto i:s)
    {
    if(filename == i)
    {
        QMessageBox::information(this, "Error","Connot add this playlist, it's already there!");
        filename=nullptr;
        break;
    }
    }
    if(filename!=nullptr)
    {
        s.push_back(filename);
        ui->label_tot_song->setNum(int(s.size()));
    }
}

void MyApp::on_actionFrequency_triggered()
{
    Frequency myFreq;
    myFreq.exec();
}

void MyApp::on_actionPause_triggered()
{
    on_pushButton_play_pause_clicked();
}

void MyApp::on_actionPrevious_triggered()
{
    on_pushButton_prev_clicked();
}

void MyApp::on_actionnext_triggered()
{
    on_pushButton_next_clicked();
}

void MyApp::on_actionJump_to_begin_triggered()
{
    it=s.begin();
    play_pause=0;
    player->setMedia(QUrl::fromLocalFile(*it));
    v.clear();
    name="";
    for(int i=21;(i<it->length()-4);i++)
    {
        v.push_back(it->at(i));
    }
    for(auto i=0;i<(int)v.size();i++)
    {
        name+=v[i];
    }
    ui->label_titlesong->setText("");
    ui->label_titlesong->setText(name);
    cur_song=1;
    ui->label_cur_song->setNum(cur_song);
}

void MyApp::on_actionJump_to_end_triggered()
{
    it=s.end();
    it--;
    play_pause=0;
    player->setMedia(QUrl::fromLocalFile(*it));
    v.clear();
    name="";
    for(int i=21;(i<it->length()-4);i++)
    {
        v.push_back(it->at(i));
    }
    for(auto i=0;i<(int)v.size();i++)
    {
        name+=v[i];
    }
    ui->label_titlesong->setText("");
    ui->label_titlesong->setText(name);
    cur_song=s.size();
    ui->label_cur_song->setNum(cur_song);
}

void MyApp::on_actionVersion_triggered()
{
    QMessageBox::information(this,"Version","1.0.0",QMessageBox::Ok,QMessageBox::Help);
}

void MyApp::durationChanged(qint64 duration)
{
    m_duration = duration / 1000;
}

void MyApp::updateDurationInfo(void)
{
    ui->label_min->setNum((int)(m_duration/60));
    ui->label_sec->setNum((int)(m_duration%60));
}
