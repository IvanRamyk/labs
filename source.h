#ifndef SOURCE_H
#define SOURCE_H

#include <vector>
#include <random>
#include <memory>

#include "topic.h"
#include "blog.h"


class Blog;

class Source
{
public:
    virtual std::vector<std::pair<std::shared_ptr<Topic>, int>> getMessages(Date date)=0;
    virtual ~Source() = default;
};

class SourceFixedTopic: public Source
{
public:
    SourceFixedTopic(std::shared_ptr<Topic> _topic, int _min, int _max): topic(_topic), minCntMessages(_min), maxCntMessages(_max) {}
    std::vector<std::pair<std::shared_ptr<Topic>, int> > getMessages(Date date) override;

private:
    int minCntMessages, maxCntMessages;
    std::shared_ptr<Topic> topic;
};


class SourceBlog: public Source
{
public:
    SourceBlog(std::shared_ptr<Blog> _blog, double prob, int _delay): blog(_blog), probability(prob), delay(_delay) {}
    std::vector<std::pair<std::shared_ptr<Topic>, int>> getMessages(Date date) override;
private:
    std::shared_ptr<Blog> blog;
    double probability;
    int delay;
};

class SourcePopularity: public Source
{
public:
    SourcePopularity (int n, int min, int max, std::vector<std::shared_ptr<Topic>> _topics):
        N(n), minCntMessages(min), maxCntMessages(max), topics(_topics) {}
    std::vector<std::pair<std::shared_ptr<Topic>, int>> getMessages(Date date) override;
private:
    int N, minCntMessages, maxCntMessages;
    std::vector<std::shared_ptr<Topic>> topics;
};






#endif // SOURCE_H
