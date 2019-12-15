#ifndef BLOGSYSTEM_H
#define BLOGSYSTEM_H

#include <memory>
#include <vector>
#include <map>

#include "topic.h"
#include "date.h"
#include "blog.h"
#include "source.h"

class BlogSystem
{
public:
    BlogSystem(Date cur);
    void nextDay();
    std::vector<std::pair<std::shared_ptr<Topic>, int>> cntMessages(std::vector<std::shared_ptr<Blog>> blogs, Date from, Date to);
    void addBlog(std::shared_ptr<Blog> _blog);
    void addTopic(std::shared_ptr<Topic> topic);
    std::pair<std::vector<std::pair<Date, double>>, std::vector<std::pair<std::shared_ptr<Blog>, int>>>
                                                            getStatistics(std::string title);
    std::vector<std::shared_ptr<Topic>> getTopics();
    Date getDate();
    std::vector<std::pair<Date, double>> topicPopularityHistory(std::string title);
    std::vector<std::pair<std::shared_ptr<Blog>, double>> topicPartInBlogs(std::string title);
    void changeTopicPopularity(std::string title, double newPop);

private:
    std::vector<std::shared_ptr<Topic>> topics;
    std::vector<std::shared_ptr<Blog>> blogs;
    Date current_date;
};

#endif // BLOGSYSTEM_H
