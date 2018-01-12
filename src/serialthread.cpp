#include "serialthread.h"
#include <QtDebug>

SerialThread::SerialThread()
{
    memset(rxDataTemp,0,53);
    memset(rxData,0,53);
}

SerialThread::~SerialThread()
{
    terminate();
    wait();
}

void SerialThread::run()
{
    QSerialPort qSerialPort;

    QString portName = "/dev/ttyUSB0";
    qSerialPort.setPortName(portName);

    if(qSerialPort.open(QIODevice::ReadOnly))
    {
        qSerialPort.setBaudRate(QSerialPort::Baud115200);
        qSerialPort.setParity(QSerialPort::NoParity);
        qSerialPort.setDataBits(QSerialPort::Data8);
        qSerialPort.setStopBits(QSerialPort::OneStop);
        qSerialPort.setFlowControl(QSerialPort::NoFlowControl);

        qSerialPort.clearError();
        qSerialPort.clear();
    }
    else
    {
        qDebug()<<"Open SerialPort Failed!";
    }

    qint64 dLength = qSerialPort.read(rxData,53);
//    qint64 it_ = 0;

    while(qSerialPort.waitForReadyRead(5000))
    {

        dLength = qSerialPort.read(rxData,53);
        dataProc((int)dLength);
    }

    if(qSerialPort.error() == QSerialPort::ReadError)
    {
        qDebug()<<"Read Error!";
    }
    else if(qSerialPort.error() == QSerialPort::TimeoutError)
    {
        qDebug()<<"No data received!";
    }
}

/*
void SerialThread::dataProc()
{
    float tempFloat;
    float heading=0;
    float eastVel=0;
    float northVel=0;
    float lonVel=0;
    float latVel=0;
//    unsigned char temp;
    int id = 0;

    for(int i=0;i<106;i++)
    {
        if((((unsigned char)rxData[i])==0xAA) &&
           (((unsigned char)rxData[i+1])==0x55) &&
           (((unsigned char)rxData[i+2])==0x01))
        {
            id = i;
            break;
        }
    }

    for(int j=0;j<53;j++)
    {
        rxDataTemp[j] = (unsigned char)rxData[j+id];
    }

    char checkSum = 0;
    for(int j=0;j<52;j++)
    {
        checkSum+=rxDataTemp[j];
        cout<<rxDataTemp;
    }
    cout<<endl;

    if(checkSum==rxDataTemp[52])
    {
//                    memcpy(&tempU16, bufProc + 3, 2);
//                    g_ins.week = tempU16;
//                    memcpy(&tempU32, bufProc + 2 + 3, 4);
//                    g_ins.gps_time = (double)tempU32 / 1000.0;
        memcpy(&tempFloat, rxDataTemp + 6 + 3, 4);
        heading = tempFloat * 3.1415926 / 180.00;
//                    dbHeadingRadian = g_ins.heading * PI / 180.00;
//                    memcpy(&tempFloat, bufProc + 10 + 3, 4);
//                    g_ins.pitch = tempFloat;
//                    memcpy(&tempFloat, bufProc + 14 + 3, 4);
//                    g_ins.roll = tempFloat;
//                    memcpy(&tempU32, bufProc + 18 + 3, 4);
//                    g_ins.lat = tempU32*1e-7;
//                    memcpy(&tempU32, bufProc + 22 + 3, 4);
//                    g_ins.lon = tempU32*1e-7;
//                    memcpy(&tempU32, bufProc + 26 + 3, 4);
//                    g_ins.height = tempU32*1e-3;

        memcpy(&tempFloat, rxDataTemp + 30 + 3, 4);
        eastVel = tempFloat;
        memcpy(&tempFloat, rxDataTemp + 34 + 3, 4);

        northVel = tempFloat;
//                    memcpy(&tempFloat, bufProc + 38 + 3, 4);
//                    g_ins.down_speed = tempFloat;
//                    memcpy(&tempU8, bufProc + 48 + 3, 1);
//                    g_ins.n = tempU8;

        lonVel = eastVel * sin(heading) + northVel * cos(heading);
        latVel = eastVel * cos(heading) - northVel * sin(heading);

        VehSts_LonVel_A8_CAN1 = double(lonVel*3.6);

//        qDebug()<<"lonVel = "<<lonVel<<"; latVel = "<<latVel;
//        memset(rxData,0,53);
//        memset(rxDataTemp,0,53);
    }
    else
    {
        qDebug()<<"Checksum error!";
    }
}
*/

void SerialThread::dataProc(int dLength)
{
    float tempFloat;
    float heading=0;
    float eastVel=0;
    float northVel=0;
    float lonVel=0;
    float latVel=0;

    if(dLength>0)
    {
        for(int i=0;i<dLength;i++)
        {
            memmove(rxDataTemp,rxDataTemp+1,52);
            rxDataTemp[52] = (unsigned char)rxData[i];

//            cout<<hex<<(unsigned int)rxDataTemp[52]<<endl;

            if(rxDataTemp[0]==0xAA && rxDataTemp[1]==0x55 && rxDataTemp[2]==0x01)
            {
                unsigned char checkSum = 0;
                for(int j=0;j<52;j++)
                {
                    checkSum+=rxDataTemp[j];
                }

                if(checkSum==rxDataTemp[52])
                {
//                    memcpy(&tempU16, bufProc + 3, 2);
//                    g_ins.week = tempU16;
//                    memcpy(&tempU32, bufProc + 2 + 3, 4);
//                    g_ins.gps_time = (double)tempU32 / 1000.0;
                    memcpy(&tempFloat, rxDataTemp + 6 + 3, 4);
                    heading = tempFloat * 3.1415926 / 180.00;
//                    dbHeadingRadian = g_ins.heading * PI / 180.00;
//                    memcpy(&tempFloat, bufProc + 10 + 3, 4);
//                    g_ins.pitch = tempFloat;
//                    memcpy(&tempFloat, bufProc + 14 + 3, 4);
//                    g_ins.roll = tempFloat;
//                    memcpy(&tempU32, bufProc + 18 + 3, 4);
//                    g_ins.lat = tempU32*1e-7;
//                    memcpy(&tempU32, bufProc + 22 + 3, 4);
//                    g_ins.lon = tempU32*1e-7;
//                    memcpy(&tempU32, bufProc + 26 + 3, 4);
//                    g_ins.height = tempU32*1e-3;

                    memcpy(&tempFloat, rxDataTemp + 30 + 3, 4);
                    eastVel = tempFloat;
                    memcpy(&tempFloat, rxDataTemp + 34 + 3, 4);

                    northVel = tempFloat;
//                    memcpy(&tempFloat, bufProc + 38 + 3, 4);
//                    g_ins.down_speed = tempFloat;
//                    memcpy(&tempU8, bufProc + 48 + 3, 1);
//                    g_ins.n = tempU8;

                    lonVel = eastVel * sin(heading) + northVel * cos(heading);
                    latVel = eastVel * cos(heading) - northVel * sin(heading);

                    qDebug()<<"lonVel = "<<lonVel<<"; latVel = "<<latVel;
//                    VehSts_LonVel_A8_CAN1 = double(lonVel*3.6);
//                    memset(rxData,0,53);
//                    memset(rxDataTemp,0,53);
                }
                else
                {
                    qDebug()<<"Checksum error!";
                }
            }
        }
    }
}
