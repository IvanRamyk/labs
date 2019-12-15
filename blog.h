#ifndef BLOG_H
#define BLOG_H

#include <memory>
#include <vector>
#include <string>
#include <map>

#include "date.h"
#include "topic.h"
#include "source.h"

class Source;

struct cmpDate {
    bool operator()(const Date& a, const Date& b) const {
        if (a.year != b.year)
            return a.year < b.year;
        if (a.month != b.month)
            return a.month < b.month;
        if (a.day != b.day)
            return a.day < b.day;
        return false;
    }
};

class Blog
{
public:
    Blog() = default;
    Blog(std::string _title, std::string _url);
    void addSource(std::shared_ptr<Source> source);
    std::vector<std::pair<std::shared_ptr<Topic>, int>> getMessages(Date date);
    void update(Date date);

private:
    std::string title;
    std::string URL;
    std::map<Date, std::vector<std::pair<std::shared_ptr<Topic>, int>>, cmpDate> history;
    std::vector<std::shared_ptr<Source>> sources;
};

#endif // BLOG_H
