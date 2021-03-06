//
// Created by Ivan Ramyk on 10/27/19.
//

#include "../Headers/Stock.h"

CargoProduction::CargoProduction(Cargo _cargo, double _period, int _count):
cargo(_cargo), period(_period), count(_count){
    last_time = -period;
}

CargoNeeds::CargoNeeds(Cargo _cargo, double _period, int _count):
cargo(_cargo), period(_period), count(_count){
    last_time = 0;
    current_count = 0;
}

Stock::Stock(std::string _name, double _x, double _y): name(_name), x(_x), y(_y) { }

void Stock::addNeeds(Cargo cargo, double period, int count) {
    needs.push_back(CargoNeeds(cargo, period, count));
}

void Stock::addProduction(Cargo cargo, double period, int count) {
    production.push_back(CargoProduction(cargo, period, count));
}

bool Stock::operator!=(Stock B) {
    return name != B.name;
}

double Stock::getX() {
    return x;
}

double Stock::getY() {
    return y;
}


std::map<Cargo, int, ByName> Stock::getNeeds() {
    std::map<Cargo, int, ByName> result;
    for (auto &i : needs)
        if (i.count - i.current_count){
            if (result.count(i.cargo))
                result[i.cargo] += i.count - i.current_count;
            else
                result[i.cargo] = i.count - i.current_count;
        }
    return result;
}

std::map<Cargo, int, ByName> Stock::getProducts() {
    std::map<Cargo, int, ByName> result;
    for (auto i : cargo) {
        if (i.second)
            if (result.count(i.first))
                result[i.first] += i.second;
            else
                result[i.first] = i.second;
    }
    return result;
}

void Stock::unload(Cargo cargo, int count) {
    for (auto i : needs)
        if (i.cargo == cargo) {
            i.current_count += count;
            break;
        }
}

void Stock::load(const Cargo &_cargo, int count) {
    for (auto i : cargo)
        if (i.first.getName() == _cargo.getName())
            i.second -= count;
}

void Stock::setName(std::string _name) {
    name = _name;
}

void Stock::print() {
    std::cout << "Stock " << name << "\n";
    std::cout << "Coordinates: x - " << x << "; y - " << y << ";\n";
    std::cout << "Production:\n";
    for (auto i : production)
        i.cargo.print();
    std::cout << "Needs:\n";
    for (auto i : needs)
        i.cargo.print();
}

std::string Stock::getName() {
    return name;
}

void Stock::setX(double _x) {
    x = _x;
}

void Stock::setY(double _y) {
    y = _y;
}
