//
// Created by Ivan Ramyk on 10/27/19.
//

#include "../Headers/Transport.h"

Transport::Transport(std::string _name, double _maxWeight, double _maxSize,
        double _loadTime, double _uploadTime, double _speed):
        name(_name), maxSize(_maxSize), maxWeight(_maxWeight), loadTime(_loadTime),
        uploadTime(_uploadTime), speed(_speed) {
    currentSize = 0;
    currentWeight = 0;
}

void Transport::setName(std::string _name) {
    name = _name;
}

void Transport::setLoadTime(double time) {
    loadTime = time;
}

void Transport::setUploadTime(double time) {
    uploadTime = time;
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

double Transport::getUploadTime() {
    return uploadTime;
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
    << "\n\t Time for upload: " << uploadTime
    << "\n\t Current size of goods: " << currentSize
    << "\n\t Current weight of goods: " << currentWeight
    << "\n\t Max weight of goods: " << maxWeight
    << "\n\t Max size of goods: " << maxSize
    << "\n";
    if (show_goods){
        std::cout << "Goods:\n";
        for (auto i : goods) {
            i.print();
        }
    }
}