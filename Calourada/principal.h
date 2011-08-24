#ifndef OPENSERIAL
#define OPENSERIAL

#include <QMainWindow>
class QextSerialPort;
#include <QDebug>
#include <QTimer>
#include "ui_principal.h"
#include "Protocol.h"


namespace Ui {
    class Principal;
}

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = 0);
    int receive(int count, char *bytes);
    void send(int count, char *bytes);




    ~Principal();

private:
    Ui::Principal *ui;
    QextSerialPort *serial;
    QTimer *time;

    bool led1Status;
    bool led2Status;
    bool motorStatus;
public slots:
    void showData();
private slots:
    void on_pushButton_clicked(bool checked);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif // PRINCIPAL_H
