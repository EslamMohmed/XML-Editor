#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <sstream>
#include <QtDebug>
#include <QProcess>
#include<QMessageBox>
#include<QTextEdit>
#include <QFile>
#include <QAction>
#include <bits/stdc++.h>
using namespace std;
QT_BEGIN_NAMESPACE


namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_checkbutton_clicked();
    void on_CompressionButton_clicked();
    void on_SaveButton_clicked();
    void on_ExitButton_clicked();
    void on_Resetbutton_clicked();
    void on_FormatButton_clicked();
    void on_openButton_clicked();
    void on_minifyButton_clicked();
    void on_DecompressionButton_clicked();
    void on_XmlToJson_clicked();
    void on_correctBtutton_clicked();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
