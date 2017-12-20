/*************************************************************************
	> File Name: mainWindow.h
	> Author: 
	> Mail: 
	> Created Time: 2017年12月19日 星期二 16时10分55秒
 ************************************************************************/

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <iostream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *e);
    ~MainWindow();

private slots:
    void on_PanguGo_PushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif
