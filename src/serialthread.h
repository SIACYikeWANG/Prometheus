#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include <unistd.h>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "body_dbc_conf.h"
#include "iostream"

using namespace std;

class SerialThread : public QThread
{
    Q_OBJECT
public:
    SerialThread();
    ~SerialThread();

    void dataProc(int dLength);
//    void dataProc();

private:
//    QSerialPort qSerialPort;
//    QByteArray rxByteData;
    char rxData[53];
    unsigned char rxDataTemp[53];


protected:
    void run();
};

#endif // SERIALTHREAD_H
