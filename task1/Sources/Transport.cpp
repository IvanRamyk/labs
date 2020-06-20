//
// Created by Ivan Ramyk on 10/27/19.
//

#include "../Headers/Transport.h"

Transport::Transport(std::string _name, std::string _type, double _maxWeight, double _maxSize,
        double _loadTime, double _unloadTime, double _speed):
        name(_name), maxSize(_maxSize), maxWeight(_maxWeight), loadTime(_loadTime),
        unloadTime(_unloadTime), speed(_speed), type(_type) {
    currentSize = 0;
    currentWeight = 0;
}

void Transport::setName(std::string _name) {
    name = _name;
}

void Transport::setLoadTime(double time) {
    loadTime = time;
}

void Transport::setUnloadTime(double time) {
    unloadTime = time;
}

void Transport::setMaxSize(double size) {
    maxSize = size;
}

void Transport::setMaxWeight(double weight) {
    maxWeight = weight;
}

void Transport::setSpeed(double _speed) {
    speed = _speed;
}

double Transport::getMaxWeight() {
    return maxWeight;
}

double Transport::getMaxSize() {
    return maxSize;
}

double Transport::getLoadTime() {
    return loadTime;
}

double Transport::getUnloadTime() {
    return unloadTime;
}

std::string Transport::getName() {
    return name;
}

double Transport::getSpeed() {
    return speed;
}

bool Transport::addCargo(Cargo cargo, int count) {
    if ((cargo.getSize() <= maxSize - currentSize)
    && (cargo.getWeight() <= maxWeight - currentWeight)){
        int k = std::min(std::min(count, int((maxSize - currentSize) / cargo.getSize())),
                int((maxWeight - currentWeight) / cargo.getWeight()));
        for(int i = 0; i < goods.size(); ++i)
            if (goods[i].first == cargo){
                goods[i].second += k;
                return true;
            }

        goods.push_back({cargo, k});
        return true;
    }
    return false;
}

void Transport::print(bool show_goods) {
    std::cout << "Transport " << name << ":\n\tSpeed: " << speed
    << "\n\t Time for load: " << loadTime
    << "\n\t Time for unload: " << unloadTime
    << "\n\t Current size of goods: " << currentSize
    << "\n\t Current weight of goods: " << currentWeight
    << "\n\t Max weight of goods: " << maxWeight
    << "\n\t Max size of goods: " << maxSize
    << "\n";
    if (show_goods){
        std::cout << "Goods:\n";
        for (auto i : goods) {
            i.first.print();
        }
    }
}

void Transport::setType(std::string _type) {
    type = _type;
}

std::string Transport::getType() {
    return type;
}

std::map<Cargo, int, ByName> Transport::getGoods() {
    std::map <Cargo, int, ByName> result;
    for (auto i : goods)
        if (result.count(i.first))
            result[i.first] += i.second;
        else
            result[i.first] = i.second;
    return result;
}

int Transport::load(Cargo cargo, int count) {
    int k = std::min(count, std::min(int((maxWeight - currentWeight)/ cargo.getWeight()),
                                     int((maxSize - currentSize)/cargo.getSize())));
    currentSize += k * cargo.getSize();
    currentWeight += k * cargo.getWeight();
    if (k > 0)
        goods.push_back({cargo, k});
    return k;
}

int Transport::unload(Cargo cargo, int count) {
    for (int i = 0; i < goods.size(); ++i) {
        if (goods[i].first == cargo){
            int k = std::min(count, goods[i].second);
            goods[i].second -= k;
            currentSize -= k * cargo.getSize();
            currentWeight -= k * cargo.getWeight();
            if (!goods[i].second)
                goods.erase(goods.begin() + i);
            return k;
        }
    }
}
