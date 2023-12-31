#ifndef CALL_H
#define CALL_H

#include <QWidget>
#include <pjsua.h>

namespace Ui {
class Call;
}

class Call : public QWidget
{
    Q_OBJECT

public:
    explicit Call(QString acc_id, QString call_id, QWidget *parent = nullptr);
    ~Call();

    QString m_current_call_id;
    QString m_current_acc_id;
signals:
    void sig_call_pickedUp();
    void sig_call_hangup();

private slots:
    void on_pb_hangCall_clicked();

    void on_pb_pickCall_clicked();

    void init_video_win();
private:
    Ui::Call *ui;
};

#endif // CALL_H
