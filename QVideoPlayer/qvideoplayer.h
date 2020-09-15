#ifndef QVIDEOPLAYER_H
#define QVIDEOPLAYER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QTime>
#include <QVideoWidget>

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

private slots:
    void on_play_pausebutton_clicked();

    void on_horizontalSlider_time_sliderMoved(int position);

    void on_soundSlider_sliderMoved(int position);

    void on_soundSlider_valueChanged(int value);

    void on_pushButton_clicked();

    void on_actionOpen_triggered();

    void on_actionQuit_triggered();

    void on_nextbutton_clicked();

    void on_actionJump_to_begin_triggered();

    void on_actionJump_to_end_triggered();

    void on_back_button_clicked();

    void on_play_pausebutton_pressed();

    void on_play_pausebutton_released();

    void on_nextbutton_pressed();

    void on_nextbutton_released();

    void on_back_button_pressed();

    void on_back_button_released();

    void on_fullScreen_clicked();

private:
    Ui::QVideoPlayer *ui;
    QMediaPlayer *player;
    bool play, mute, full;
    qreal linearVolume;
    QMap<QString,QString> avSongs;
    QMap<QString,QString>::iterator it;
};
#endif // QVIDEOPLAYER_H
