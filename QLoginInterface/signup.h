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

    void on_visible_clicked();

private:
    bool verifyMail(const QString&);

    bool verifyPass(const QString&);

    void clearAll();

    void paintEvent(QPaintEvent*) override;

    Ui::SignUp *ui;

    bool visible;
};

#endif // SIGNUP_H

