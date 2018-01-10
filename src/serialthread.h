#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include <unistd.h>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialThread : public QThread
{
    Q_OBJECT
public:
    SerialThread();
    ~SerialThread();

    void dataProc(int dLength);

private:
//    QSerialPort qSerialPort;
//    QByteArray rxByteData;
    char rxData[53];
    unsigned char rxDataTemp[53];


protected:
    void run();
};

#endif // SERIALTHREAD_H
