#include "source.h"

int randomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

double randomDouble(double begin, double end) {
    double d = end - begin;
    double a = randomInt(0, 1000);
    return begin + (a / 1000.0) * d;
}


std::vector<std::pair<std::shared_ptr<Topic>, int>> SourceBlog::getMessages(Date date){
    std::vector<std::pair<std::shared_ptr<Topic>, int>> fromBlog = blog->getMessages(date - delay);
    std::vector<std::pair<std::shared_ptr<Topic>, int>> result;
    for (auto i : fromBlog){
        int cnt = 0;
        for (int k = 0; k < i.second; ++k)
            if (randomDouble(0, 1) <= probability)
                 ++cnt;
        if (cnt > 0)
            result.push_back({i.first, cnt});
    }
    return result;
}

std::vector<std::pair<std::shared_ptr<Topic>, int> > SourceFixedTopic::getMessages(Date date){
    return {{topic, randomInt(minCntMessages, maxCntMessages)}};
}
