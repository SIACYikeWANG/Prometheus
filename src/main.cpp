/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年10月31日 星期二 09时31分21秒
 ************************************************************************/

#include <iostream>
#include "kvrChannel.h"
#include <unistd.h>
#include <pthread.h>
#include "dbcparser.h"
#include "dev_kvaser.h"
#include "body_dbc_conf.h"
#include "dev_kvaser.h"
#include "dbc_test.h"
#include "mainWindow.h"
#include <QApplication>

using namespace std;

void* Proc_ParseData_Srv0Can0(void *arg);

extern RxSlotType stg_RxSlot[8];

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //Initialize kvaser library!
    canInitializeLibrary();

    int bitRate = canBITRATE_500K;

    KvrChannel kvrChl0(0,bitRate);

    pthread_t pth0,pth1,pth2;

    StartCanTxMsgTask(&pth0,&kvrChl0); // 开始发送
    StartCanRxMsgTask(&pth1,&kvrChl0); // 开始接受
    StartCanParserTask(&pth2); // Start Can message parsering

    if(pthread_join(pth0,NULL))
    {
        cout<<"Could not join pth0"<<endl;
    }

    if(pthread_join(pth1,NULL))
    {
        cout<<"Could not join pth1"<<endl;
    }

    if(pthread_join(pth2,NULL))
    {
        cout<<"Could not join pth2"<<endl;
    }

    return a.exec();
}
