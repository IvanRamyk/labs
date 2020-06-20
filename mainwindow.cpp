#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include <string>

void setUp(BlogSystem &system){
    Date current = system.getDate();
    std::shared_ptr<Topic>  Ukraine(new Topic("Ukraine", 25, current)); system.addTopic(Ukraine);
    std::shared_ptr<Topic>   Football(new Topic("Football", 2, current)); system.addTopic(Football);
    std::shared_ptr<Topic>   Milk(new Topic("Milk", 21, current));system.addTopic(Milk);
    std::shared_ptr<Topic>   Alpha(new Topic("Alpha", 5, current));system.addTopic(Alpha);
    std::shared_ptr<Topic>   Beta(new Topic("Beta", 35, current));system.addTopic(Beta);
    std::shared_ptr<Topic>   Gamma(new Topic("Gamma", 4, current));system.addTopic(Gamma);
    std::shared_ptr<Topic>   One(new Topic("One", 1, current));system.addTopic(One);
    std::shared_ptr<Topic>   Seven(new Topic("Seven", 0.7, current));system.addTopic(Seven);
    std::shared_ptr<Topic>   Eight(new Topic("Eight", 2, current));system.addTopic(Eight);
    std::shared_ptr<Topic>   Best(new Topic("Best", 123, current));system.addTopic(Best);
    std::shared_ptr<Blog>   Sport(new Blog("Sport", "url"));
    std::shared_ptr<Blog>   News(new Blog("News", "url"));
    std::shared_ptr<Blog>   Forum(new Blog("Forum", "url"));
    std::shared_ptr<Blog>   ABABAGALAMAGA(new Blog("ABABAGALAMAGA", "url")); system.addBlog(ABABAGALAMAGA);
    std::shared_ptr<Source> source(new SourceFixedTopic(Ukraine, 10, 10));
    std::shared_ptr<Source> source1(new SourceFixedTopic(Milk, 10, 10));
    std::shared_ptr<Source> source2(new SourceFixedTopic(Alpha, 10, 10));
    std::shared_ptr<Source> source3(new SourceFixedTopic(Beta, 10, 10));
    std::shared_ptr<Source> source4(new SourceFixedTopic(One, 10, 10));
    std::shared_ptr<Source> source5(new SourcePopularity(1, 10, 10, {Seven, Eight, Best}));Sport->addSource(source);
    ABABAGALAMAGA->addSource(source1);
    Sport->addSource(source1);
    Sport->addSource(source2);
    Sport->addSource(source3);
    Sport->addSource(source4);
    Sport->addSource(source5);
    News->addSource(source1);
    Forum->addSource(source2);
    Sport->addSource(source3);
    Sport->addSource(source4);
    ABABAGALAMAGA->addSource(source5);
    system.addBlog(Sport);
    system.addBlog(News);
    system.addBlog(Forum);
    for (int k = 1; k < 10; ++k){
        for (int i = 0; i < 60; ++i)
            system.nextDay();
        if (k % 2 == 1)
            system.changeTopicPopularity("Football", 122 * k);
        system.changeTopicPopularity("Ukraine", 0.1 * k);
    }
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
        for (int j = 0; j < ui->topics->columnCount(); ++j)
            if (j == 0)
                ui->details->setItem(i, j, new QTableWidgetItem(QString::fromUtf8(popHistory[i].first.toMonth().c_str())));
            else
                ui->details->setItem(i, j, new QTableWidgetItem(QString::fromUtf8(std::to_string(popHistory[i].second).c_str())));
    std::vector <std::pair<std::shared_ptr<Blog>, double>> blogs = system.topicPartInBlogs(data);
    for (auto i : blogs)
        std::cout << i.second << "\n";
    ui->blogs->clear();
    ui->blogs->setRowCount(blogs.size());
    ui->blogs->setColumnCount(2);
    ui->blogs->setHorizontalHeaderLabels(QStringList() << "Blog" << "Part");
    for (int i = 0; i < ui->blogs->rowCount(); ++i)
        for (int j = 0; j < ui->blogs->columnCount(); ++j)
            if (j == 0)
                ui->blogs->setItem(i, j, new QTableWidgetItem(QString::fromUtf8(blogs[i].first->getTitle().c_str())));
            else
                ui->blogs->setItem(i, j, new QTableWidgetItem(QString::fromUtf8(std::to_string(blogs[i].second).c_str())));
}
