#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qdebug.h>
#include <QList>
#include <user.h>
#include <contact.h>

#include <pjsua.h>
#include <vidwin.h>
#include <qmediaplayer.h>
#include <qmainwindow.h>
#include <call.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    MainWindow* this_;

    bool initStack();
    void handleIncomingCall(pjsua_acc_id acc_id, pjsua_call_id call_id,
                            pjsip_rx_data *rdata);


    QList<User> users;
    pjsua_acc_id account_id;
    QList<QString> m_current_calls;
    QList<VidWin*> m_current_videos;



    VidWin* video_prev;
    VidWin* video_;
    QMediaPlayer* ringtone;
    void test();

    Call* call;

    void show_incoming_call(QString);




signals:
     void sig_incoming_call(QString, QString);
     void sig_init_video_win(int call_id);



public slots:
    void handleCall(QString, QString);
    void initVideoWin(int);


private:
    Ui::MainWindow *ui;
    static MainWindow *instance();

};
#endif // MAINWINDOW_H
