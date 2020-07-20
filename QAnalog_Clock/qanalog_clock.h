#ifndef QANALOG_CLOCK_H
#define QANALOG_CLOCK_H

#include <QWidget>
#include <QTimer>

class QAnalog_Clock : public QWidget
{
    Q_OBJECT

public:
    QAnalog_Clock(QWidget *parent = nullptr);

    void  paintEvent(QPaintEvent*);
    ~QAnalog_Clock();

private:
    QTimer timer;
};
#endif // QANALOG_CLOCK_H
