//
// Created by Ivan Ramyk on 10/27/19.
//

#include "../Headers/Stock.h"

cargoOut::cargoOut(Cargo _cargo, double _period, int _count):
cargo(_cargo), period(_period), count(_count){
    lastTime = -period;
}

cargoIn::cargoIn(Cargo _cargo, double _period, int _count):
cargo(_cargo), period(_period), count(_count){
    lastTime = 0;
    currentCount = 0;
}

Stock::Stock(std::string _name, double _x, double _y): name(_name), x(_x), y(_y) { }

void Stock::add_needs(Cargo cargo, double period, int count) {
    needs.push_back(cargoIn(cargo, period, count));
}

void Stock::add_out(Cargo cargo, double period, int count) {
    out.push_back(cargoOut(cargo, period, count));
}

std::vector <std::pair<Cargo, int>> Stock::needToTransport() {
    std::vector<std::pair<Cargo, int>> res;
    for (auto i : needs)
        if (i.currentCount != i.count)
            res.push_back({i.cargo, i.count - i.currentCount});
    return res;
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

std::map<Stock, int> Stock::canLoad() {
    return std::map<Stock, int>();
}
