#include "blogsystem.h"

#include <iostream>

BlogSystem::BlogSystem(Date cur): current_date(cur) {}

void BlogSystem::nextDay(){
    current_date = current_date + Date(1);
    for (auto &i : blogs)
        i->update(current_date);
}

std::vector<std::pair<std::shared_ptr<Topic>, int>> BlogSystem::cntMessages(std::vector<std::shared_ptr<Blog>> blogs, Date from, Date to){
   if (to < from) 
       return {};
   std::vector<std::pair<std::shared_ptr<Topic>, int>> result;
   for (auto blog : blogs){
       for (Date cur = from; cur != (to + Date(1)); cur = cur + Date(1)){
           std::vector<std::pair<std::shared_ptr<Topic>, int>> temp = blog->getMessages(cur);
           for (auto k : temp){
               bool alreadyInList = false;
               for (auto& added : result)
                   if (k.first == added.first){
                       added.second += k.second;
                       alreadyInList = true;
                   }
               if (!alreadyInList) {
                   result.push_back({k.first, k.second});
               }
           }
       }
   }
   return result;
}

void BlogSystem::addBlog(std::shared_ptr<Blog> blog){
    blogs.push_back(blog);
}

void BlogSystem::addTopic(std::shared_ptr<Topic> topic){
    topics.push_back(topic);
}

std::vector<std::shared_ptr<Topic>> BlogSystem::getTopics(){
    return topics;
}

Date BlogSystem::getDate(){
    return current_date;
}

std::vector<std::pair<Date, double>> BlogSystem::topicPopularityHistory(std::string title){
    for (auto i : topics)
        if (i->getTitle() == title){
            std::map<month, double, cmpMonth> history = i->getPopularityHistory();
            std::vector<std::pair<Date, double>> result;
            for (auto cur : history)
                result.push_back({Date(cur.first / 12, cur.first % 12 + 1, 1), cur.second});
            return result;
        }
}

std::vector<std::pair<std::shared_ptr<Blog>, double>> BlogSystem::topicPartInBlogs(std::string title){
    std::vector<std::pair<std::shared_ptr<Blog>, double>> result;
    for (auto i : blogs){
        double cur = i->topicPart(title);
        if (cur > 0.001)
            result.push_back({i, cur});
    }
    return result;
}
void BlogSystem::changeTopicPopularity(std::string title, double newPop){
    for (auto i : topics)
        if (i->getTitle() == title){
            i->changePopularity(newPop, current_date);
        }
}
