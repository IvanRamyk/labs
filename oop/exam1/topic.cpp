#include "topic.h"

Topic::Topic(std::string title, double popularity, Date date): _title(title){
    month current_month = date.year * 12 + date.month - 1;
    _popularity[current_month] = popularity;
}

bool Topic::changePopularity(double new_popularity, Date date){
    month current_month = date.year * 12 + date.month - 1;
    if (_popularity.count(current_month))
        return false;
    _popularity[current_month] = new_popularity;
    return true;
}

std::string Topic::getTitle(){
    return _title;
}

double Topic::getPopularity(){
    return (--_popularity.end())->second;
}

std::map<month, double, cmpMonth> Topic::getPopularityHistory(){
    return _popularity;
}
