#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>

namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

private slots:
    void on_cancelbutton_clicked();

    void on_okbutton_clicked();

private:
    Ui::SignUp *ui;
};

#endif // SIGNUP_H
