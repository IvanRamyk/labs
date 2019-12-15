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
                   result.push_back(k);
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

std::pair<std::vector<std::pair<Date, double>>, std::vector<std::pair<std::shared_ptr<Blog>, int>>>//????????
BlogSystem::getStatistics(std::string title){
    std::shared_ptr<Topic> topic = nullptr;
    for (auto i : topics)
        if (title == i->getTitle()){
            topic = i;
        }
    if (topic == nullptr)
        return {};
    //TODO
}

std::vector<std::shared_ptr<Topic>> BlogSystem::getTopics(){
    return topics;
}
