/*************************************************************************
	> File Name: thread_in_rx.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年12月03日 星期日 16时43分25秒
 ************************************************************************/
#include "dev_kvaser.h"
#include "body_dbc_conf.h"
#include "unistd.h"


extern DbcParserMsgTblType TBL_DP_DBCMSGLIST_Body_dbc_cfg[];
extern uint16 u16s_dp_MsgTblSize_body_dbc_cfg;

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

                cout<<"Channel Number = "<<ptt_slot->channelNo<<endl;

                ecal_com_dp_RxIndication(ptt_slot->channelNo, canId, msgLen, (uint8*)data, TBL_DP_DBCMSGLIST_Body_dbc_cfg, u16s_dp_MsgTblSize_body_dbc_cfg);


                cout<<"Receive Can Data: "<<EPS_SteeringAngle_202_CAN1<<endl;
                t_rItr += 13;
            }
            ptt_slot->rxBufRItr = 0;
            ptt_slot->rxBufWItr = 0;
        }
        ptt_slot->rxDataInProcFlag = false;
        usleep(10000);
    }
}

