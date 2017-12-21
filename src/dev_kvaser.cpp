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
#include "thread_in_rx.h"
#include<iostream>

using namespace std;

extern DbcParserMsgTblType TBL_DP_DBCMSGLIST_Body_dbc_cfg[];
extern uint16 u16s_dp_MsgTblSize_body_dbc_cfg;
extern DbcParserMsgTblType TBL_DP_DBCMSGLIST_DBCTest_dbc_cfg[];
extern uint16 u16s_dp_MsgTblSize_DBCTest_dbc_cfg;

KvaserCanMsgType stg_CanRxMsg_0;

RxSlotType stg_RxSlot[8];

void copyCanDataToBuf(KvaserCanMsgType kvrCanMsg, RxSlotType* pt_slot);
void dispCanMsg(KvaserCanMsgType kvrCanMsg_);

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

/*
 frameType:0=standard frame, 1=extend frame
canStatus TransmitMsg(long canId, byte data[], int dataLen, int frameType)
{

    canStatus result;

    result = canWrite(m_DriverConfig->Channel[channel].hnd, canId, data, dataLen, frameType);

    return result;
}
*/

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

void StartCanParserTask(pthread_t* pth)
{
    int result = pthread_create(pth, NULL, Proc_ParseData_Srv0Can0, (void*)&stg_RxSlot[0]); //　将收到的CAN数据通过DBC解析对应到变量

    if(result)
    {
        cout<<"Create Thread CanMsgParser failed!"<<endl;
    }
    else
    {
        cout<<"Create Thread CanMsgParser successful!"<<endl;
    }
}

void* Proc_Can0TxMsg(void *arg)
{
    KvrChannel *kvrChl = (KvrChannel *)arg;

    while(1)
    {
        ecal_com_dp_ContructMsg(kvrChl, 0x112, TBL_DP_DBCMSGLIST_Body_dbc_cfg, u16s_dp_MsgTblSize_body_dbc_cfg);
        ecal_com_dp_ContructMsg(kvrChl, 0x300, TBL_DP_DBCMSGLIST_Body_dbc_cfg, u16s_dp_MsgTblSize_body_dbc_cfg);
//        ecal_com_dp_ContructMsg(kvrChl, 0x240, TBL_DP_DBCMSGLIST_DBCTest_dbc_cfg, u16s_dp_MsgTblSize_DBCTest_dbc_cfg);
//        ecal_com_dp_ContructMsg(kvrChl, 0x241, TBL_DP_DBCMSGLIST_DBCTest_dbc_cfg, u16s_dp_MsgTblSize_DBCTest_dbc_cfg);
//        ecal_com_dp_ContructMsg(kvrChl, 0x250, TBL_DP_DBCMSGLIST_DBCTest_dbc_cfg, u16s_dp_MsgTblSize_DBCTest_dbc_cfg);
//        ecal_com_dp_ContructMsg(kvrChl, 0x251, TBL_DP_DBCMSGLIST_DBCTest_dbc_cfg, u16s_dp_MsgTblSize_DBCTest_dbc_cfg);

        cout<<"Throttle = "<<ESP_Throttle_300_CAN1;
        cout<<"; EPS Angle Request = "<<EPS_SteeringAngleReq_112_CAN1;
        cout<<"; EPS Status = "<<EPS_StsReq_112_CAN1<<endl;
        usleep(50000);
    }

    canClose(kvrChl->getHandle());

    return (void*)0;
}

void* Proc_Can0RxMsg(void *arg)
{
    KvrChannel *kvrChl = (KvrChannel *)arg;

    canStatus rxStatus;

    while(1)
    {
        bool rxFlag = false;
        rxStatus = canRead(kvrChl->getHandle(),
                           &stg_CanRxMsg_0.CanId,
                           stg_CanRxMsg_0.Data,
                           &stg_CanRxMsg_0.Datalen,
                           &stg_CanRxMsg_0.Flag,
                           &stg_CanRxMsg_0.TimeStamp);
        if(rxStatus == canOK && stg_CanRxMsg_0.CanId != 0)
        {
            rxFlag = true;
            copyCanDataToBuf(stg_CanRxMsg_0,&stg_RxSlot[0]);
            //dispCanMsg(stg_CanRxMsg_0);
        }
        else
        {
            rxStatus = canReadWait(kvrChl->getHandle(),
                                   &stg_CanRxMsg_0.CanId,
                                   stg_CanRxMsg_0.Data,
                                   &stg_CanRxMsg_0.Datalen,
                                   &stg_CanRxMsg_0.Flag,
                                   &stg_CanRxMsg_0.TimeStamp,
                                   10000);
            if(rxStatus == canOK && stg_CanRxMsg_0.CanId != 0)
            {
                rxFlag = true;
                copyCanDataToBuf(stg_CanRxMsg_0,&stg_RxSlot[0]);
                //dispCanMsg(stg_CanRxMsg_0);
            }
        }
        stg_CanRxMsg_0.CanId = 0x0;
    }

    canClose(kvrChl->getHandle());
    return (void*)0;
}

void copyCanDataToBuf(KvaserCanMsgType kvrCanMsg, RxSlotType* pt_slot)
{
    char hd = (char)(kvrCanMsg.Flag << 7 | kvrCanMsg.Datalen);
    if(pt_slot->rxDataInProcFlag == true)
    {
        memcpy(pt_slot->rxBuffer_bkup + pt_slot->rxBkupBufDataLen,&hd,1);
        memcpy(pt_slot->rxBuffer_bkup + pt_slot->rxBkupBufDataLen+1,&kvrCanMsg.CanId,4);
        memcpy(pt_slot->rxBuffer_bkup + pt_slot->rxBkupBufDataLen+5,kvrCanMsg.Data,8);
        pt_slot->rxBkupBufDataLen += 13;
    }
    else
    {
        if(pt_slot->rxBkupBufDataLen != 0)
        {
            memcpy(pt_slot->rxBuffer + pt_slot->rxBufWItr, pt_slot->rxBuffer_bkup, pt_slot->rxBkupBufDataLen);
            pt_slot->rxBufWItr += pt_slot->rxBkupBufDataLen;
            pt_slot->rxBkupBufDataLen = 0;
        }

        memcpy(pt_slot->rxBuffer + pt_slot->rxBufWItr, &hd, 1);
        memcpy(pt_slot->rxBuffer + pt_slot->rxBufWItr+1, &kvrCanMsg.CanId,4);
        memcpy(pt_slot->rxBuffer + pt_slot->rxBufWItr+5, kvrCanMsg.Data,8);
        pt_slot->rxBufWItr += 13;
    }
}

void dispCanMsg(KvaserCanMsgType kvrCanMsg_)
{
    cout<<"Receive Can Data: ";
    for(unsigned int i=0;i<kvrCanMsg_.Datalen;i++)
    {
        cout<<kvrCanMsg_.Data[i];
    }
    cout<<endl;
}
