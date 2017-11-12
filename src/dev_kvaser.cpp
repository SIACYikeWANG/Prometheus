/*************************************************************************
	> File Name: dev_kvaser.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月12日 星期日 15时50分30秒
 ************************************************************************/

#include"dev_kvaser.h"
#include"unistd.h"
#include"pthread.h"
#include<iostream>

using namespace std;

/*
int InitKvaser(int baudrate, int channel)
{
    int result = 1;
    int stat;
    m_DriverConfig->Channel[channel].driverMode = canDRIVER_NORMAL;
    canInitializeLibrary();
    canHandle hnd;

    hnd = canOpenChannel(channel, canOPEN_OVERRIDE_EXCLUSIVE);
    if( hnd < 0 )
    {
        // 打开错误
        qDebug("Open Kvaser Error.\n");
    }
    else
    {
        // 成功打开
        qDebug("Open Kvaser successfully.\n");

        m_channelData.Channel[channel].hnd = hnd;
        if ((stat = canIoCtl(hnd, canIOCTL_FLUSH_TX_BUFFER, NULL, NULL)) != canOK)
        qDebug("ERROR canIoCtl(canIOCTL_FLUSH_TX_BUFFER) FAILED, Err= %d <line: %d>\n", stat, __LINE__);

        // 配置波特率
        switch(baudrate)
        {
        case 125:
            m_usedBaudRate = BAUD_125K;
            break;
        case 250:
            m_usedBaudRate = BAUD_250K;
            break;
        case 500:
            m_usedBaudRate = BAUD_500K;
            break;
        case 1000:
            m_usedBaudRate = BAUD_1M;
            break;
        default:
            m_usedBaudRate = BAUD_500K;
        }
        stat = canSetBusParams(hnd, m_usedBaudRate, 0, 0, 0, 0, 0);

        canBusOn(hnd);

        result = 0;
    }
    return result;
}


int CloseKvaser(int channel)
{
    int result = 0;
    int stat;

    stat = canBusOff(m_channelData.Channel[channel].hnd);
    if( stat != canOK)
    {
        qDebug("ERROR canBusOff() FAILED Err= %d. <line: %d>\n", stat, __LINE__);
        result = 1;
    }

    stat = canClose(m_channelData.Channel[channel].hnd);
    if (stat != canOK)
    {
        qDebug("ERROR canClose() in Cleanup() FAILED Err= %d. <line: %d>\n",
                      stat, __LINE__);
        result = 1;
    }

    return result;
}

// frameType:0=standard frame, 1=extend frame
canStatus TransmitMsg(int channel, long canId, byte data[], int dataLen, int frameType)
{
    WORD FT = canMSG_STD;
    canStatus result;
    if (g_ObserverFlag == true)
    {
        return result;
    }
    switch(frameType)
    {
    case 0:
        FT = canMSG_STD;
        break;
    case 1:
        FT = canMSG_EXT;
        break;
    }
    if (g_ComDevice == 1)
    {
        result = canOK;
        stg_EthCom.sendCanMsg(channel, canId, (char *)data, dataLen, frameType);

    }
    else if( g_ComDevice == 0)
    {
        result = canWrite(m_DriverConfig->Channel[channel].hnd, canId, data, dataLen, FT);
    }
    return result;
}
*/

int StartCanRxMsgTask(pthread_t pth,int kvaserChannelNo)
{
    int result = 0;

    if (kvaserChannelNo < 0 || kvaserChannelNo > 3)
    {
        result = 1;
    }
    else
    {
        switch (kvaserChannelNo)
        {
        case 0:
            result = pthread_create(&pth, NULL, Proc_Can0RxMsg, NULL);
            break;
        case 1:
            result = pthread_create(&pth, NULL, Proc_Can0RxMsg, NULL);
            break;
        case 2:
            result = pthread_create(&pth, NULL, Proc_Can0RxMsg, NULL);
            break;
        case 3:
            result = pthread_create(&pth, NULL, Proc_Can0RxMsg, NULL);
            break;
        default:
            break;
        }
    }

    return result;
}

int StartCanTxMsgTask(pthread_t pth,int kvaserChannelNo)
{
    int result = 0;
    pthread_t pth;
    if (kvaserChannelNo < 0 || kvaserChannelNo > 3)
    {
        result = 1;
    }
    else
    {
        switch (kvaserChannelNo)
        {
        case 0:
            result = pthread_create(&pth, NULL, Proc_Can0TxMsg, NULL);
            break;
        case 1:
            result = pthread_create(&pth, NULL, Proc_Can0TxMsg, NULL);
            break;
        case 2:
            result = pthread_create(&pth, NULL, Proc_Can0TxMsg, NULL);
            break;
        case 3:
            result = pthread_create(&pth, NULL, Proc_Can0TxMsg, NULL);
            break;
        default:
            break;
        }
    }

    return result;
}

void* Proc_Can0TxMsg(void *arg)
{
    while(1)
    {
        cout<<"Can Message Send!"<<endl;
        usleep(50000);
    }
    return (void*)0;
}

void* Proc_Can0RxMsg(void *arg)
{
    while(1)
    {
        cout<<"Can Message Received!"<<endl;
        usleep(50000);
    }
    return (void*)0;
}
