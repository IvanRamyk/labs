//
// Created by ivan on 15.12.19.
//

#include <gtest/gtest.h>
#include <iostream>

#include "../blogsystem.h"

TEST (TestSystem, TestBaseOptions){
    Date current(2019, 12, 15);
    BlogSystem system(current);
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
    std::shared_ptr<Source> source5(new SourcePopularity(1, 10, 10, {Seven, Eight, Best}));
    Sport->addSource(source);
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
    for (int i = 0; i < 30; ++i)
        system.nextDay();
    std::vector <std::pair<std::shared_ptr<Blog>, double>> blogs = system.topicPartInBlogs("Ukraine");
    EXPECT_EQ(blogs.size(), 1);
}

TEST (TestSystem, TestAlgorithm) {
    Date current(2019, 12, 15);
    BlogSystem system(current);
    std::shared_ptr<Topic> Ukraine(new Topic("Ukraine", 25, current));
    system.addTopic(Ukraine);
    std::shared_ptr<Topic> Football(new Topic("Football", 2, current));
    system.addTopic(Football);
    std::shared_ptr<Topic> Milk(new Topic("Milk", 21, current));
    system.addTopic(Milk);
    std::shared_ptr<Topic> Alpha(new Topic("Alpha", 5, current));
    system.addTopic(Alpha);
    std::shared_ptr<Topic> Beta(new Topic("Beta", 35, current));
    system.addTopic(Beta);
    std::shared_ptr<Topic> Gamma(new Topic("Gamma", 4, current));
    system.addTopic(Gamma);
    std::shared_ptr<Topic> One(new Topic("One", 1, current));
    system.addTopic(One);
    std::shared_ptr<Topic> Seven(new Topic("Seven", 0.7, current));
    system.addTopic(Seven);
    std::shared_ptr<Topic> Eight(new Topic("Eight", 2, current));
    system.addTopic(Eight);
    std::shared_ptr<Topic> Best(new Topic("Best", 123, current));
    system.addTopic(Best);
    std::shared_ptr<Blog> Sport(new Blog("Sport", "url"));
    std::shared_ptr<Blog> News(new Blog("News", "url"));
    std::shared_ptr<Blog> Forum(new Blog("Forum", "url"));
    std::shared_ptr<Blog> ABABAGALAMAGA(new Blog("ABABAGALAMAGA", "url"));
    system.addBlog(ABABAGALAMAGA);
    std::shared_ptr<Source> source(new SourceFixedTopic(Ukraine, 10, 10));
    std::shared_ptr<Source> source1(new SourceFixedTopic(Milk, 10, 10));
    std::shared_ptr<Source> source2(new SourceFixedTopic(Alpha, 10, 10));
    std::shared_ptr<Source> source3(new SourceFixedTopic(Beta, 10, 10));
    std::shared_ptr<Source> source4(new SourceFixedTopic(One, 10, 10));
    std::shared_ptr<Source> source5(new SourcePopularity(1, 10, 10, {Seven, Eight, Best}));
    Sport->addSource(source);
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
    system.nextDay();
    auto result = system.cntMessages({News}, current, system.getDate());
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].second, 10);
    system.nextDay();
    result = system.cntMessages({News, Sport}, current, system.getDate());
    EXPECT_EQ(result.size(), 6);
    EXPECT_EQ(result[0].second, 40);
    EXPECT_EQ(result[1].second, 20);
    EXPECT_EQ(result[2].second, 20);
    EXPECT_EQ(result[3].second, 40);
    EXPECT_EQ(result[4].second, 40);
    EXPECT_EQ(result[5].second, 20);
    result = system.cntMessages({News}, current, system.getDate() - 1);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].second, 10);

}
