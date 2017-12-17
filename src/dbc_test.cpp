/*************************************************************************
	> File Name: moto_test.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年12月16日 星期六 09时51分35秒
 ************************************************************************/

#include"dbc_test.h"

using namespace std;


/* ID 400: */
double Intel_Sig1_CAN1;
double Intel_Sig2_CAN1;
double Intel_Sig3_CAN1;
double Intel_Sig4_CAN1;
double Intel_Sig5_CAN1;
double Intel_Sig6_CAN1;
double Intel_Sig7_CAN1;
uint8  Intel_Test_240_Buffer_CAN1[8];
uint8  Intel_Test_240_RxFlag_CAN1;
uint32 Intel_Test_240_AgeCounter_CAN1;
uint16 Intel_Test_240_TimeCounter_CAN1;

volatile const DbcParserSignalTblType TBL_DP_CAN1_240_SIGNALLIST[] =
{
    {(AddrType)&Intel_Sig1_CAN1, DP_SIGNALTYPE_FLOAT,  0,   8, DP_BYTEORDER_INTEL, 1,  -128,  -128,  127, DP_SIGNTYPE_UNSIGNED},
    {(AddrType)&Intel_Sig2_CAN1, DP_SIGNALTYPE_FLOAT,  8,  12, DP_BYTEORDER_INTEL, 1, -2048, -2048, 2047, DP_SIGNTYPE_UNSIGNED},
    {(AddrType)&Intel_Sig3_CAN1, DP_SIGNALTYPE_FLOAT, 20,  12, DP_BYTEORDER_INTEL, 1, -2048, -2048, 2047, DP_SIGNTYPE_UNSIGNED},
    {(AddrType)&Intel_Sig4_CAN1, DP_SIGNALTYPE_FLOAT, 32,   4, DP_BYTEORDER_INTEL, 1,    -8,    -8,    7, DP_SIGNTYPE_UNSIGNED},
    {(AddrType)&Intel_Sig5_CAN1, DP_SIGNALTYPE_FLOAT, 36,   2, DP_BYTEORDER_INTEL, 1,    -2,    -2,    1, DP_SIGNTYPE_UNSIGNED},
    {(AddrType)&Intel_Sig6_CAN1, DP_SIGNALTYPE_FLOAT, 38,   2, DP_BYTEORDER_INTEL, 1,    -2,    -2,    1, DP_SIGNTYPE_UNSIGNED},
    {(AddrType)&Intel_Sig7_CAN1, DP_SIGNALTYPE_FLOAT, 44,   8, DP_BYTEORDER_INTEL, 1,  -128,  -128,  127, DP_SIGNTYPE_UNSIGNED},

};

volatile const uint8 u8s_dp_CAN1_240_SignalTblSize = (uint8)(sizeof(TBL_DP_CAN1_240_SIGNALLIST)/sizeof(DbcParserSignalTblType));


/* ID 250:  */
double Moto_Sig1_CAN1;
double Moto_Sig2_CAN1;
double Moto_Sig3_CAN1;
double Moto_Sig4_CAN1;
double Moto_Sig5_CAN1;
double Moto_Sig6_CAN1;
double Moto_Sig7_CAN1;
uint8  Moto_Test_250_Buffer_CAN1[8];
uint8  Moto_Test_250_RxFlag_CAN1;
uint32 Moto_Test_250_AgeCounter_CAN1;
uint16 Moto_Test_250_TimeCounter_CAN1;

volatile const DbcParserSignalTblType TBL_DP_CAN1_250_SIGNALLIST[] =
{
    {(AddrType)&Moto_Sig1_CAN1, DP_SIGNALTYPE_FLOAT,  0,  8, DP_BYTEORDER_MOTOROLA, 1,  -128,  -128,  127, DP_SIGNTYPE_UNSIGNED},
    {(AddrType)&Moto_Sig2_CAN1, DP_SIGNALTYPE_FLOAT, 20, 12, DP_BYTEORDER_MOTOROLA, 1, -2048, -2048, 2047, DP_SIGNTYPE_UNSIGNED},
    {(AddrType)&Moto_Sig3_CAN1, DP_SIGNALTYPE_FLOAT, 24, 12, DP_BYTEORDER_MOTOROLA, 1, -2048, -2048, 2047, DP_SIGNTYPE_UNSIGNED},
    {(AddrType)&Moto_Sig4_CAN1, DP_SIGNALTYPE_FLOAT, 32,  4, DP_BYTEORDER_MOTOROLA, 1,    -8,    -8,    7, DP_SIGNTYPE_UNSIGNED},
    {(AddrType)&Moto_Sig5_CAN1, DP_SIGNALTYPE_FLOAT, 36,  2, DP_BYTEORDER_MOTOROLA, 1,    -2,    -2,    1, DP_SIGNTYPE_UNSIGNED},
    {(AddrType)&Moto_Sig6_CAN1, DP_SIGNALTYPE_FLOAT, 38,  2, DP_BYTEORDER_MOTOROLA, 1,    -2,    -2,    1, DP_SIGNTYPE_UNSIGNED},
    {(AddrType)&Moto_Sig7_CAN1, DP_SIGNALTYPE_FLOAT, 52,  8, DP_BYTEORDER_MOTOROLA, 1,  -128,  -128,  127, DP_SIGNTYPE_UNSIGNED},

};

volatile const uint8 u8s_dp_CAN1_250_SignalTblSize = (uint8)(sizeof(TBL_DP_CAN1_250_SIGNALLIST)/sizeof(DbcParserSignalTblType));


/* DBC Test Message List */
DbcParserMsgTblType TBL_DP_DBCMSGLIST_DBCTest_dbc_cfg[] =
{
    {0x240, DP_MSGDIR_RX, DP_PERIODICMACRO, 100, (AddrType)TBL_DP_CAN1_240_SIGNALLIST, u8s_dp_CAN1_240_SignalTblSize, 0, Intel_Test_240_Buffer_CAN1, &Intel_Test_240_RxFlag_CAN1, &Intel_Test_240_AgeCounter_CAN1, &Intel_Test_240_TimeCounter_CAN1, 3, DP_MSGKIND_NORMAL},
    {0x250, DP_MSGDIR_RX, DP_PERIODICMACRO, 100, (AddrType)TBL_DP_CAN1_250_SIGNALLIST, u8s_dp_CAN1_250_SignalTblSize, 0,  Moto_Test_250_Buffer_CAN1,  &Moto_Test_250_RxFlag_CAN1,  &Moto_Test_250_AgeCounter_CAN1,  &Moto_Test_250_TimeCounter_CAN1, 3, DP_MSGKIND_NORMAL}
};

uint16 u16s_dp_MsgTblSize_DBCTest_dbc_cfg = (uint16)(sizeof(TBL_DP_DBCMSGLIST_DBCTest_dbc_cfg)/sizeof(DbcParserMsgTblType));
