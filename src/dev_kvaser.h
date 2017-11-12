/*************************************************************************
	> File Name: dev_kvaser.h
	> Author: 
	> Mail: 
	> Created Time: 2017年11月12日 星期日 15时50分34秒
 ************************************************************************/

#ifndef _DEV_KVASER_H
#define _DEV_KVASER_H

#include "canlib.h"

#define MAX_CHANNELS 63   //cannot be more because waitforsingle object can "only" handle 64 events

typedef struct {
  int           channel;
  char          name[100];
  unsigned long hwType;
  canHandle     hnd;
  int           hwIndex;
  int           hwChannel;
  int           isOnBus;
  int           driverMode;
  int           txAck;
} ChannelDataStruct;

typedef struct {
  unsigned int       channelCount;

  ChannelDataStruct  Channel[MAX_CHANNELS];

} driverData;

typedef struct
{
    canStatus     Status;
    long          CanId;
    unsigned char Data[8];
    unsigned int  Datalen;
    unsigned int  Flag;
    unsigned long TimeStamp;
}KvaserCanMsgType;

//int InitKvaser(int baudrate, int channel);
//int CloseKvaser(int channel);
int StartCanRxMsgTask(pthread_t pth, int kvaserChannelNo);
int StartCanTxMsgTask(int kvaserChannelNo);

void* Proc_Can0TxMsg(void *arg);
void* Proc_Can0RxMsg(void *arg);

//void UpdateTTCWarning(int warnFlg, RadarLocation l);
//void UpdateTcpFrame(CurTrkType_Phy tracks[], int trkNum, RadarLocation l);
//canStatus TransmitMsg(int channel, long canId, byte data[], int dataLen, int frameType);

//DWORD WINAPI CanTxMsgProc(LPVOID lpParameter)

#endif
