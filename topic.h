#ifndef TOPIC_H
#define TOPIC_H
#include <string>
#include <vector>
#include <map>
#include <date.h>

using month = int;

class Topic
{
public:
    Topic() = default;
    Topic(std::string title, double popularity, month current_month);
    bool changePopularity(double new_popularity, month current_month);

private:
    std::string _title;
    std::map<month, double> _popularity;
};

#endif // TOPIC_H
