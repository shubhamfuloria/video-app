#include "mainwindow.h"
#include "ui_mainwindow.h"


#include<call.h>
#include <SDL.h>
#include <qdialog.h>
#include <qthread.h>
#include <QAudioOutput>
#include <call.h>
#include <QLabel>
#include <QPushButton>

static MainWindow* main_instance;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    main_instance = this;
    Contact* contact = new Contact();
    contact->setFixedWidth(300);

    //set ringtone
    ringtone = new QMediaPlayer;
    ringtone->setMedia(QUrl("qrc:/music/resources/ringtone.mp3"));

    ui->mainLayout->addWidget(contact);
    ui->mainLayout->addStretch();
    video_prev = NULL;


    if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        qDebug() << "Unable to initialize sdl";
        qFatal("Unable to initialize sdl");
    }

    if(!initStack()) {
        qDebug() << "problem in initializing sip stack";
        qFatal("Unable to initialize sip stack");
    }
    video_ = NULL;

    connect(this, SIGNAL(sig_incoming_call(QString, QString)), this, SLOT(handleCall(QString, QString)));

    connect(this, SIGNAL(sig_init_video_win(int)), this, SLOT(initVideoWin(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initVideoWin(pjsua_call_id call_id)
{
    qDebug() << "******************";
    qDebug() << "init video window called";
    qDebug() << QString::number(call_id);
    pjsua_call_info ci;
    unsigned i;


//    delete video_;
    video_ = NULL;

//   making full screen

    for (i = 0; i < ci.media_cnt; ++i) {
        if ((ci.media[i].type == PJMEDIA_TYPE_VIDEO) &&
            (ci.media[i].dir & PJMEDIA_DIR_DECODING))
        {
            pjsua_vid_win_info wi;
            pjsua_vid_win_get_info(ci.media[i].stream.vid.win_in, &wi);

//            video_= new VidWin(&wi.hwnd);
            VidWin* vid = new VidWin(&wi.hwnd);

//            if(m_current_calls.length() >= 1) {
//                qDebug() << "********ADDING TO CONFERENCE*******\n\n\n\n";
//                //make conference
//                pjsua_call_id call_1_id = m_current_calls.at(0).toInt();

//                int call_1_dec_port = pjsua_call_get_vid_conf_port(call_1_id, PJMEDIA_DIR_DECODING);
//                int call_1_enc_port = pjsua_call_get_vid_conf_port(call_1_id, PJMEDIA_DIR_ENCODING);

//                int call_2_dec_port = pjsua_call_get_vid_conf_port(call_id, PJMEDIA_DIR_DECODING);
//                int call_2_enc_port = pjsua_call_get_vid_conf_port(call_id, PJMEDIA_DIR_ENCODING);


//                pj_status_t status;
//                status = pjsua_vid_conf_connect(call_1_dec_port, call_2_enc_port, NULL);
//                status = pjsua_vid_conf_connect(call_2_dec_port, call_1_enc_port, NULL);
//                return;
//            }

            m_current_videos.append(vid);
            qDebug() << "$$$$$$$$$$$$$$";
//            video_->putIntoLayout(ui->mainLayout);
            QWidget* w = new QWidget;
            QBoxLayout* layout = new QHBoxLayout(w);
//            video_->putIntoLayout(layout);
           vid->putIntoLayout(layout);
            w->show();

            break;
        }
    }
}

void on_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id,
                        pjsip_rx_data *rdata)
{
    emit main_instance->sig_incoming_call(QString::number(acc_id), QString::number(call_id));
}


void on_call_state(pjsua_call_id call_id, pjsip_event *e)
{
    qDebug() << "Call state changed";
}

void on_call_media_state(pjsua_call_id call_id)
{
    qDebug() << "call media state changed";
    pjsua_call_info ci;
    pjsua_call_get_info(call_id, &ci);

    for (unsigned i=0; i<ci.media_cnt; ++i) {
        if (ci.media[i].type == PJMEDIA_TYPE_AUDIO) {
            switch (ci.media[i].status) {
            case PJSUA_CALL_MEDIA_ACTIVE:
                pjsua_conf_connect(ci.media[i].stream.aud.conf_slot, 0);
                pjsua_conf_connect(0, ci.media[i].stream.aud.conf_slot);
                break;
            default:
                break;
            }
        } else if (ci.media[i].type == PJMEDIA_TYPE_VIDEO) {
//            emit signalInitVideoWindow();
              emit main_instance->sig_init_video_win(call_id);
        }
    }
}


//temporary function to show incoming call dialog

void MainWindow::show_incoming_call(QString call_id)
{

    QWidget* incomingCall = new QWidget();
    QBoxLayout* vLayout = new QVBoxLayout;


    incomingCall->setLayout(vLayout);
    vLayout->addWidget(new QLabel("Incoming Call..."));

    QBoxLayout* hLayout = new QHBoxLayout;
    QPushButton* acceptBtn = new QPushButton("Accept");

    connect(acceptBtn, &QPushButton::clicked, this, [this, call_id, incomingCall]() {
        pjsua_call_setting call_conf;
        pjsua_call_setting_default(&call_conf);
        call_conf.vid_cnt = PJ_TRUE;
        pjsua_call_answer2(call_id.toInt(), &call_conf, 200, NULL, NULL);
        m_current_calls.append(call_id);
        incomingCall->hide();
    });

    QPushButton* rejectBtn = new QPushButton("Reject");
    connect(rejectBtn, &QPushButton::clicked, this, [call_id, &incomingCall]() {
        pjsua_call_hangup(call_id.toInt(), 603, NULL, NULL);
        incomingCall->hide();
    });


    hLayout->addWidget(acceptBtn);
    hLayout->addWidget(rejectBtn);
    vLayout->addLayout(hLayout);

    incomingCall->show();

    qDebug() << "Activated new Window";
}

void MainWindow::handleCall(QString acc_id, QString call_id)
{
    show_incoming_call(call_id);
//    this->call = new Call(acc_id, call_id);

//    show_incoming_call();

//    ringtone->play();
//    call->show();


//    connect(this->call, &Call::sig_call_pickedUp, this, [this]() {
//        ringtone->stop();
//        call->addVideo(video_);
//    });

//    connect(this->call, &Call::sig_call_hangup, this, [=]() {
//        ringtone->stop();
//        ui->mainLayout->removeWidget(call);
//        delete call;
//    });

}


void MainWindow::handleIncomingCall(pjsua_acc_id acc_id, pjsua_call_id call_id, pjsip_rx_data *rdata)
{

}

void MainWindow::test()
{

}

//initializes the sip application
/*
 *1. pjsua_create()
 *2. create pjsua_config and setup callbacks (eg. on_incoming_call, on_call_state etc)
 *3. pjsua_init(config, log_config, media_config)
 *4. create tcp and udp transports and setup port
 *5. create account config and add account to sip server
 *6. pjsua_start()
*/

bool MainWindow::initStack()
{
    qDebug() << "initializing stack";
    pj_status_t status;
    status = pjsua_create();

    if(status != PJ_SUCCESS)
    {
        qDebug() << "Error while creating stack";
        return false;
    }

    //user agent configuration;
    pjsua_config ua_cfg;
    pjsua_config_default(&ua_cfg);

    pjsua_callback ua_cb;


    ua_cfg.cb.on_incoming_call = &on_incoming_call;
    ua_cfg.cb.on_call_state = &on_call_state;
    ua_cfg.cb.on_call_media_state = &on_call_media_state;



    pjsua_logging_config log_cfg;
    pjsua_logging_config_default(&log_cfg);


    pjsua_media_config media_cfg;
    pjsua_media_config_default(&media_cfg);
    media_cfg.enable_ice = PJ_TRUE;

    status = pjsua_init(&ua_cfg, &log_cfg, &media_cfg);
    if(status != PJ_SUCCESS)
    {
        qDebug() << "Something went wrong in initializing pjsua";
        return false;
    }


    pjsua_transport_config udp_cfg;
    pjsua_transport_id udp_id;
    pjsua_transport_config_default(&udp_cfg);
    udp_cfg.port = 5080;
    status = pjsua_transport_create(PJSIP_TRANSPORT_UDP, &udp_cfg, &udp_id);
    if(status != PJ_SUCCESS)
    {
        qDebug() << "Error while creating pjsip transport";
        return false;
    }

    pjsua_transport_config tcp_cfg;
    pjsua_transport_id tcp_id;
    pjsua_transport_config_default(&tcp_cfg);
    tcp_cfg.port = 0;
    status = pjsua_transport_create(PJSIP_TRANSPORT_TCP, &tcp_cfg, &tcp_id);
    if(status != PJ_SUCCESS)
    {
        qDebug() << "Error while creating tcp pjsip transport";
        return false;
    }

    pjsua_transport_info udp_info;
    status = pjsua_transport_get_info(udp_id, &udp_info);
    if(status != PJ_SUCCESS)
    {
        qDebug() << "Error while getting transport info";
        return false;
    }
    //creating account
    pjsua_acc_config acc_cfg;
    pjsua_acc_config_default(&acc_cfg);
    char sip_id[80];
    snprintf(sip_id, sizeof(sip_id),
        "sip:%s@%.*s:%u", "sampark",
        (int)udp_info.local_name.host.slen,
        udp_info.local_name.host.ptr,
        udp_info.local_name.port);

    acc_cfg.id = pj_str(sip_id);


    acc_cfg.vid_cap_dev = -1;
    acc_cfg.vid_rend_dev = -2;
    acc_cfg.vid_in_auto_show = PJ_TRUE;
    acc_cfg.vid_out_auto_transmit = PJ_TRUE;

    status = pjsua_acc_add(&acc_cfg, PJ_TRUE, &account_id);
    if(status != PJ_SUCCESS)
    {
        qDebug() << "Something went wrong while adding account";
        return false;
    }

    status = pjsua_start();
    if(status != PJ_SUCCESS)
    {
        qDebug() << "PJSUA not able to start";
        return false;
    }

    return true;
}




