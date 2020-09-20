#include "map.h"
#include "ui_map.h"

Map::Map(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Map)
{
    ui->setupUi(this);
}

Map::~Map()
{
    delete ui;
}

