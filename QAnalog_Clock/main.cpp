#include "qanalog_clock.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QAnalog_Clock w;
    w.show();
    return a.exec();
}
