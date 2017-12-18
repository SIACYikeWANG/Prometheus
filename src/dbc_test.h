/*************************************************************************
	> File Name: moto_test.h
	> Author: 
	> Mail: 
	> Created Time: 2017年12月16日 星期六 09时51分45秒
 ************************************************************************/

#ifndef _MOTO_TEST_H
#define _MOTO_TEST_H

#include "dbcparser.h"

extern double Intel_Sig1_CAN1;
extern double Intel_Sig2_CAN1;
extern double Intel_Sig3_CAN1;
extern double Intel_Sig4_CAN1;
extern double Intel_Sig5_CAN1;
extern double Intel_Sig6_CAN1;
extern double Intel_Sig7_CAN1;
extern uint8  Intel_Test_400_Buffer_CAN1[8];
extern uint8  Intel_Test_400_RxFlag_CAN1;
extern uint32 Intel_Test_400_AgeCounter_CAN1;
extern uint16 Intel_Test_400_TimeCounter_CAN1;

extern double Moto_Sig1_CAN1;
extern double Moto_Sig2_CAN1;
extern double Moto_Sig3_CAN1;
extern double Moto_Sig4_CAN1;
extern double Moto_Sig5_CAN1;
extern double Moto_Sig6_CAN1;
extern double Moto_Sig7_CAN1;
extern uint8  Moto_Test_500_Buffer_CAN1[8];
extern uint8  Moto_Test_500_RxFlag_CAN1;
extern uint32 Moto_Test_500_AgeCounter_CAN1;
extern uint16 Moto_Test_500_TimeCounter_CAN1;

extern double Intel_Sig8_CAN1;
extern uint8  Intel_Test_241_Buffer_CAN1[8];
extern uint8  Intel_Test_241_RxFlag_CAN1;
extern uint32 Intel_Test_241_AgeCounter_CAN1;
extern uint16 Intel_Test_241_TimeCounter_CAN1;

extern double Moto_Sig8_CAN1;
extern uint8  Moto_Test_251_Buffer_CAN1[8];
extern uint8  Moto_Test_251_RxFlag_CAN1;
extern uint32 Moto_Test_251_AgeCounter_CAN1;
extern uint16 Moto_Test_251_TimeCounter_CAN1;

#endif
