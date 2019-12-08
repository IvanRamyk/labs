//
// Created by Ivan Ramyk on 10/27/19.
//

#ifndef TASK1_TRANSPORT_H
#define TASK1_TRANSPORT_H

#include "Cargo.h"
#include "Stock.h"

#include <string>
#include <iostream>
#include <vector>
#include <map>


class Transport {
private:
    std::string name;
    std::string type;
    double maxWeight;
    double maxSize;
    double unloadTime;
    double loadTime;
    double speed;
    double currentWeight;
    double currentSize;
    std::vector <std::pair<Cargo, int>> goods;

public:
    Transport(std::string _name = "", std::string _type = "", double _maxWeight = 0, double _maxSize = 0,
            double _loadTime = 0, double _unloadTime = 0, double _speed = 0);

    std::string getName();

    std::string getType();

    double getMaxWeight();

    double getMaxSize();

    double getUnloadTime();

    double getLoadTime();

    double getSpeed();

    void setName(std::string _name);

    void setType(std::string _type);

    void setMaxWeight(double weight);

    void setMaxSize(double size);

    void setUnloadTime(double time);

    void setLoadTime(double time);

    void setSpeed(double speed);

    bool addCargo(Cargo cargo, int count);

    void print(bool show_goods = false);

    std::map <Cargo, int, ByName> getGoods();

    int unload(Cargo cargo, int count);

    int load(Cargo cargo, int count);
};

#endif //TASK1_TRANSPORT_H
