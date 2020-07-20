#include "qanalog_clock.h"
#include <QPainter>
#include <QTime>

QAnalog_Clock::QAnalog_Clock(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Analog Clock"));
    resize(500,500);

    timer.setParent(this);
    connect(&timer, SIGNAL(timeout()),this, SLOT(update()));
    timer.start(100);
}

void QAnalog_Clock::paintEvent(QPaintEvent*)
{
    int side = qMin(width(),height());
    QTime time=QTime::currentTime();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.translate(width()/2,height()/2);
    painter.scale(side/200.0,side/200.0);
    for(int sec=0;sec<=60;sec++)
    {
        if(sec%5==0)
            painter.drawLine(QPoint(0,81),QPoint(0,98));
        else
            painter.drawLine(QPoint(0,90),QPoint(0,98));
        painter.rotate(6);
    }
    double hour=time.hour(), min=time.minute(), sec=time.second(), msec=time.msec();
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    {
        static const QPoint hourHand[3]={QPoint(8,8),QPoint(-8,8),QPoint(0,-60)};
        painter.save();
        double hour_l=hour+(min/60.0)+(sec/3600.0)+(msec/3600000.0);
        painter.rotate(30.0*hour_l);
        painter.drawConvexPolygon(hourHand,3);
        painter.restore();
    }
    {
        static const QPoint minHand[3]={QPoint(6,8),QPoint(-6,8),QPoint(0,-70)};
        painter.save();
        double min_l=min+(sec/60.0)+(msec/60000.0);
        painter.rotate(6.0*min_l);
        painter.drawConvexPolygon(minHand,3);
        painter.restore();
    }
    {
        static const QPoint secHand[3]={QPoint(4,8),QPoint(-4,8),QPoint(0,-80)};
        painter.save();
        double sec_l=sec+(msec/1000);
        painter.rotate(6.0*sec_l);
        painter.drawConvexPolygon(secHand,3);
        painter.restore();
    }
}
QAnalog_Clock::~QAnalog_Clock()
{
}
