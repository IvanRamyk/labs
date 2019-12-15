#ifndef TOPIC_H
#define TOPIC_H
#include <string>
#include <vector>
#include <map>

#include "date.h"

using month = int;

class Topic
{
public:
    Topic() = default;
    Topic(std::string title, double popularity, Date current_month);
    bool changePopularity(double new_popularity, Date current_month);
    std::string getTitle();
    double getPopularity(){
        return (--_popularity.end())->second;
    }
    std::map<month, double> getPopularityHistory(){
        return _popularity;
    }

private:
    std::string _title;
    std::map<month, double> _popularity;
};

#endif // TOPIC_H
