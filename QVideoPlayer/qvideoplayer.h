#ifndef QVIDEOPLAYER_H
#define QVIDEOPLAYER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QTime>
#include <QVideoWidget>
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui { class QVideoPlayer; }
QT_END_NAMESPACE

class QVideoPlayer : public QMainWindow
{
    Q_OBJECT

public:
    QVideoPlayer(QWidget *parent = nullptr);
    ~QVideoPlayer();

    void timeChanged(qint64);
    //void durationChanged(qint64);

private slots:
    void on_play_pausebutton_clicked();

    void on_horizontalSlider_time_sliderMoved(int position);

    void on_soundSlider_sliderMoved(int position);

    void on_pushButton_clicked();

    void on_actionOpen_triggered();

    void on_actionQuit_triggered();

    void on_nextbutton_clicked();

    void on_actionJump_to_begin_triggered();

    void on_actionJump_to_end_triggered();

    void on_back_button_clicked();

private:
    Ui::QVideoPlayer *ui;
    QMediaPlayer *player;
    bool play, mute;
    qreal linearVolume;
    std::map<QString,QString> avSongs;
    std::map<QString,QString>::iterator it;
    int i = 0;
};
#endif // QVIDEOPLAYER_H
