/*************************************************************************
	> File Name: kvrChannel.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月07日 星期二 08时18分33秒
 ************************************************************************/

#include"kvrChannel.h"


//Default: Channel ID = 0, Bit rate = 500K
KvrChannel::KvrChannel(int idChl_,int bitRate_)
{
    idChl = idChl_;
    bitRate = bitRate_;

    hnd = canOpenChannel(idChl,canOPEN_ACCEPT_VIRTUAL);

    if(checkHandle())
    {
        cout<<"Channel "<<idChl<<" Open successful!"<<endl;
    }
    else
    {
        cout<<"Channel "<<idChl<<" Open failed!"<<endl;
    }

    stat = canSetBusParams(hnd, bitRate, 0, 0, 0, 0, 0);
    if(checkStatus())
    {
        cout<<"Channel "<<idChl<<" Set Parameters successful!"<<endl;
    }
    else
    {
        cout<<"Channel "<<idChl<<" Set Parameters failed!"<<endl;
    }

    stat = canBusOn(hnd);
    if(checkStatus())
    {
        cout<<"Channel "<<idChl<<" Bus On successful!"<<endl;
    }
    else
    {
        cout<<"Channel "<<idChl<<" Bus On failed!"<<endl;
    }
}

KvrChannel::~KvrChannel()
{
    stat = canBusOff(hnd);
    if(checkStatus())
    {
        cout<<"Channel "<<idChl<<" Bus Off successful!"<<endl;
    }
    else
    {
        cout<<"Channel "<<idChl<<" Bus Off failed!"<<endl;
    }

    stat = canClose(hnd);
    if(checkStatus())
    {
        cout<<"Channel "<<idChl<<" Bus Close successful!"<<endl;
    }
    else
    {
        cout<<"Channel "<<idChl<<" Bus Close failed!"<<endl;
    }
}

bool KvrChannel::checkStatus()
{
    if(stat!=canOK)
    {
        string buf;
        canGetErrorText(stat,(char *)buf.data(),100);
        cout<<"Channel "<<idChl<<" Status Error! "<<buf<<endl;
        return false;
    }
    else
    {
        return true;
    }
}

bool KvrChannel::checkHandle()
{
    if(hnd<0)
    {
        cout<<"Channel "<<idChl<<" Handle Error!"<<endl;
        return false;
    }
    else
    {
        return true;
    }
}

void KvrChannel::setData(unsigned char *data_, unsigned int dataLen_)
{
    for(int i=0;i<dataLen_;i++)
    {
        data[i] = data_[i];
    }
}
