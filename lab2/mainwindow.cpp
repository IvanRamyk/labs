#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tab.h"

#include <QTabWidget>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newNote_clicked()
{
    close();
}


void MainWindow::on_newGroup_clicked()
{

    //close();
    ui->tabWidget->addTab(new Tab(), "Temp");
}
