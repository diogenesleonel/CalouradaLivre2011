#include "SerialPort.h"

// Specify the MSWindows naming scheme (COM1, COM2, ...)
#define _TTY_WIN_
#include "C:\qextserialport\qextserialbase.h"
#include "C:\qextserialport\qextserialport.h"

#include <QString>

SerialPort::SerialPort(QWidget *parent) : QDialog(parent)
{
	setupUi(this);
	serial=new QextSerialPort();
	timer=new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(checkPort()));
}

void SerialPort::on_openButton_clicked()
{
	// Make sure things are clear
	serial->close();
	emit(portClosed());
	
	// read in all the settings and open the port
	serial->setPortName(choosePort->currentText());
	switch(chooseBaudRate->currentIndex())
	{
		case 0:
			serial->setBaudRate(BAUD9600);
			break;
		case 1:
			serial->setBaudRate(BAUD19200);
			break;
		case 2:
			serial->setBaudRate(BAUD38400);
			break;
		case 3:
			serial->setBaudRate(BAUD57600);
			break;
		case 4:
			serial->setBaudRate(BAUD115200);
	}
	serial->setDataBits( (DataBitsType)(chooseDataBits->currentIndex()) );
	serial->setParity( (ParityType)(chooseParity->currentIndex()) );
	serial->setStopBits( (StopBitsType)(chooseStopBits->currentIndex()) );
	serial->setFlowControl( (FlowType)(chooseFlowControl->currentIndex()) );
	serial->setTimeout(0,100);
	
	if(serial->open())
	{
		timer->start();
		emit(portOpened());
	}
}

void SerialPort::closePort()
{
	serial->close();
	emit(portClosed());
}

void SerialPort::send(int count, char *bytes)
{
	serial->writeData(bytes, count);
	serial->flush();
}

// read in up to count bytes
// return the number of bytes read
int SerialPort::receive(int count, char *bytes)
{
	return serial->readData(bytes, count);
}

void SerialPort::checkPort()
{
	if(serial->bytesAvailable()>0)
	{
		emit(dataReady());
	}
}
