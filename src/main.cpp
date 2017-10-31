/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年10月31日 星期二 09时31分21秒
 ************************************************************************/

#include<iostream>
#include"inputs.h"

using namespace std;

int main()
{
    cout<<"Hello World!"<<endl;
    int idChannel[2];
    idChannel[0]=0;
    idChannel[1]=1;
    int numChannl = 2;
    Inputs temp(numChannl,idChannel,canBITRATE_1M);
    temp.kvaserInit();
}
