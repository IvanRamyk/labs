#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QString>

#include "blogsystem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Date date = Date(2019, 12, 15));
    ~MainWindow();

private slots:
    void on_tableWidget_cellClicked(int row, int column);

    void on_topics_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    BlogSystem system;
};
#endif // MAINWINDOW_H
