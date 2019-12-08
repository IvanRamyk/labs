//
// Created by Ivan Ramyk on 10/27/19.
//

#ifndef TASK1_STOCK_H
#define TASK1_STOCK_H

#include "Cargo.h"

#include <string>
#include <vector>
#include <map>

struct CargoProduction  {
    Cargo cargo;
    double period;
    int count;
    double last_time;

    CargoProduction(Cargo _cargo = Cargo(), double _period = 0, int _count = 0);
};

struct CargoNeeds  {
    Cargo cargo;
    double period;
    int count;
    int current_count;
    double last_time;

    explicit CargoNeeds(Cargo _cargo = Cargo(), double _period = 0, int _count = 0);
};

struct ByName : public std::binary_function<Cargo, Cargo, bool>
{
    bool operator()(Cargo lhs, Cargo rhs) const
    {
        return lhs.getName() < rhs.getName();
    }
};

class Stock {
private:
    std::string name;
    double x, y;
    std::map<Cargo, int, ByName> cargo;
    std::vector <CargoProduction> production;
    std::vector <CargoNeeds> needs;

public:
    Stock(std::string _name = "", double _x = 0, double _y = 0);

    void addNeeds(Cargo cargo, double period, int count);

    void addProduction(Cargo cargo, double period, int count);

    bool operator !=(Stock B);

    void setName(std::string _name);

    void setX(double _x);

    void setY(double _y);

    double getX();

    double getY();

    std::map <Cargo, int, ByName> getNeeds();

    std::map <Cargo, int, ByName> getProducts();

    void unload(Cargo cargo, int count);

    void load(const Cargo& _cargo, int count);

    void print();

    std::string getName();

    void update(double current_time){
        for (auto i : production) {
            while (i.last_time <= current_time - i.period) {
                std::cout << "yes ";
                if (cargo.count(i.cargo)) {
                    std::cout << i.count << " ";
                    cargo[i.cargo] += i.count;
                    std::cout << cargo[i.cargo] << "*\n";
                }
                else {
                    std::cout << i.count << " ";
                    cargo[i.cargo] = i.count;
                    std::cout << cargo[i.cargo] << "*\n";
                }
                i.last_time += i.period;
            }
        }
        for (auto i : needs) {
            if (i.last_time <= current_time - i.period) {
                i.current_count = 0;
            }
            while (i.last_time <= current_time - i.period)
                i.last_time += i.period;
        }
        std::cout << cargo.size() << " size after update\n";
    }
};


#endif //TASK1_STOCK_H
