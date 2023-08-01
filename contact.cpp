#include "contact.h"
#include "ui_contact.h"
#include <qline.h>
#include <qlineedit.h>
#include <qinputdialog.h>

Contact::Contact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Contact)
{
    ui->setupUi(this);

}

Contact::~Contact()
{
    delete ui;
}

void Contact::on_addContactBtn_clicked()
{
    qDebug() << "Adding to contact";

        qDebug() << "Adding a new user";

    bool ok = false;
    QString name = QInputDialog::getText(this, "Enter Name", "User Name", QLineEdit::Normal, "salman khan", &ok);
    if(!ok) {
        return;
    }
    QString ip = QInputDialog::getText(this, "Enter IP Address", "IP Address", QLineEdit::Normal, "192.168.x.x", &ok);
    if(!ok) {
        return;
    }

    User* user = new User(name, ip);
    ui->usersLayout->addWidget(user);
}

