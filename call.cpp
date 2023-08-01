#include "call.h"
#include "ui_call.h"
#include "vidwin.h"

Call::Call(QString acc_id, QString call_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Call)
{
    ui->setupUi(this);
    this->m_current_call_id = call_id;
    this->m_current_acc_id = acc_id;

    ui->label->setText("Incoming Call from " + acc_id);

}

Ui::Call * Call::getUi()
{
        return ui;
}

void Call::addVideo(VidWin* video)
{
    video->putIntoLayout(ui->videoBox);
//    ui->videoBox->addWidget(call);

}

Call::~Call()
{
    delete ui;
}




void Call::on_pb_hangCall_clicked()
{
    pjsua_call_hangup(m_current_call_id.toInt(), 603, NULL, NULL);
    emit sig_call_hangup();

}


void Call::on_pb_pickCall_clicked()
{
    pjsua_call_setting call_conf;
    pjsua_call_setting_default(&call_conf);
    call_conf.vid_cnt = PJ_TRUE;
    pjsua_call_answer2(m_current_call_id.toInt(), &call_conf, 200, NULL, NULL);
    emit sig_call_pickedUp();
}


void Call::init_video_win()
{

}

