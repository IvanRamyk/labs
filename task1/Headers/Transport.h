//
// Created by Ivan Ramyk on 10/27/19.
//

#ifndef TASK1_TRANSPORT_H
#define TASK1_TRANSPORT_H

#include "Cargo.h"

#include <string>
#include <iostream>
#include <vector>


class Transport {
private:
    std::string name;
    double maxWeight;
    double maxSize;
    double uploadTime;
    double loadTime;
    double speed;
    double currentWeight;
    double currentSize;
    std::vector <Cargo> goods;

public:
    Transport(std::string _name = "", double _maxWeight = 0, double _maxSize = 0,
            double _loadTime = 0, double _uploadTime = 0, double _speed = 0);

    std::string getName();

    double getMaxWeight();

    double getMaxSize();

    double getUploadTime();

    double getLoadTime();

    double getSpeed();

    void setName(std::string _name);

    void setMaxWeight(double weight);

    void setMaxSize(double size);

    void setUploadTime(double time);

    void setLoadTime(double time);

    void setSpeed(double speed);

    bool addCargo(Cargo cargo);

    void print(bool show_goods = false);
};

#endif //TASK1_TRANSPORT_H
