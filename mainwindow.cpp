#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>

bool cmp(QPair<QString, int>& a, QPair<QString, int>& b) {
    return a.second < b.second;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("hello world");
}

MainWindow::~MainWindow()
{
    delete ui;
}



