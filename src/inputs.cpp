/*************************************************************************
	> File Name: inputs.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年10月31日 星期二 10时21分18秒
 ************************************************************************/

#include "inputs.h"

Inputs::Inputs(int numChannel_, int *idChannel_, int bitRate_)
{
    numChannel = numChannel_;
    idChannel = idChannel_;
    bitRate = bitRate_; 
}

void Inputs::kvaserInit()
{ 
    canInitializeLibrary();

    for(int i=0;i<numChannel;i++)
    {
        hnd = canOpenChannel(idChannel[i],canOPEN_ACCEPT_VIRTUAL);
        if(hnd<0)
        {
            cout<<"Can Channel "<< idChannel[i] <<" Open not successful!"<<endl;
        }
        else
        {    
            cout<<"Can Channel "<< idChannel[i] <<" Open successful!"<<endl;
        }

        stat = canSetBusParams(hnd,bitRate,0,0,0,0,0);
        if(stat!=canOK)
        {
            cout<<"Can Channel "<< idChannel[i] <<" Set Bus Params not successful!"<<endl; 
        }
        else
        {    
            cout<<"Can Channel "<< idChannel[i] <<" Set Bus Params successful!"<<endl; 
        }
        
        stat = canBusOn(hnd);
        if(stat!=canOK)
        {
            cout<<"Can Channel "<< idChannel[i] <<" Bus On not successful!"<<endl;
        }
        else
        {  
            cout<<"Can Channel "<< idChannel[i] <<" Bus On successful!"<<endl;
        }
    }
}
