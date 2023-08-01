#include "user.h"
#include "ui_user.h"
#include <QPixmap>
User::User(QString name, QString ip, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User)
{
    this->m_name = name;
    this->m_ip = ip;

    ui->setupUi(this);

    ui->name->setText(name);
    ui->ip->setText(ip);

    QPixmap pix(":/icons/resources/phone.ico");
    ui->call->setIcon(pix.scaled(30, 30, Qt::KeepAspectRatio));
}

User::~User()
{
    delete ui;
}

void User::on_call_clicked()
{
    qDebug() << "Making call to " << this->m_name << " : " << this->m_ip;
}

