#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <map>
#include <vector>
#include <wbemidl.h>
#include <comdef.h>
#include <algorithm>
#include <iostream>
using namespace std;

#pragma comment(lib, "wbemuuid.lib")

#include "DnpService.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    void get_mac();
    
private slots:
    void on_pushButton_refresh_clicked();
    
private:
    Ui::MainWindow *ui;
    
    int GetWMIInformationBySQL(const char *sql, const char *pszClass, vector<map<string, string>> &vecMapOut);
    bool GetMacAddr(string &sMac);
};
#endif // MAINWINDOW_H
