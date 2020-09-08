#include "machinehealth.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MachineHealth w;
    w.show();
    return a.exec();
}
