/*************************************************************************
	> File Name: inputs.h
	> Author: 
	> Mail: 
	> Created Time: 2017年10月31日 星期二 10时09分33秒
 ************************************************************************/

#ifndef _INPUTS_H
#define _INPUTS_H
#endif

#include<iostream>
#include<canlib.h>

using namespace std;

class Inputs
{
    private:
       canHandle *hndPtr; 
       canStatus stat;
       int bitRate;
       int numChannel;
       int *idChannelPtr;

    public:
        Inputs(int numChannel_, int *idChannelPtr_, int bitRate_);
        void kvaserInit();
        ~Inputs();
};
