/*************************************************************************
    > File Name: dbcparser.cpp
    > Author:
    > Mail:
    > Created Time: 2017年11月12日 星期日 10时43分59秒
 ************************************************************************/
#include "dbcparser.h"
#include <iostream>
#include <stdlib.h>
#include <bitset>


using namespace std;

uint8 u8g_ecal_com_dp_RxStatus;
uint8 u8g_ecal_com_dp_TxStatus;
static uint16 u16s_ecal_com_dp_txcounter;
static uint16 u16s_ecal_com_dp_rxcounter;

void ecal_com_dp_Init(DbcParserMsgTblType * pt_MsgTbl, uint16 u16_tblSize)
{
    uint16 u16t_loop;
    u16s_ecal_com_dp_txcounter = (uint8)0;
    u16s_ecal_com_dp_rxcounter = (uint8)0;
    u8g_ecal_com_dp_RxStatus = (uint8)ON;
    u8g_ecal_com_dp_TxStatus = (uint8)ON;

    for ( u16t_loop = (uint16)0 ; u16t_loop < u16_tblSize; u16t_loop++ )
    {
        *(pt_MsgTbl[u16t_loop].pt_RxFlag) = (uint8)OFF;
        *(pt_MsgTbl[u16t_loop].pt_AgeCounter) = (uint32)0;
        *(pt_MsgTbl[u16t_loop].pt_TimerCounter) = (uint16)0;
    }
}

//void ecal_com_dp_TxMainFunction(void)
//{
//	uint16 u16t_loop;
//	uint32 u32t_time;
//	u16s_ecal_com_dp_txcounter++;
//
//	if ( u16s_ecal_com_dp_txcounter == 0xFFFF )
//	{
//		u16s_ecal_com_dp_txcounter = 0;
//	}
//	u32t_time = ((uint32)u16s_ecal_com_dp_txcounter) * ((uint32)DP_TXMAINFUNCTION_PERIOD);
//	for ( u16t_loop = (uint16)0 ; u16t_loop < u16s_dp_MsgTblSize ; u16t_loop++ )
//	{
//		if (( TBL_DP_DBCMSGLIST[u16t_loop].u8_Dir == DP_MSGDIR_TX )
//				&&( TBL_DP_DBCMSGLIST[u16t_loop].u8_SendType == DP_PERIODICMACRO )
//				&&( u32t_time % TBL_DP_DBCMSGLIST[u16t_loop].u16_Period == 0 ))
//		{
//			ecal_com_dp_ContructMsg(TBL_DP_DBCMSGLIST[u16t_loop].u32_CanId);
//		}
//	}
//}

void ecal_com_dp_RxMainFunction(DbcParserMsgTblType * pt_MsgTbl, uint16 u16_tblSize)
{
    uint16 u16t_loop;
    uint32 u32t_time;
    u16s_ecal_com_dp_rxcounter++;

    if( u8g_ecal_com_dp_RxStatus == (uint8)ON )
    {
        if ( u16s_ecal_com_dp_rxcounter == 0xFFFF )
        {
            u16s_ecal_com_dp_rxcounter = 0;
        }
        u32t_time = ((uint32)u16s_ecal_com_dp_rxcounter) * ((uint32)DP_RXMAINFUNCTION_PEIROD);
        for ( u16t_loop = (uint16)0 ; u16t_loop < u16_tblSize; u16t_loop++ )
        {
            if (pt_MsgTbl[u16t_loop].u8_Dir == DP_MSGDIR_RX )
            {
                if ( *(pt_MsgTbl[u16t_loop].pt_RxFlag) == (uint8)ON )
                {
                    if (pt_MsgTbl[u16t_loop].u16_TblSize != 0 )
                    {
                        ecal_com_dp_ParseMsg(pt_MsgTbl[u16t_loop].u32_CanId, 8, pt_MsgTbl[u16t_loop].pt_Buffer, pt_MsgTbl[u16t_loop].u8_Channel, pt_MsgTbl, u16_tblSize);
                    }
                        *(pt_MsgTbl[u16t_loop].pt_RxFlag) = (uint8)OFF;
                    if (pt_MsgTbl[u16t_loop].u8_SendType == DP_PERIODICMACRO )
                    {
                        if ( *(pt_MsgTbl[u16t_loop].pt_AgeCounter) > 0 )
                        {
                            *(pt_MsgTbl[u16t_loop].pt_AgeCounter) = 0;
                        }
                        *(pt_MsgTbl[u16t_loop].pt_TimerCounter) = u16s_ecal_com_dp_rxcounter;
                    }
                }
                else
                {
                    if (pt_MsgTbl[u16t_loop].u8_SendType == DP_PERIODICMACRO )
                    {
                        if ( *(pt_MsgTbl[u16t_loop].pt_TimerCounter) < u16s_ecal_com_dp_rxcounter )
                    {
                        u32t_time = ( u16s_ecal_com_dp_rxcounter - *(pt_MsgTbl[u16t_loop].pt_TimerCounter) ) * ((uint32)DP_RXMAINFUNCTION_PEIROD);
                    }
                    else
                    {
                            u32t_time = (uint32)(u16s_ecal_com_dp_rxcounter | (uint32)0x10000) - (uint32)*(pt_MsgTbl[u16t_loop].pt_TimerCounter);
                    }
                    if ( u32t_time % pt_MsgTbl[u16t_loop].u16_Period == 0 )
                    {
                        if ( *(pt_MsgTbl[u16t_loop].pt_AgeCounter) < 0xFFFF )
                        {
                            (*(pt_MsgTbl[u16t_loop].pt_AgeCounter))++;
                            }
                        }
                    }

                }
                //ecal_com_dp_ContructMsg(TBL_DP_DBCMSGLIST[u16t_loop].u32_CanId);
            }
        }
    }
}

void ecal_com_dp_RxIndication(uint8 hrh, uint32 u32t_canid, uint8 u8t_datalen, uint8 * ptt_buffer, DbcParserMsgTblType * pt_MsgTbl, uint16 u16_tblSize)
{
    uint16 u16t_loop;
    uint8 u8t_loop;

    if( u8g_ecal_com_dp_RxStatus == (uint8)ON )
    {
        for ( u16t_loop = (uint16)0 ; u16t_loop < u16_tblSize; u16t_loop++ )
        {
            if (( u32t_canid == pt_MsgTbl[u16t_loop].u32_CanId )
                    &&(pt_MsgTbl[u16t_loop].u8_Dir == DP_MSGDIR_RX)
                    &&(pt_MsgTbl[u16t_loop].u8_Channel == hrh))
            {
                if (pt_MsgTbl[u16t_loop].u8_MsgParserType == DP_MSGKIND_NORMAL)
                {
                    *(pt_MsgTbl[u16t_loop].pt_RxFlag) = (uint8)ON;
                    //memcpy (TBL_DP_DBCMSGLIST[u16t_loop].pt_Buffer, ptt_buffer, u8t_datalen);
                    for (u8t_loop = (uint8)0; u8t_loop < u8t_datalen; u8t_loop++)
                    {
                        pt_MsgTbl[u16t_loop].pt_Buffer[u8t_loop] = ptt_buffer[u8t_loop];
                    }
                }
                else
                {
                    for (u8t_loop = (uint8)0; u8t_loop < u8t_datalen; u8t_loop++)
                    {
                        pt_MsgTbl[u16t_loop].pt_Buffer[u8t_loop] = ptt_buffer[u8t_loop];
                    }
                    ecal_com_dp_ParseMsg(u32t_canid, u8t_datalen, pt_MsgTbl[u16t_loop].pt_Buffer
                        , hrh, pt_MsgTbl, u16_tblSize);
                }
                break;
            }
        }
    }
}


void ecal_com_dp_ParseMsg(uint32 u32t_canid, uint8 u8t_datalen, uint8 * ptt_buffer, uint8 u8t_hrh, DbcParserMsgTblType * pt_MsgTbl, uint16 u16_tblSize)
{
    uint8 u8t_loop;
    uint16 u16t_loop;
    uint64 u64t_value;
    sint64 s64t_value;
    volatile const DbcParserSignalTblType* ptt_sigtbl;
    double f32t_factor;
    double f32t_offset;
    double f32t_max;
    double f32t_min;
    double f32t_physval;
    double f64t_physval;
    uint8 u8t_byteorder;
    uint8 u8t_startpos;
    sint8 s8t_signallen;
    uint8 u8t_bytepos;
    sint8 s8t_startbit;
    uint8 u8t_tempdata;
    sint8 s8t_shiftbit;
    float t_value;
    uint32 * ptt_value;
    uint64 * ptt_value64;
    float ** ptt_signal;

    for ( u16t_loop = (uint16)0 ; u16t_loop < u16_tblSize; u16t_loop++ )
    {
        if (( u32t_canid == pt_MsgTbl[u16t_loop].u32_CanId )
                &&(pt_MsgTbl[u16t_loop].u8_Dir == DP_MSGDIR_RX)
                &&(pt_MsgTbl[u16t_loop].u8_Channel == u8t_hrh))
        {
            ptt_sigtbl = (volatile const DbcParserSignalTblType*)pt_MsgTbl[u16t_loop].pt_SignalTbl;
            break;
        }
    }
    if ( u16t_loop == u16_tblSize)
    {
        return;
    }
    if (pt_MsgTbl[u16t_loop].u8_MsgParserType == DP_MSGKIND_NORMAL)
    {
        for (u8t_loop = 0; u8t_loop < pt_MsgTbl[u16t_loop].u16_TblSize; u8t_loop++)
        {
            u64t_value = (uint64)0;
            f32t_factor = ptt_sigtbl[u8t_loop].f32_Factor;
            f32t_offset = ptt_sigtbl[u8t_loop].f32_Offset;
            f32t_max = ptt_sigtbl[u8t_loop].f32_Max;
            f32t_min = ptt_sigtbl[u8t_loop].f32_Min;
            u8t_byteorder = ptt_sigtbl[u8t_loop].u8_ByteOrder;
            u8t_startpos = ptt_sigtbl[u8t_loop].u8_StartBit;
            s8t_signallen = (sint8)(ptt_sigtbl[u8t_loop].u8_DataLen);
            if (u8t_byteorder == DP_BYTEORDER_MOTOROLA)
            {
                u8t_bytepos = u8t_startpos / 8;	/* 起始字节位　*/
                s8t_startbit = (sint8)u8t_startpos % 8;
                //s8t_signallen = s8t_signallen - s8t_templen - 1;
                /* 将该字节不相关数据清零 */
                u8t_tempdata = ptt_buffer[u8t_bytepos] << (8 - s8t_startbit - 1);
                u8t_tempdata = u8t_tempdata >> (8 - s8t_startbit - 1);

                /* 跨字节数据 */
                if (s8t_signallen - s8t_startbit - 1 >= 0)
                {
                    s8t_signallen = s8t_signallen - s8t_startbit - 1;
                    u64t_value = ((uint64)u8t_tempdata << s8t_signallen);
                    s8t_signallen -= 8;
                    while (s8t_signallen > 0)
                    {
                        u8t_bytepos++;
                        u64t_value |= ((uint64)ptt_buffer[u8t_bytepos] << s8t_signallen);
                        s8t_signallen -= 8;
                    }
                    if (s8t_signallen == 0)
                    {
                        u8t_bytepos++;
                        u64t_value |= ((uint64)ptt_buffer[u8t_bytepos] << s8t_signallen);
                    }
                    else if (s8t_signallen < 0)
                    {
                        s8t_signallen = 0 - s8t_signallen;
                        if (s8t_signallen < 8)
                        {
                            u8t_bytepos++;
                            u64t_value |= ((uint64)ptt_buffer[u8t_bytepos] >> s8t_signallen);
                        }
                    }
                }
                else
                {
                    /* 长度短，但起始位在高位，需右移两次，举例：startbit = 08 len = 02 */
                    if (s8t_signallen > 8 - s8t_startbit)
                    {
                        if (s8t_signallen - s8t_startbit > 0)
                        {
                            /* 长度短，但起始位在低位，需右移两次，举例：startbit = 00 len = 02 */
                            u64t_value |= ((uint64)ptt_buffer[u8t_bytepos] >> s8t_startbit);
                            u8t_bytepos++;
                            u8t_tempdata = ptt_buffer[u8t_bytepos] << (s8t_startbit - s8t_signallen);
                            u64t_value |= ((uint64)u8t_tempdata >> (s8t_startbit - s8t_signallen));
                        }
                        else
                        {
                            /* 长度短，但起始位在高位：startbit = 07 len = 02 */
                            u8t_tempdata = (ptt_buffer[u8t_bytepos] << (8 - s8t_startbit - 1));
                            u64t_value |= ((uint64)u8t_tempdata >> (8 - s8t_signallen));
                        }
                    }
                    else
                    {
                        /* 长度短，但起始位不在高位，只需右移一次：startbit = 07 len = 02 */
                        u64t_value |= ((uint64)u8t_tempdata >> (s8t_startbit + 1 - s8t_signallen));
                    }
                }
            }
            else
            {
                u8t_bytepos = u8t_startpos / 8;
                s8t_shiftbit = (sint8)u8t_startpos % 8;
                if (8 - s8t_shiftbit < s8t_signallen)
                {
                    /* 跨字节 */
                    u64t_value |= ((uint64)ptt_buffer[u8t_bytepos] >> s8t_shiftbit);
                    s8t_startbit = 8 - s8t_shiftbit;
                    while (s8t_signallen - (uint8)s8t_startbit >= 8)
                    {
                        u8t_bytepos++;
                        u64t_value |= ((uint64)ptt_buffer[u8t_bytepos] << s8t_startbit);
                        s8t_startbit += 8;
                    }
                    u8t_bytepos++;
                    u8t_tempdata = ptt_buffer[u8t_bytepos] << (8 - s8t_signallen + (uint8)s8t_startbit);
                    u8t_tempdata = u8t_tempdata >> (8 - s8t_signallen + (uint8)s8t_startbit);
                    u64t_value |= ((uint64)u8t_tempdata << s8t_startbit);
                }
                else
                {
                    /* 非跨字节 */
                    s8t_startbit = 8 - s8t_shiftbit - s8t_signallen;
                    u8t_tempdata = ptt_buffer[u8t_bytepos] << (s8t_startbit);
                    u8t_tempdata = u8t_tempdata >> (s8t_startbit + s8t_shiftbit);
                    u64t_value = (uint64)u8t_tempdata;
                }
            }
            switch (ptt_sigtbl->u8_Type)
            {
            case DP_SIGNALTYPE_UINT8:
                break;
            case DP_SIGNALTYPE_UINT16:
                break;
            case DP_SIGNALTYPE_UINT32:
                break;
            case DP_SIGNALTYPE_SINT8:
                break;
            case DP_SIGNALTYPE_SINT16:
                break;
            case DP_SIGNALTYPE_SINT32:
                break;
            case DP_SIGNALTYPE_FLOAT:
                if (ptt_sigtbl[u8t_loop].u8_SignType == DP_SIGNTYPE_SIGNED
                    && ptt_sigtbl[u8t_loop].u8_DataLen > 1)
                {
                    if (u64t_value >> (ptt_sigtbl[u8t_loop].u8_DataLen - 1) == 1)
                    {	//负数
                        s64t_value = 0 - (sint64)(((~u64t_value + 1) << (64 - ptt_sigtbl[u8t_loop].u8_DataLen)) >> (64 - ptt_sigtbl[u8t_loop].u8_DataLen));
                    }
                    else
                    {
                        s64t_value = (sint64)u64t_value;
                    }
                    f32t_physval = s64t_value * f32t_factor + f32t_offset;
                    if (f32t_physval > f32t_max)
                    {
                        f32t_physval = f32t_max;
                    }
                    else if (f32t_physval < f32t_min)
                    {
                        f32t_physval = f32t_min;
                    }
                    //*ptt_signal = (float *)(ptt_sigtbl[u8t_loop].u32_Addr);
                    //**ptt_signal = f32t_physval;
                    *((double *)(ptt_sigtbl[u8t_loop].ad_Addr)) = f32t_physval;
                }
                else
                {
                    f32t_physval = u64t_value * f32t_factor + f32t_offset;
                    if (f32t_physval > f32t_max)
                    {
                        f32t_physval = f32t_max;
                    }
                    else if (f32t_physval < f32t_min)
                    {
                        f32t_physval = f32t_min;
                    }
                    //*ptt_signal = (float *)(ptt_sigtbl[u8t_loop].u32_Addr);
                    //**ptt_signal = f32t_physval;
                    *((double *)(ptt_sigtbl[u8t_loop].ad_Addr)) = f32t_physval;
                }
                break;
            case DP_SIGNALTYPE_IEEEFLOAT:
                ptt_value = (uint32*)&t_value;
                *ptt_value = (uint32)u64t_value;
                f32t_physval = (double)(t_value);
                *((double *)(ptt_sigtbl[u8t_loop].ad_Addr)) = f32t_physval;
                break;
            case DP_SIGNALTYPE_IEEEDOUBLE:
                ptt_value64 = (uint64*)&t_value;
                *ptt_value64 = (uint32)u64t_value;
                f64t_physval = (double)(t_value);
                *((double *)(ptt_sigtbl[u8t_loop].ad_Addr)) = f64t_physval;
                break;
            default:
                break;
            }
        }
    }
    else if (pt_MsgTbl[u16t_loop].u8_MsgParserType == DP_MSGKIND_GROUP)
    {
        uint8 t_groupIdx = 0;
        uint8 t_sigIdx = 0;
        for (u8t_loop = 0; u8t_loop < pt_MsgTbl[u16t_loop].u16_TblSize; u8t_loop++)
        {
            if (u8t_loop == 0)
            {
                t_sigIdx = 0;
            }
            else
            {
                t_sigIdx = u8t_loop + pt_MsgTbl[u16t_loop].u16_TblSize * t_groupIdx;
            }
            if (ptt_sigtbl[t_sigIdx].ad_Addr == (AddrType)nullptr)
            {
                break;
            }
            u64t_value = (uint64)0;
            f32t_factor = ptt_sigtbl[t_sigIdx].f32_Factor;
            f32t_offset = ptt_sigtbl[t_sigIdx].f32_Offset;
            f32t_max = ptt_sigtbl[t_sigIdx].f32_Max;
            f32t_min = ptt_sigtbl[t_sigIdx].f32_Min;
            u8t_byteorder = ptt_sigtbl[t_sigIdx].u8_ByteOrder;
            u8t_startpos = ptt_sigtbl[t_sigIdx].u8_StartBit;
            s8t_signallen = (sint8)(ptt_sigtbl[t_sigIdx].u8_DataLen);
            if (u8t_byteorder == DP_BYTEORDER_MOTOROLA)
            {
                u8t_bytepos = u8t_startpos / 8;	/* 起始字节位 */
                s8t_startbit = (sint8)u8t_startpos % 8;
                //s8t_signallen = s8t_signallen - s8t_templen - 1;
                /* 该字节不相关数据清零 */
                u8t_tempdata = ptt_buffer[u8t_bytepos] << (8 - s8t_startbit - 1);
                u8t_tempdata = u8t_tempdata >> (8 - s8t_startbit - 1);

                /* 跨字节数据 */
                if (s8t_signallen - s8t_startbit - 1 >= 0)
                {
                    s8t_signallen = s8t_signallen - s8t_startbit - 1;
                    u64t_value = ((uint64)u8t_tempdata << s8t_signallen);
                    s8t_signallen -= 8;
                    while (s8t_signallen > 0)
                    {
                        u8t_bytepos++;
                        u64t_value |= ((uint64)ptt_buffer[u8t_bytepos] << s8t_signallen);
                        s8t_signallen -= 8;
                    }
                    if (s8t_signallen == 0)
                    {
                        u8t_bytepos++;
                        u64t_value |= ((uint64)ptt_buffer[u8t_bytepos] << s8t_signallen);
                    }
                    else if (s8t_signallen < 0)
                    {
                        s8t_signallen = 0 - s8t_signallen;
                        if (s8t_signallen < 8)
                        {
                            u8t_bytepos++;
                            u64t_value |= ((uint64)ptt_buffer[u8t_bytepos] >> s8t_signallen);
                        }
                    }
                }
                else
                {
                    /* 长度短，但起始位在高位，需右移两次，举例：startbit = 08 len = 02 */
                    if (s8t_signallen > 8 - s8t_startbit)
                    {
                        if (s8t_signallen - s8t_startbit > 0)
                        {
                            /* 长度短，但起始位在低位，需右移两次，举例：startbit = 00 len = 02 */
                            u64t_value |= ((uint64)ptt_buffer[u8t_bytepos] >> s8t_startbit);
                            u8t_bytepos++;
                            u8t_tempdata = ptt_buffer[u8t_bytepos] << (s8t_startbit - s8t_signallen);
                            u64t_value |= ((uint64)u8t_tempdata >> (s8t_startbit - s8t_signallen));
                        }
                        else
                        {
                            /* 长度短，但起始位在高位：startbit = 07 len = 02 */
                            u8t_tempdata = (ptt_buffer[u8t_bytepos] << (8 - s8t_startbit - 1));
                            u64t_value |= ((uint64)u8t_tempdata >> (8 - s8t_signallen));
                        }
                    }
                    else
                    {
                        /* 长度短，但起始位不在高位，只需右移一次：startbit = 07 len = 02 */
                        u64t_value |= ((uint64)u8t_tempdata >> (s8t_startbit + 1 - s8t_signallen));
                    }
                }
            }
            else
            {
                u8t_bytepos = u8t_startpos / 8;
                s8t_shiftbit = (sint8)u8t_startpos % 8;
                if (8 - s8t_shiftbit < s8t_signallen)
                {
                    /* 跨字节 */
                    u64t_value |= ((uint64)ptt_buffer[u8t_bytepos] >> s8t_shiftbit);
                    s8t_startbit = 8 - s8t_shiftbit;
                    while (s8t_signallen - (uint8)s8t_startbit >= 8)
                    {
                        u8t_bytepos++;
                        u64t_value |= ((uint64)ptt_buffer[u8t_bytepos] << s8t_startbit);
                        s8t_startbit += 8;
                    }
                    u8t_bytepos++;
                    u8t_tempdata = ptt_buffer[u8t_bytepos] << (8 - s8t_signallen + (uint8)s8t_startbit);
                    u8t_tempdata = u8t_tempdata >> (8 - s8t_signallen + (uint8)s8t_startbit);
                    u64t_value |= ((uint64)u8t_tempdata << s8t_startbit);
                }
                else
                {
                    /* 非跨字节 */
                    s8t_startbit = 8 - s8t_shiftbit - s8t_signallen;
                    u8t_tempdata = ptt_buffer[u8t_bytepos] << (s8t_startbit);
                    u8t_tempdata = u8t_tempdata >> (s8t_startbit + s8t_shiftbit);
                    u64t_value = (uint64)u8t_tempdata;
                }
            }
            switch (ptt_sigtbl->u8_Type)
            {
            case DP_SIGNALTYPE_UINT8:
                break;
            case DP_SIGNALTYPE_UINT16:
                break;
            case DP_SIGNALTYPE_UINT32:
                break;
            case DP_SIGNALTYPE_SINT8:
                break;
            case DP_SIGNALTYPE_SINT16:
                break;
            case DP_SIGNALTYPE_SINT32:
                break;
            case DP_SIGNALTYPE_FLOAT:
                if (ptt_sigtbl[t_sigIdx].u8_SignType == DP_SIGNTYPE_SIGNED
                    && ptt_sigtbl[t_sigIdx].u8_DataLen > 1)
                {
                    if (u64t_value >> (ptt_sigtbl[t_sigIdx].u8_DataLen - 1) == 1)
                    {	//负数
                        s64t_value = 0 - (sint64)(((~u64t_value + 1) << (64 - ptt_sigtbl[t_sigIdx].u8_DataLen)) >> (64 - ptt_sigtbl[t_sigIdx].u8_DataLen));
                    }
                    else
                    {
                        s64t_value = (sint64)u64t_value;
                    }
                    f32t_physval = s64t_value * f32t_factor + f32t_offset;
                    if (f32t_physval > f32t_max)
                    {
                        f32t_physval = f32t_max;
                    }
                    else if (f32t_physval < f32t_min)
                    {
                        f32t_physval = f32t_min;
                    }
                    //*ptt_signal = (float *)(ptt_sigtbl[t_sigIdx].u32_Addr);
                    //**ptt_signal = f32t_physval;
                    *((double *)(ptt_sigtbl[t_sigIdx].ad_Addr)) = f32t_physval;
                }
                else
                {
                    f32t_physval = u64t_value * f32t_factor + f32t_offset;
                    if (f32t_physval > f32t_max)
                    {
                        f32t_physval = f32t_max;
                    }
                    else if (f32t_physval < f32t_min)
                    {
                        f32t_physval = f32t_min;
                    }
                    //*ptt_signal = (float *)(ptt_sigtbl[t_sigIdx].u32_Addr);
                    //**ptt_signal = f32t_physval;
                    *((double *)(ptt_sigtbl[t_sigIdx].ad_Addr)) = f32t_physval;
                }
                break;
            case DP_SIGNALTYPE_IEEEFLOAT:
                ptt_value = (uint32*)&t_value;
                *ptt_value = (uint32)u64t_value;
                f32t_physval = (double)(t_value);
                *((double *)(ptt_sigtbl[t_sigIdx].ad_Addr)) = f32t_physval;
                break;
            case DP_SIGNALTYPE_IEEEDOUBLE:
                ptt_value64 = (uint64*)&t_value;
                *ptt_value64 = (uint32)u64t_value;
                f64t_physval = (double)(t_value);
                *((double *)(ptt_sigtbl[t_sigIdx].ad_Addr)) = f64t_physval;
                break;
            default:
                break;
            }
            if (u8t_loop == 0)
            {
                t_groupIdx = (uint8)(*((double *)(ptt_sigtbl[u8t_loop].ad_Addr)));
            }
        }
    }
}

void ecal_com_dp_ContructMsg(KvrChannel *kvrChl,uint32 u32t_canid, DbcParserMsgTblType * pt_MsgTbl, uint16 u16_tblSize)
{
    uint8 u8t_loop;
    uint16 u16t_loop;
    uint64 u64t_value;
    sint64 s64t_value;
    volatile const DbcParserSignalTblType* ptt_sigtbl;
    double f32t_factor;
    double f32t_offset;
    double f32t_max;
    double f32t_min;
    double f32t_physval;
    float f4t_physval;
    double f8t_physval;
    uint8 u8t_startpos;
    uint8 u8t_datalen;
    uint8 u8t_byteorder;
    sint8 s8t_shiftbit;
    uint8 u8t_bytepos;
    uint8 u8t_buffer[8] = { 0 };
    uint8 u8t_tempdatalen;
    double ** ptt_signal;
    uint8 u8t_channel;
    uint8 u8t_msglen;
    uint8 u8t_frameType;
    uint64 u64t_temp_1;
    uint32 * ptt_val;
    uint64 * ptt_val64;

    for ( u16t_loop = (uint16)0 ; u16t_loop < u16_tblSize; u16t_loop++ )
    {
        if (( u32t_canid == pt_MsgTbl[u16t_loop].u32_CanId )
                &&(pt_MsgTbl[u16t_loop].u8_Dir == DP_MSGDIR_TX))
        {
            ptt_sigtbl = (volatile const DbcParserSignalTblType*)pt_MsgTbl[u16t_loop].pt_SignalTbl;
            u8t_channel = pt_MsgTbl[u16t_loop].u8_Channel;
            u8t_msglen = pt_MsgTbl[u16t_loop].u8_MsgLen;
            break;
        }
    }
    if ( u16t_loop == u16_tblSize)
    {
        return;
    }

    for ( u8t_loop = 0 ; u8t_loop < pt_MsgTbl[u16t_loop].u16_TblSize ; u8t_loop ++ )
    {
        u8t_startpos = ptt_sigtbl[u8t_loop].u8_StartBit;
        u8t_datalen = ptt_sigtbl[u8t_loop].u8_DataLen;
        u8t_byteorder = ptt_sigtbl[u8t_loop].u8_ByteOrder;
        f32t_factor = ptt_sigtbl[u8t_loop].f32_Factor;
        f32t_offset = ptt_sigtbl[u8t_loop].f32_Offset;
        f32t_max = ptt_sigtbl[u8t_loop].f32_Max;
        f32t_min = ptt_sigtbl[u8t_loop].f32_Min;
        u64t_value = (uint64)0;
        switch (ptt_sigtbl->u8_Type)
        {
        case DP_SIGNALTYPE_UINT8:
            break;
        case DP_SIGNALTYPE_UINT16:
            break;
        case DP_SIGNALTYPE_UINT32:
            break;
        case DP_SIGNALTYPE_SINT8:
            break;
        case DP_SIGNALTYPE_SINT16:
            break;
        case DP_SIGNALTYPE_SINT32:
            break;
        case DP_SIGNALTYPE_FLOAT:

            f32t_physval = *((double * )(ptt_sigtbl[u8t_loop].ad_Addr));

            if( ptt_sigtbl[u8t_loop].u8_SignType == DP_SIGNTYPE_SIGNED && ptt_sigtbl[u8t_loop].u8_DataLen > 1)
            {
                s64t_value = (sint64)((f32t_physval - f32t_offset) / f32t_factor);
                if (s64t_value >= 0)
                {

                }
                else //算补码
                {
                    s64t_value = (s64t_value & 0x7FFFFFFF);//去掉最高位符号
                    s64t_value = s64t_value | (((sint64)1) << (ptt_sigtbl[u8t_loop].u8_DataLen - 1));
                    u64t_temp_1 = 0;
                    for (int si = 0; si < ptt_sigtbl[u8t_loop].u8_DataLen; si++)
                    {
                        u64t_temp_1 = (u64t_temp_1 << 1) | 1;
                    }
                    s64t_value = s64t_value & u64t_temp_1;
                }
                u64t_value = (uint64)s64t_value;
            }
            else
            {
                u64t_value = (f32t_physval - f32t_offset) / f32t_factor;
            }
            break;
        case DP_SIGNALTYPE_IEEEFLOAT:
            f4t_physval = *((float *)(ptt_sigtbl[u8t_loop].ad_Addr));
            ptt_val = (uint32 *)&f4t_physval;
            u64t_value = *ptt_val;
            break;
        case DP_SIGNALTYPE_IEEEDOUBLE:
            f8t_physval = *((double *)(ptt_sigtbl[u8t_loop].ad_Addr));
            ptt_val64 = (uint64 *)&f8t_physval;
            u64t_value = *ptt_val64;
            break;
        default:
            break;
        }

        if (u8t_byteorder == DP_BYTEORDER_MOTOROLA)
        {
//            u8t_bytepos = u8t_startpos / 8;
            u8t_bytepos = (u8t_startpos - u8t_datalen + 1)/8;
            s8t_shiftbit = (sint8)((sint8)u8t_datalen - (sint8)(u8t_startpos % 8) - (sint8)1);
            if ( s8t_shiftbit >= 0)
            {
                cout<<"u64t_value = "<<bitset<64>(u64t_value)<<endl;
                cout<<"temp = "<<bitset<64>(u64t_value >> s8t_shiftbit)<<endl;
                cout<<"temp = "<<bitset<8>((uint8)(u64t_value >> s8t_shiftbit))<<endl;
                u8t_buffer[u8t_bytepos] = u8t_buffer[u8t_bytepos] | ((uint8)(u64t_value >> s8t_shiftbit));
            }
            else
            {
                u8t_buffer[u8t_bytepos] = u8t_buffer[u8t_bytepos] | ((uint8)(u64t_value << (0 - s8t_shiftbit)));
            }
            while ( s8t_shiftbit > 0 )
            {
                s8t_shiftbit -= 8;
                u8t_bytepos++;
                u8t_datalen -= 8;
                if ( s8t_shiftbit >= 0)
                {
                    u8t_buffer[u8t_bytepos] = u8t_buffer[u8t_bytepos] | ((uint8)(u64t_value >> s8t_shiftbit));
                }
                else
                {
                    u8t_buffer[u8t_bytepos] = u8t_buffer[u8t_bytepos] | ((uint8)(u64t_value << (0 - s8t_shiftbit)));
                }
            }
        }
        else
        {
            u8t_bytepos = u8t_startpos / 8;
            s8t_shiftbit = (sint8)(u8t_startpos % 8);
            u8t_buffer[u8t_bytepos] = u8t_buffer[u8t_bytepos] | ((uint8)(u64t_value << s8t_shiftbit));
            u8t_tempdatalen = 8 - (uint8)s8t_shiftbit;
            while( u8t_datalen - u8t_tempdatalen > 0 )
            {
                u8t_bytepos++;
                u8t_buffer[u8t_bytepos] = u8t_buffer[u8t_bytepos] | ((uint8)(u64t_value >> u8t_tempdatalen));
                u8t_tempdatalen += 8;
            }
        }
    }

    if (u32t_canid > 0x7FF)
    {
        u8t_frameType = canMSG_EXT;
    }
    else
    {
        u8t_frameType = canMSG_STD;
    }

    kvrChl->setStatus(canWrite(kvrChl->getHandle(), u32t_canid, u8t_buffer, u8t_msglen, u8t_frameType));
//    if(kvrChl->getStatus()!=canOK)
//    {
//        cout<<"Can Write Failed!"<<endl;
//    }
//    else
//    {
//        cout<<"Can Write Successful!"<<endl;
//    }
}

void ecal_com_dp_SetRxStatus(uint8 status)
{
    u8g_ecal_com_dp_RxStatus = status;
}

void ecal_com_dp_SetTxStatus(uint8 status)
{
    u8g_ecal_com_dp_TxStatus = status;
}

uint32 ecal_com_dp_GetTimeCounter( void )
{
    uint16 u16t_temp_counter;
    uint32 u32t_result;
    u16t_temp_counter = 0xFFFF - u16s_ecal_com_dp_rxcounter;
    u32t_result = (uint32)(u16t_temp_counter << 16) | (uint32)(u16s_ecal_com_dp_rxcounter);
    return u32t_result;
}
