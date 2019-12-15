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
    BlogSystem();
    void nextDay();
private:
    std::vector<std::shared_ptr<Topic>> topics;
    std::vector<std::shared_ptr<Blog>> blogs;
    Date current_date;
};

#endif // BLOGSYSTEM_H
