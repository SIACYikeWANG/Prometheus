/*************************************************************************
	> File Name: dev_kvaser.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月12日 星期日 15时50分30秒
 ************************************************************************/

#include"dev_kvaser.h"
#include"dbcparser.h"
#include"body_dbc_conf.h"
#include"unistd.h"
#include"pthread.h"
#include<iostream>

using namespace std;

extern DbcParserMsgTblType TBL_DP_DBCMSGLIST_Body_dbc_cfg[];
extern uint16 u16s_dp_MsgTblSize_body_dbc_cfg;

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
}*/

// frameType:0=standard frame, 1=extend frame
//canStatus TransmitMsg(long canId, byte data[], int dataLen, int frameType)
//{

//    canStatus result;

//    result = canWrite(m_DriverConfig->Channel[channel].hnd, canId, data, dataLen, frameType);

//    return result;
//}


void StartCanRxMsgTask(pthread_t* pth, KvrChannel* kvrObj)
{
    int result = 0;

    if (kvrObj->getIDChl() < 0 || kvrObj->getIDChl() > 3)
    {
        result = 1;
    }
    else
    {
        switch (kvrObj->getIDChl())
        {
        case 0:
            result = pthread_create(pth, NULL, Proc_Can0RxMsg, (void*)kvrObj);
            break;
        case 1:
            result = pthread_create(pth, NULL, Proc_Can0RxMsg, (void*)kvrObj);
            break;
        case 2:
            result = pthread_create(pth, NULL, Proc_Can0RxMsg, (void*)kvrObj);
            break;
        case 3:
            result = pthread_create(pth, NULL, Proc_Can0RxMsg, (void*)kvrObj);
            break;
        default:
            break;
        }
    }

    if(result)
    {
        cout<<"Create Thread "<< kvrObj->getIDChl() <<" failed!"<<endl;
    }
    else
    {
        cout<<"Create Thread "<< kvrObj->getIDChl() <<" successful!"<<endl;
    }
}

void StartCanTxMsgTask(pthread_t* pth,KvrChannel* kvrObj)
{
    int result = 0;
    //pthread_t pth;
    if (kvrObj->getIDChl() < 0 || kvrObj->getIDChl() > 3)
    {
        result = 1;
    }
    else
    {
        switch (kvrObj->getIDChl())
        {
        case 0:
            result = pthread_create(pth, NULL, Proc_Can0TxMsg, (void*)kvrObj);
            break;
        case 1:
            result = pthread_create(pth, NULL, Proc_Can0TxMsg, (void*)kvrObj);
            break;
        case 2:
            result = pthread_create(pth, NULL, Proc_Can0TxMsg, (void*)kvrObj);
            break;
        case 3:
            result = pthread_create(pth, NULL, Proc_Can0TxMsg, (void*)kvrObj);
            break;
        default:
            break;
        }
    }

    if(result)
    {
        cout<<"Create Thread "<< kvrObj->getIDChl() <<" failed!"<<endl;
    }
    else
    {
        cout<<"Create Thread "<< kvrObj->getIDChl() <<" successful!"<<endl;
    }
}

void* Proc_Can0TxMsg(void *arg)
{
    KvrChannel *kvrChl = (KvrChannel *)arg;

//    unsigned char data[8];
//    for(int i=0;i<8;i++)
//    {
//        data[i]=1;
//    }

    while(1)
    {
//        cout<<"Can Message Send!"<<endl;
        //ptr->setStatus(canWrite(ptr->getHandle(),0x11,data,8,canMSG_STD));
        ecal_com_dp_ContructMsg(kvrChl, 0x112, TBL_DP_DBCMSGLIST_Body_dbc_cfg, u16s_dp_MsgTblSize_body_dbc_cfg);
        usleep(50000);
    }

    canClose(kvrChl->getHandle());

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
