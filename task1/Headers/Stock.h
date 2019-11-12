//
// Created by Ivan Ramyk on 10/27/19.
//

#ifndef TASK1_STOCK_H
#define TASK1_STOCK_H

#include "Cargo.h"

#include <string>
#include <vector>
#include <map>

struct cargoOut  {
    Cargo cargo;
    double period;
    int count;
    double lastTime;

    cargoOut(Cargo _cargo = Cargo(), double _period = 0, int _count = 0);
};

struct cargoIn  {
    Cargo cargo;
    double period;
    int count;
    int currentCount;
    double lastTime;

    cargoIn(Cargo _cargo = Cargo(), double _period = 0, int _count = 0);
};

class Stock {
private:
    std::string name;
    double x, y;
    std::vector <std::pair<Cargo, int>> cargo;
    std::vector <cargoOut> out;
    std::vector <cargoIn> needs;

public:
    Stock(std::string _name = "", double _x = 0, double _y = 0);

    void add_needs(Cargo cargo, double period, int count);

    void add_out(Cargo cargo, double period, int count);

    std::vector <std::pair<Cargo, int>> needToTransport();

    bool operator !=(Stock B);

    double getX();

    double getY();

    std::map <Stock, int> canLoad(std::map<Stock, int> m);

    std::map<Stock, int> canLoad();

    bool operator <(Cargo that);
};

#endif //TASK1_STOCK_H
