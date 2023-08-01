#ifndef USER_H
#define USER_H

#include <QWidget>
#include <QString>
#include <qdebug.h>


namespace Ui {
class User;
}

class User : public QWidget
{
    Q_OBJECT

public:
    explicit User(QString name, QString ip, QWidget *parent = nullptr);
    ~User();


    QString m_name;
    QString m_ip;

private slots:
    void on_call_clicked();

private:
    Ui::User *ui;
};

#endif // USER_H
