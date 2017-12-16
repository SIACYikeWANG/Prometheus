/*************************************************************************
	> File Name: body_dbc_conf.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月16日 星期四 18时17分42秒
 ************************************************************************/

#include"body_dbc_conf.h"

using namespace std;

/* ID 300: Throttle Request */
double ESP_Throttle_300_CAN1;
uint8 ESP_300_Buffer_CAN1[8];
uint8 ESP_300_RxFlag_CAN1;
uint32 ESP_300_AgeCounter_CAN1;
uint16 ESP_300_TimeCounter_CAN1;

volatile const DbcParserSignalTblType TBL_DP_CAN1_300_SIGNALLIST[] =
{
    {(AddrType)&ESP_Throttle_300_CAN1, DP_SIGNALTYPE_FLOAT, 7, 8, DP_BYTEORDER_MOTOROLA, 0.390625, 0, 0, 100, DP_SIGNTYPE_UNSIGNED}
};

volatile const uint8 u8s_dp_CAN1_300_SignalTblSize = (uint8)(sizeof(TBL_DP_CAN1_300_SIGNALLIST)/sizeof(DbcParserSignalTblType));

/* ID 112: EPS Request */
double EPS_StsReq_112_CAN1;
double EPS_SteeringAngleReq_112_CAN1;
uint8 EPS_112_Buffer_CAN1[8];
uint8 EPS_112_RxFlag_CAN1;
uint32 EPS_112_AgeCounter_CAN1;
uint16 EPS_112_TimeCounter_CAN1;

volatile const DbcParserSignalTblType TBL_DP_CAN1_112_SIGNALLIST[] =
{
    {(AddrType)&EPS_StsReq_112_CAN1,           DP_SIGNALTYPE_FLOAT,  7,  8,  DP_BYTEORDER_MOTOROLA,    1,     0,    0,   1, DP_SIGNTYPE_UNSIGNED},
    {(AddrType)&EPS_SteeringAngleReq_112_CAN1, DP_SIGNALTYPE_FLOAT, 23, 16,  DP_BYTEORDER_MOTOROLA,    1,     0, -500, 500, DP_SIGNTYPE_UNSIGNED}
//    {(AddrType)&EPS_StsReq_112_CAN1,           DP_SIGNALTYPE_FLOAT,  0,  8,  DP_BYTEORDER_INTEL,    1,     0,    0,   1, DP_SIGNTYPE_UNSIGNED},
//    {(AddrType)&EPS_SteeringAngleReq_112_CAN1, DP_SIGNALTYPE_FLOAT,  8, 16,  DP_BYTEORDER_INTEL,    1,     0, -500, 500, DP_SIGNTYPE_UNSIGNED}
};

volatile const uint8 u8s_dp_CAN1_112_SignalTblSize = (uint8)(sizeof(TBL_DP_CAN1_112_SIGNALLIST)/sizeof(DbcParserSignalTblType));

/* ID 202: EPS Feedback */
double EPS_SteeringAngle_202_CAN1;
uint8 EPS_202_Buffer_CAN1[8];
uint8 EPS_202_RxFlag_CAN1;
uint32 EPS_202_AgeCounter_CAN1;
uint16 EPS_202_TimeCounter_CAN1;

volatile const DbcParserSignalTblType TBL_DP_CAN1_202_SIGNALLIST[] =
{
    {(AddrType)&EPS_SteeringAngle_202_CAN1, DP_SIGNALTYPE_FLOAT, 23, 16, DP_BYTEORDER_MOTOROLA, 0.06, -1937, -480, 480, DP_SIGNTYPE_UNSIGNED}
};

volatile const uint8 u8s_dp_CAN1_202_SignalTblSize = (uint8)(sizeof(TBL_DP_CAN1_202_SIGNALLIST)/sizeof(DbcParserSignalTblType));


/* Body Message List */
DbcParserMsgTblType TBL_DP_DBCMSGLIST_Body_dbc_cfg[] =
{
    {0x112, DP_MSGDIR_TX, DP_PERIODICMACRO, 100, (AddrType)TBL_DP_CAN1_112_SIGNALLIST, u8s_dp_CAN1_112_SignalTblSize, 0, EPS_112_Buffer_CAN1, &EPS_112_RxFlag_CAN1, &EPS_112_AgeCounter_CAN1, &EPS_112_TimeCounter_CAN1, 3, DP_MSGKIND_NORMAL},
    {0x202, DP_MSGDIR_RX, DP_PERIODICMACRO, 100, (AddrType)TBL_DP_CAN1_202_SIGNALLIST, u8s_dp_CAN1_202_SignalTblSize, 0, EPS_202_Buffer_CAN1, &EPS_202_RxFlag_CAN1, &EPS_202_AgeCounter_CAN1, &EPS_202_TimeCounter_CAN1, 3, DP_MSGKIND_NORMAL},
    {0x300, DP_MSGDIR_TX, DP_PERIODICMACRO, 100, (AddrType)TBL_DP_CAN1_300_SIGNALLIST, u8s_dp_CAN1_300_SignalTblSize, 0, ESP_300_Buffer_CAN1, &ESP_300_RxFlag_CAN1, &ESP_300_AgeCounter_CAN1, &ESP_300_TimeCounter_CAN1, 1, DP_MSGKIND_NORMAL}
};

uint16 u16s_dp_MsgTblSize_body_dbc_cfg = (uint16)(sizeof(TBL_DP_DBCMSGLIST_Body_dbc_cfg)/sizeof(DbcParserMsgTblType));

