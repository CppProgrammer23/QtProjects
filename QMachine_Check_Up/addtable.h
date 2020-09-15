#ifndef ADDTABLE_H
#define ADDTABLE_H

#include <QDialog>
#include "machinehealth.h"

namespace Ui {
class AddTable;
}

class MachineHealth;


class AddTable : public QDialog
{
    Q_OBJECT

public:
    explicit AddTable(QWidget *parent = nullptr);
    ~AddTable();


private slots:
    void on_Ok_clicked();

    void on_Cancel_clicked();

private:
    Ui::AddTable *ui;
public:
    static QString TableName;
};

#endif // ADDTABLE_H
