#ifndef LOGININTERFACE_H
#define LOGININTERFACE_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include "signup.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginInterface; }
QT_END_NAMESPACE

class LoginInterface : public QDialog
{
    Q_OBJECT

public:
    LoginInterface(QWidget *parent = nullptr);
    ~LoginInterface();

private slots:
    void on_Login_button_clicked();

    void on_visiblepass_clicked();

    void on_createbutton_clicked();

private:
    Ui::LoginInterface *ui;
    bool visible;
    SignUp *s = new SignUp;

public:
    static QSqlDatabase db;

};
#endif // LOGININTERFACE_H
