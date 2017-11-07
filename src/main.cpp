/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年10月31日 星期二 09时31分21秒
 ************************************************************************/

#include<iostream>
#include"kvrChannel.h"
#include<unistd.h>
#include<pthread.h>

using namespace std;

void* SendAndReceive(void *arg);
void checkCanWrite(canStatus stat_);

int main()
{
    //Initialize kvaser library!
    canInitializeLibrary();



    cout<<"Hello World!"<<endl;
    //int idChl =0;
    int bitRate = 500000;

    KvrChannel kvrChl1(0,bitRate);
    KvrChannel kvrChl2(1,bitRate);

    pthread_t pth1;
    int ret = 0;

    ret = pthread_create(&pth1, NULL, SendAndReceive, (void *)&kvrChl1);
    if(ret)
    {
        cout<<"Create pthread Failed!"<<endl;
    }
    else
    {
        cout<<"Create pthread successful!"<<endl;
    }

    if(pthread_join(pth1,NULL))
    {
        cout<<"Could not join pth1"<<endl;
    }


    return 0;
}

void* SendAndReceive(void* arg)
{
    KvrChannel *ptr = (KvrChannel *)arg;

    unsigned char data[8];
    for(int i=0;i<8;i++)
    {
        data[i]='a';
    }

    while(ptr->getHandle()>=0)
    {
        ptr->setStatus(canWrite(ptr->getHandle(),1234,data,8,canMSG_EXT));
        checkCanWrite(ptr->getStatus());
        usleep(50000);
    }

    canClose(ptr->getHandle());

    return (void *)0;
}

void checkCanWrite(canStatus stat_)
{
    if(stat_!=canOK)
    {
        cout<<"Oops, Can Message Write failed!"<<endl;
    }
    else
    {
        cout<<"Can Message Write successful!"<<endl;
    }
}
