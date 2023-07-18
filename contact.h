#ifndef CONTACT_H
#define CONTACT_H

#include <QWidget>
#include <qdebug.h>
#include <qdialog.h>
#include <user.h>

namespace Ui {
class Contact;
}

class Contact : public QWidget
{
    Q_OBJECT

public:
    explicit Contact(QWidget *parent = nullptr);
    ~Contact();

private slots:
    void on_addContactBtn_clicked();

private:
    Ui::Contact *ui;
};

#endif // CONTACT_H
