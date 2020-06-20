//
// Created by Ivan Ramyk on 10/27/19.
//

#ifndef TASK1_CARGO_H
#define TASK1_CARGO_H

#include <string>
#include <iostream>

class Cargo {
private:
    std::string name;
    double weight;
    double size;

public:
    explicit Cargo(std::string _name = "", double _weight = 0, double _size = 0);

    void setName(std::string _name);

    void setWeight(double _weight);

    void setSize(double _size);

    std::string getName() const;

    double getWeight();

    double getSize();

    void print();

    bool operator ==(const Cargo& that) {return this->name == that.name; }
};

//bool operator <(Cargo a, Cargo b){ return a.getName() < b.getName(); }

#endif //TASK1_CARGO_H
