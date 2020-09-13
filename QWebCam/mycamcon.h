#ifndef MYCAMCON_H
#define MYCAMCON_H

#include <QMainWindow>
#include <QCameraInfo>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui { class myCamCon; }
QT_END_NAMESPACE

class myCamCon : public QMainWindow
{
    Q_OBJECT

public:
    myCamCon(QWidget *parent = nullptr);
    ~myCamCon();
    void connectCamera();

private slots:
    void on_pushButton_Connect_clicked();

    void on_pushButton_cap_clicked();

    void on_pushButton_rec_clicked();

private:
    Ui::myCamCon *ui;
    QCamera *camera;
    QCameraViewfinder *viewfinder;
    bool connected;
    QCameraImageCapture *cap;
};
#endif // MYCAMCON_H
