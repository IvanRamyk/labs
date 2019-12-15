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
    Date getDate(){
        return current_date;
    }
    std::vector<std::pair<Date, double>> topicPopularityHistory(std::string title){
        for (auto i : topics)
            if (i->getTitle() == title){
                std::map<month, double> history = i->getPopularityHistory();
                std::vector<std::pair<Date, double>> result;
                for (auto cur : history)
                    result.push_back({Date(cur.first / 12, cur.first % 12 + 1, 1), cur.second});
                return result;
            }
    }
    std::vector<std::pair<std::shared_ptr<Blog>, double>> topicPartInBlogs(std::string title){
        std::vector<std::pair<std::shared_ptr<Blog>, double>> result;
        for (auto i : blogs){
            double cur = i->topicPart(title);
            if (cur > 0.001)
                result.push_back({i, cur});
        }
        return result;
    }

    void changeTopicPopularity(std::string title, double newPop){
        for (auto i : topics)
            if (i->getTitle() == title){
                i->changePopularity(newPop, current_date);
            }
    }

private:
    std::vector<std::shared_ptr<Topic>> topics;
    std::vector<std::shared_ptr<Blog>> blogs;
    Date current_date;
};

#endif // BLOGSYSTEM_H
