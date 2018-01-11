/*************************************************************************
	> File Name: body_dbc_conf.h
	> Author: 
	> Mail: 
	> Created Time: 2017年11月16日 星期四 18时17分35秒
 ************************************************************************/
#ifndef _BODY_DBC_CONF_H
#define _BODY_DBC_CONF_H

#include "dbcparser.h"

extern double ESP_Throttle_300_CAN1;
extern unsigned char ESP_300_Buffer_CAN1[8];
extern unsigned char ESP_300_RxFlag_CAN1;
extern unsigned long ESP_300_AgeCounter_CAN1;
extern unsigned short ESP_300_TimeCounter_CAN1;

extern double EPS_StsReq_112_CAN1;
extern double EPS_SteeringAngleReq_112_CAN1;
extern unsigned char EPS_112_Buffer_CAN1[8];
extern unsigned char EPS_112_RxFlag_CAN1;
extern unsigned long EPS_112_AgeCounter_CAN1;
extern unsigned short EPS_112_TimeCounter_CAN1;

extern double EPS_SteeringAngle_202_CAN1;

extern double EBS_BrakePadel_228_CAN1;

extern double BCM_Gear_AA_CAN1;

extern double VehSts_LonVel_A8_CAN1;
extern double VehSts_BeamSts_A8_CAN1;
extern unsigned char VehSts_A8_Buffer_CAN1[8];
extern unsigned char VehSts_A8_RxFlag_CAN1;
extern unsigned long VehSts_A8_AgeCounter_CAN1;
extern unsigned short VehSts_A8_TimeCounter_CAN1;


#endif
