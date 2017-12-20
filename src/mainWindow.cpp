/*************************************************************************
	> File Name: mainWindow.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年12月19日 星期二 16时11分03秒
 ************************************************************************/

#include "mainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
        case Qt::Key_W:
//            cout<<"W"<<endl;break;
            ESP_Throttle_300_CAN1++;
        case Qt::Key_S:
//            cout<<"S"<<endl;break;
            ESP_Throttle_300_CAN1--;
        case Qt::Key_A:
//            cout<<"A"<<endl;break;
            EPS_SteeringAngleReq_112_CAN1++;
        case Qt::Key_D:
//            cout<<"D"<<endl;break;
            EPS_SteeringAngleReq_112_CAN1--;
        case Qt::Key_R:
            ESP_Throttle_300_CAN1 = 0;
            EPS_StsReq_112_CAN1 = 0;
            EPS_SteeringAngleReq_112_CAN1 = 0;
    default:
            cout<<"Please press W/A/S/D/R to control the vehicle!"<<endl;
    }
}

void MainWindow::on_PanguGo_PushButton_clicked()
{
    ESP_Throttle_300_CAN1 = 0;
    EPS_StsReq_112_CAN1 = 1;
    EPS_SteeringAngleReq_112_CAN1 = 0;

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
}

void MainWindow::on_Stop_PushButton_clicked()
{
    ESP_Throttle_300_CAN1 = 0;
    EPS_StsReq_112_CAN1 = 0;
    EPS_SteeringAngleReq_112_CAN1 = 0;
}
