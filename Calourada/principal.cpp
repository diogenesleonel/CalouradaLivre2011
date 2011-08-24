#include "principal.h"
#include <QString>

#define _TTY_WIN_
#include "C:\qextserialport\qextserialbase.h"
#include "C:\qextserialport\qextserialport.h"

Principal::Principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);
    time = new QTimer(this);

    led1Status = false;
    led2Status = false;
    motorStatus = false;

    serial=new QextSerialPort(QString("COM4"));

    serial->setBaudRate(BAUD9600);
    serial->setDataBits(DATA_8);
    serial->setParity(PAR_NONE);
    serial->setStopBits(STOP_1 );
    serial->setFlowControl(FLOW_OFF );
    serial->setTimeout(0,10);

    if(serial->open(QIODevice::ReadWrite))
    {
        qDebug()<< "conectado";

    }

    connect(time,SIGNAL(timeout()),this,SLOT(showData()));
//    connect(serial,SIGNAL(readyRead()),this,SLOT(showData()));
    time->start(1000);
//    showData();


}

int Principal::receive(int count, char *bytes)
{
        return serial->readData(bytes, count);
}

Principal::~Principal()
{
    delete ui;
}

void Principal::showData()
{

    char buffer[256];
    int rec=receive(255,buffer);
    buffer[rec]='\0';

    qDebug()<< QString::fromLocal8Bit(buffer,rec) <<rec;




}

void Principal::send(int count, char *bytes)
{
        serial->writeData(bytes, count);
        serial->flush();
}

void Principal::on_pushButton_clicked(bool checked)
{
    led1Status=!led1Status;

    char *u = new char[3];
    u[0]=0x01;
    if(led1Status)
        ui->pushButton->setIcon(QIcon(QString::fromUtf8(":/img/on")));
    else
        ui->pushButton->setIcon(QIcon(QString::fromUtf8(":/img/off")));

    ui->pushButton->setIconSize(QSize(30, 30));


    send(1,u);
}

void Principal::on_pushButton_2_clicked()
{

    led2Status=!led2Status;

    char *u = new char[3];
    u[0]=0x10;
    if(led2Status)
        ui->pushButton_2->setIcon(QIcon(QString::fromUtf8(":/img/on")));
    else
        ui->pushButton_2->setIcon(QIcon(QString::fromUtf8(":/img/off")));

    ui->pushButton_2->setIconSize(QSize(30, 30));


    send(1,u);


}

void Principal::on_pushButton_3_clicked()
{
    motorStatus=!motorStatus;

    char *u = new char[3];
    u[0]=0x04;

    send(1,u);
}
