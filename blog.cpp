#include "blog.h"

#include <iostream>

Blog::Blog(std::string _name, std::string _url):title(_name), URL(_url) {}

void Blog::addSource(std::shared_ptr<Source> source) {
    sources.push_back(source);
}

std::vector <std::pair<std::shared_ptr<Topic>, int>> Blog::getMessages(Date date){
    if (history.count(date)){
        return history[date];
    }
    return {};
}

void Blog::update(Date date){
    std::vector <std::pair<std::shared_ptr<Topic>, int>> newMessages;
    for (auto &i : sources){
        std::vector <std::pair<std::shared_ptr<Topic>, int>> temp = i->getMessages(date);
        for (auto &k : temp){
            bool alreadyInList = false;
            for (auto& added : newMessages)
                if (k.first == added.first){
                    added.second += k.second;
                    alreadyInList = true;
                }
            if (!alreadyInList)
                newMessages.push_back(k);
        }
    }
    history[date] = newMessages;
}

double Blog::topicPart(std::string title){
    int total = 0, cnt_topic = 0;
    for (auto i : history){
        for (auto j : i.second){
            total += j.second;
            if (j.first->getTitle() == title)
                cnt_topic += j.second;
        }
    }
    if (total < 0.0001)
        return 0;
    return (double(cnt_topic) / total);
}
