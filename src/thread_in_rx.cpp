/*************************************************************************
	> File Name: thread_in_rx.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年12月03日 星期日 16时43分25秒
 ************************************************************************/
#include "dev_kvaser.h"
#include "body_dbc_conf.h"
#include "dbc_test.h"
#include "unistd.h"


extern DbcParserMsgTblType TBL_DP_DBCMSGLIST_Body_dbc_cfg[];
extern uint16 u16s_dp_MsgTblSize_body_dbc_cfg;

extern DbcParserMsgTblType TBL_DP_DBCMSGLIST_DBCTest_dbc_cfg[];
extern uint16 u16s_dp_MsgTblSize_DBCTest_dbc_cfg;



void printMotoCanMsg();
void printIntelCanMsg();

void* Proc_ParseData_Srv0Can0(void *arg)
{
    RxSlotType* ptt_slot = (RxSlotType*)arg;

    while(1)
    {
        ptt_slot->rxDataInProcFlag = true;
        if(ptt_slot->rxBufRItr<ptt_slot->rxBufWItr)
        {
            int t_wItr = ptt_slot->rxBufWItr;
            int t_rItr = ptt_slot->rxBufRItr;
            while(t_rItr<t_wItr && t_rItr+13<=t_wItr)
            {
                int msgLen = ptt_slot->rxBuffer_bkup[t_rItr] & 0x0F;
                int canId = 0;

                canId = *(int *)(ptt_slot->rxBuffer + t_rItr +1);
                uint8 *data = (uint8*)(ptt_slot->rxBuffer + t_rItr + 5);

//                ecal_com_dp_RxIndication(ptt_slot->channelNo, canId, msgLen, (uint8*)data, TBL_DP_DBCMSGLIST_Body_dbc_cfg, u16s_dp_MsgTblSize_body_dbc_cfg);
//                cout<<"EPS_SteeringAngle_202_CAN1 = "<<EPS_SteeringAngle_202_CAN1<<endl;

                ecal_com_dp_RxIndication(ptt_slot->channelNo, canId, msgLen, (uint8*)data, TBL_DP_DBCMSGLIST_DBCTest_dbc_cfg, u16s_dp_MsgTblSize_DBCTest_dbc_cfg);
                //printMotoCanMsg();
                printIntelCanMsg();

                t_rItr += 13;
            }
            ptt_slot->rxBufRItr = 0;
            ptt_slot->rxBufWItr = 0;
        }
        ptt_slot->rxDataInProcFlag = false;
        usleep(10000);
    }
}

void printMotoCanMsg()
{
    cout<<"Moto_Sig1 = "<<Moto_Sig1_CAN1<<", ";
    cout<<"Moto_Sig2 = "<<Moto_Sig2_CAN1<<", ";
    cout<<"Moto_Sig3 = "<<Moto_Sig3_CAN1<<", ";
    cout<<"Moto_Sig4 = "<<Moto_Sig4_CAN1<<", ";
    cout<<"Moto_Sig5 = "<<Moto_Sig5_CAN1<<", ";
    cout<<"Moto_Sig6 = "<<Moto_Sig6_CAN1<<", ";
    cout<<"Moto_Sig7 = "<<Moto_Sig7_CAN1<<endl;
}

void printIntelCanMsg()
{
    cout<<"Intel_Sig1 = "<<Intel_Sig1_CAN1<<", ";
    cout<<"Intel_Sig2 = "<<Intel_Sig2_CAN1<<", ";
    cout<<"Intel_Sig3 = "<<Intel_Sig3_CAN1<<", ";
    cout<<"Intel_Sig4 = "<<Intel_Sig4_CAN1<<", ";
    cout<<"Intel_Sig5 = "<<Intel_Sig5_CAN1<<", ";
    cout<<"Intel_Sig6 = "<<Intel_Sig6_CAN1<<", ";
    cout<<"Intel_Sig7 = "<<Intel_Sig7_CAN1<<endl;
}

