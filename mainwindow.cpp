#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include <string>

void setUp(BlogSystem &system){
    Date date = system.getDate();
    std::shared_ptr<Topic> a(new Topic("Ukraine", 0.5, date));
    std::shared_ptr<Topic> b(new Topic("Duncky", 0.7, date));
    std::shared_ptr<Blog> blog(new Blog("News", "url"));
    std::shared_ptr<Blog> blog1(new Blog("Sport", "url"));
    std::shared_ptr<Source> source(new SourceFixedTopic(a, 10, 20));
    std::shared_ptr<Source> source1(new SourceBlog(blog, 1, 1));
    blog->addSource(source);
    blog1->addSource(source1);
    system.addBlog(blog);
    system.addBlog(blog1);
    system.addTopic(a);
    system.addTopic(b);
    system.nextDay();
    system.nextDay();
    system.nextDay();
}

MainWindow::MainWindow(QWidget *parent, Date date)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      system(date)
{
    ui->setupUi(this);
    this->setWindowTitle("Popular topics");
    setUp(system);
    std::vector<std::shared_ptr<Topic>> topics = system.getTopics();
    ui->topics->setRowCount(topics.size());
    ui->topics->setColumnCount(2);
    ui->topics->setHorizontalHeaderLabels(QStringList() << "Title" << "Popularity");
    for (int i = 0; i < ui->topics->rowCount(); ++i)
        for (int j = 0; j < ui->topics->rowCount(); ++j)
            if (j == 0)
                ui->topics->setItem(i, j, new QTableWidgetItem(QString::fromUtf8(topics[i]->getTitle().c_str())));
            else
                ui->topics->setItem(i, j, new QTableWidgetItem(QString::fromUtf8(std::to_string(topics[i]->getPopularity()).c_str())));
    ui->topics->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    std::vector<std::pair<Date, double>> popHistory = system.topicPopularityHistory(ui->topics->takeItem(row, column)->text().toUtf8().constData());
    ui->details->setRowCount(popHistory.size());
    ui->details->setColumnCount(2);
    ui->details->setHorizontalHeaderLabels(QStringList() << "Date" << "Popularity");
    for (int i = 0; i < ui->topics->rowCount(); ++i)
        for (int j = 0; j < ui->topics->rowCount(); ++j)
            if (j == 0)
                ui->details->setItem(i, j, new QTableWidgetItem(QString::fromUtf8(popHistory[i].first.toString().c_str())));
            else
                ui->details->setItem(i, j, new QTableWidgetItem(QString::fromUtf8(std::to_string(popHistory[i].second).c_str())));
}

void MainWindow::on_topics_cellClicked(int row, int column)
{
    if (column != 0)
        return;
    std::string data = ui->topics->takeItem(row, column)->text().toUtf8().constData();
    std::vector<std::pair<Date, double>> popHistory = system.topicPopularityHistory(data);
    ui->topics->setItem(row, column, new QTableWidgetItem(QString::fromUtf8(data.c_str())));
    ui->details->clear();
    ui->details->setRowCount(popHistory.size());
    ui->details->setColumnCount(2);
    ui->details->setHorizontalHeaderLabels(QStringList() << "Date" << "Popularity");
    for (int i = 0; i < ui->topics->rowCount(); ++i)
        for (int j = 0; j < ui->topics->rowCount(); ++j)
            if (j == 0)
                ui->details->setItem(i, j, new QTableWidgetItem(QString::fromUtf8(popHistory[i].first.toString().c_str())));
            else
                ui->details->setItem(i, j, new QTableWidgetItem(QString::fromUtf8(std::to_string(popHistory[i].second).c_str())));
    std::vector <std::pair<std::shared_ptr<Blog>, double>> blogs = system.topicPartInBlogs(data);
    ui->blogs->clear();
    ui->blogs->setRowCount(blogs.size());
    ui->blogs->setColumnCount(2);
    ui->blogs->setHorizontalHeaderLabels(QStringList() << "Blog" << "Part");
    for (int i = 0; i < ui->blogs->rowCount(); ++i)
        for (int j = 0; j < ui->blogs->rowCount(); ++j)
            if (j == 0)
                ui->blogs->setItem(i, j, new QTableWidgetItem(QString::fromUtf8(blogs[i].first->getTitle().c_str())));
            else
                ui->blogs->setItem(i, j, new QTableWidgetItem(QString::fromUtf8(std::to_string(blogs[i].second).c_str())));
}
