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
            cout<<"W"<<endl;break;
        case Qt::Key_S:
            cout<<"S"<<endl;break;
        case Qt::Key_A:
            cout<<"A"<<endl;break;
        case Qt::Key_D:
            cout<<"D"<<endl;break;
    default:
            cout<<"Please press W/A/S/D to control the vehicle!"<<endl;
    }
}
