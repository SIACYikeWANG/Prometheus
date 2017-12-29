/*************************************************************************
	> File Name: plotEnv.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年12月29日 星期五 15时33分36秒
 ************************************************************************/

#include "plotEnv.h"
#include "pthread.h"
#include "unistd.h"
#include <iostream>

using namespace std;

void* plotEnv(void *arg)
{
    QCustomPlot *customPlot = (QCustomPlot *)arg;

    QString demoName = "Demo";

    QVector<double> x(101),y(101);

    for(int i=0;i<101;++i)
    {
        x[i] = i/50.0-1;
        y[i] = x[i]*x[i];
    }

    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x,y);

    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1,1);
    customPlot->yAxis->setRange(0,1);

    int i=0;

    while(1)
    {
        cout<<i<<endl;
        i++;
        usleep(10000);
    }
}

