#include "topic.h"

Topic::Topic(std::string title, double popularity, month month): _title(title){
    _popularity[month] = popularity;
}

bool Topic::changePopularity(double new_popularity, month current_month){
    if (_popularity.count(current_month))
        return false;
    _popularity[current_month] = new_popularity;
    return true;
}
