/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年10月31日 星期二 09时31分21秒
 ************************************************************************/

#include <iostream>
#include "mainWindow.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    //Initialize kvaser library!
    canInitializeLibrary();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
