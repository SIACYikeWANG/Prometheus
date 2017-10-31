/*************************************************************************
	> File Name: inputs.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年10月31日 星期二 10时21分18秒
 ************************************************************************/

#include "inputs.h"

Inputs::Inputs(int numChannel_, int *idChannelPtr_, int bitRate_)
{
    numChannel = numChannel_;
    idChannelPtr = idChannelPtr_;
    bitRate = bitRate_; 
    idChannelPtr = new int[numChannel];
    hndPtr = new canHandle[numChannel];   
}

Inputs::~Inputs()
{
    for(int i=0;i<numChannel;i++)
    {
        canClose(hndPtr[i]);
        cout<<"Can Channel "<< i <<" is already closed!"<<endl;
    }

    delete [] idChannelPtr;
    delete [] hndPtr;
}

void Inputs::kvaserInit()
{ 
    canInitializeLibrary();

    for(int i=0;i<numChannel;i++)
    {
        hndPtr[i] = canOpenChannel(idChannelPtr[i],canOPEN_ACCEPT_VIRTUAL);
        if(hndPtr[i]<0)
        {
            cout<<"Can Channel "<< idChannelPtr[i] <<" Open not successful!"<<endl;
        }
        else
        {    
            cout<<"Can Channel "<< idChannelPtr[i] <<" Open successful!"<<endl;
        }

        stat = canSetBusParams(hndPtr[i],bitRate,0,0,0,0,0);
        if(stat!=canOK)
        {
            cout<<"Can Channel "<< idChannelPtr[i] <<" Set Bus Params not successful!"<<endl; 
        }
        else
        {    
            cout<<"Can Channel "<< idChannelPtr[i] <<" Set Bus Params successful!"<<endl; 
        }
        
        stat = canBusOn(hndPtr[i]);
        if(stat!=canOK)
        {
            cout<<"Can Channel "<< idChannelPtr[i] <<" Bus On not successful!"<<endl;
        }
        else
        {  
            cout<<"Can Channel "<< idChannelPtr[i] <<" Bus On successful!"<<endl;
        }
    }
}
