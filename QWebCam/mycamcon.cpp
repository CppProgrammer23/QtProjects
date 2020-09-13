#include "mycamcon.h"
#include "ui_mycamcon.h"
#include <QFileDialog>
#include <QMessageBox>

myCamCon::myCamCon(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::myCamCon)
{
    ui->setupUi(this);
    connected=false;
    camera = new QCamera();
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    foreach(const QCameraInfo& cam, cameras)
        ui->deviceSelection->addItem(cam.description());
}

myCamCon::~myCamCon()
{
    delete ui;
}

void myCamCon::connectCamera()
{
    QList<QCameraInfo> cam = QCameraInfo::availableCameras();
    foreach(const QCameraInfo& camInfo, cam)
    {
        if(camInfo.description()==ui->deviceSelection->currentText())
        {
            camera = new QCamera(camInfo);
            viewfinder = new QCameraViewfinder(this);
            camera->setViewfinder(viewfinder);
            ui->verticalLayout_2->addWidget(viewfinder);
            connected = true;
            ui->pushButton_Connect->setStyleSheet("image: url(:/Images/cam_on.png);");

            camera->start();

            break;
        }
    }
}


void myCamCon::on_pushButton_Connect_clicked()
{
    if(!connected)
        connectCamera();
    else
    {
        camera->stop();
        viewfinder->deleteLater();
        ui->pushButton_Connect->setStyleSheet("image: url(:/Images/cam_off.png);");

        connected = false;
    }
}

void myCamCon::on_pushButton_cap_clicked()
{
    if(connected)
    {
        cap = new QCameraImageCapture(camera);
        camera->setCaptureMode(QCamera::CaptureStillImage);
        camera->searchAndLock();
        cap->capture(QFileDialog::getSaveFileName(nullptr,QString(),QString(),"Image file (*.png,*.jpg,*.jpeg,*.jiff )"));
        camera->unlock();
    }
    else
        QMessageBox::information(this, "Error", "<font color = 'red'>Camera not connected.<br>"
                                                "Connect the camera first!</font>",QMessageBox::Ok);
}

void myCamCon::on_pushButton_rec_clicked()
{

}
