#ifndef MYWEBENGINE_H
#define MYWEBENGINE_H

#include <QMainWindow>
#include<QWebEngineView>
#include <QPaintEvent>
#include <QWebEnginePage>
#include <QWebEngineHistory>
#include "history.h"

QT_BEGIN_NAMESPACE
namespace Ui { class myWebEngine; }
QT_END_NAMESPACE

class myWebEngine : public QMainWindow
{
    Q_OBJECT

public:
    myWebEngine(QWidget *parent = nullptr);
    ~myWebEngine();
    void paintEvent(QPaintEvent*);

private slots:
    void on_back_button_clicked();

    void on_nextbutton_clicked();

    void on_refresbutton_clicked();

    void on_searchbutton_clicked();

    void on_viewwebLoading_valueChanged(int value);

    void Loading();

    void on_print_clicked();

    void on_history_clicked();

    void on_actionSearch_triggered();

    void on_actionBack_triggered();

    void on_actionForward_triggered();

    void on_actionVersion_triggered();

private:
    Ui::myWebEngine *ui;
    QWebEngineView *webview;
    int forward = -1, back = 0;
    QString str;

    QWebEnginePage h;
    QWebEngineHistory *history = h.history();

    History *hs;
public:
    QList<QWebEngineHistoryItem> l;
    static QList<QString> ls;

};
#endif // MYWEBENGINE_H
