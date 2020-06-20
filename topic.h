#ifndef TOPIC_H
#define TOPIC_H
#include <string>
#include <vector>
#include <map>

#include "date.h"

using month = int;

struct cmpMonth {
    bool operator()(const month& a, const month& b) const {
        return a > b;
    }
};

class Topic
{
public:
    Topic() = default;
    Topic(std::string title, double popularity, Date current_month);
    bool changePopularity(double new_popularity, Date current_month);
    std::string getTitle();
    double getPopularity();
    std::map<month, double, cmpMonth> getPopularityHistory();

private:
    std::string _title;
    std::map<month, double, cmpMonth> _popularity;
};

#endif // TOPIC_H
