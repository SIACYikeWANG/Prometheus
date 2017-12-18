/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年10月31日 星期二 09时31分21秒
 ************************************************************************/

#include<iostream>
#include"kvrChannel.h"
#include<unistd.h>
#include<pthread.h>
#include"dbcparser.h"
#include"dev_kvaser.h"
#include"body_dbc_conf.h"
#include "dev_kvaser.h"
#include "thread_in_rx.h"
#include "dbc_test.h"

using namespace std;

void* Proc_ParseData_Srv0Can0(void *arg);

extern RxSlotType stg_RxSlot[8];

int main()
{
    //Initialize kvaser library!
    canInitializeLibrary();

    int bitRate = canBITRATE_500K;

    KvrChannel kvrChl0(0,bitRate);
//    KvrChannel kvrChl1(1,bitRate);

    pthread_t pth0,pth1;

    EPS_StsReq_112_CAN1 = 1;
    EPS_SteeringAngleReq_112_CAN1 = 100;
    Intel_Sig1_CAN1 = -100;
    Intel_Sig2_CAN1 = -100;
    Intel_Sig3_CAN1 = -100;
    Intel_Sig4_CAN1 = -5;
    Intel_Sig5_CAN1 = 1;
    Intel_Sig6_CAN1 = 1;
    Intel_Sig7_CAN1 = -100;
    Intel_Sig8_CAN1 = -10000;
    Moto_Sig1_CAN1 = 2000;
    Moto_Sig2_CAN1 = -2000;
    Moto_Sig3_CAN1 = 20000;
    Moto_Sig4_CAN1 = 20;
    Moto_Sig5_CAN1 = -100;
    Moto_Sig6_CAN1 = -100;
    Moto_Sig7_CAN1 = 100;
    Moto_Sig8_CAN1 = -10000;

    StartCanTxMsgTask(&pth0,&kvrChl0); // 开始发送
    StartCanRxMsgTask(&pth1,&kvrChl0); // 开始接受

    pthread_t pth2;
    int result = pthread_create(&pth2, NULL, Proc_ParseData_Srv0Can0, (void*)&stg_RxSlot[0]); //　将收到的CAN数据通过DBC解析对应到变量

    if(result)
    {
        cout<<"Create Thread CanMsgParse failed!"<<endl;
    }
    else
    {
        cout<<"Create Thread CanMsgParse successful!"<<endl;
    }

//    StartCanTxMsgTask(&pth2,&kvrChl1);
//    StartCanRxMsgTask(&pth3,&kvrChl1);

    if(pthread_join(pth0,NULL))
    {
        cout<<"Could not join pth"<<endl;
    }

    if(pthread_join(pth1,NULL))
    {
        cout<<"Could not join pth1"<<endl;
    }

    if(pthread_join(pth2,NULL))
    {
        cout<<"Could not join pth1"<<endl;
    }

    uint8 temp = 0;

    return 0;
}
