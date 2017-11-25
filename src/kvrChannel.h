/*************************************************************************
	> File Name: kvrChannel.h
	> Author: 
	> Mail: 
	> Created Time: 2017年11月07日 星期二 08时11分54秒
 ************************************************************************/

#ifndef _KVRCHANNEL_H
#define _KVRCHANNEL_H


#include<iostream>
#include<canlib.h>
#include<string.h>

using namespace std;

class KvrChannel
{
    private:
        canHandle hnd;
        canStatus stat;
        int bitRate;
        int idChl;

    public:
        KvrChannel(int idChl_=0,int bitRate_=canBITRATE_500K);
        ~KvrChannel();
        bool checkStatus();
        bool checkHandle();
        canHandle getHandle(){ return hnd;}
        canStatus getStatus(){ return stat;}
        canStatus getStatus(canStatus stat_){ stat = stat_; return stat;}
        int getIDChl(){ return idChl; }
        int getBitRate(){ return bitRate; }
        void setHandle(canHandle hnd_){ hnd = hnd_;}
        void setStatus(canStatus stat_){ stat = stat_;}
        void setBitRate(int bitRate_){ bitRate = bitRate_;}
        void setIDChl(int idChl_){ idChl = idChl_;}
};
#endif
