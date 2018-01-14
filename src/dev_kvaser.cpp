/*************************************************************************
	> File Name: dev_kvaser.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月12日 星期日 15时50分30秒
 ************************************************************************/

#include "dev_kvaser.h"
#include "dbcparser.h"
#include "body_dbc_conf.h"
#include "unistd.h"
#include "pthread.h"
#include "thread_in_rx.h"
#include <iostream>
#include <time.h>

using namespace std;

extern DbcParserMsgTblType TBL_DP_DBCMSGLIST_Body_dbc_cfg[];
extern uint16 u16s_dp_MsgTblSize_body_dbc_cfg;
extern DbcParserMsgTblType TBL_DP_DBCMSGLIST_DBCTest_dbc_cfg[];
extern uint16 u16s_dp_MsgTblSize_DBCTest_dbc_cfg;

KvaserCanMsgType stg_CanRxMsg_0;
RxSlotType stg_RxSlot[8];


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
//        VehSts_LonVel_A8_CAN1 = 0;
//        VehSts_BeamSts_A8_CAN1 = 2;

//        ecal_com_dp_ContructMsg(kvrChl, 0x112, TBL_DP_DBCMSGLIST_Body_dbc_cfg, u16s_dp_MsgTblSize_body_dbc_cfg);
//        ecal_com_dp_ContructMsg(kvrChl, 0x300, TBL_DP_DBCMSGLIST_Body_dbc_cfg, u16s_dp_MsgTblSize_body_dbc_cfg);
        ecal_com_dp_ContructMsg(kvrChl,  0xA8, TBL_DP_DBCMSGLIST_Body_dbc_cfg, u16s_dp_MsgTblSize_body_dbc_cfg);
//        ecal_com_dp_ContructMsg(kvrChl, 0x240, TBL_DP_DBCMSGLIST_DBCTest_dbc_cfg, u16s_dp_MsgTblSize_DBCTest_dbc_cfg);
//        ecal_com_dp_ContructMsg(kvrChl, 0x241, TBL_DP_DBCMSGLIST_DBCTest_dbc_cfg, u16s_dp_MsgTblSize_DBCTest_dbc_cfg);
//        ecal_com_dp_ContructMsg(kvrChl, 0x250, TBL_DP_DBCMSGLIST_DBCTest_dbc_cfg, u16s_dp_MsgTblSize_DBCTest_dbc_cfg);
//        ecal_com_dp_ContructMsg(kvrChl, 0x251, TBL_DP_DBCMSGLIST_DBCTest_dbc_cfg, u16s_dp_MsgTblSize_DBCTest_dbc_cfg);

//        cout<<"Throttle = "<<ESP_Throttle_300_CAN1;
//        cout<<"; EPS Angle Request = "<<EPS_SteeringAngleReq_112_CAN1;
//        cout<<"; EPS Status = "<<EPS_StsReq_112_CAN1;
//        cout<<"; LonVel = "<<VehSts_LonVel_A8_CAN1<<"; BeamSts = "<<VehSts_BeamSts_A8_CAN1<<endl;
        usleep(20000);
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
