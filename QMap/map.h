#ifndef MAP_H
#define MAP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Map; }
QT_END_NAMESPACE

class Map : public QMainWindow
{
    Q_OBJECT

public:
    Map(QWidget *parent = nullptr);
    ~Map();

private:
    Ui::Map *ui;
};
#endif // MAP_H
