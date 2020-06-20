//
// Created by Ivan Ramyk on 10/27/19.
//

#include "../Headers/Cargo.h"

Cargo::Cargo(std::string _name, double _weight, double _size) :
    name(_name),weight(_weight), size(_size) {}

void Cargo::print() {
    std::cout << "Cargo " << name << ": weight - " << weight << "; size - " << size << ";\n";
}

void Cargo::setName(std::string _name) {
    name = _name;
}

void Cargo::setWeight(double _weight) {
    weight = _weight;
}

void Cargo::setSize(double _size) {
    size = _size;
}

double Cargo::getSize() {
    return size;
}

double Cargo::getWeight() {
    return weight;
}

std::string Cargo::getName() const {
    return name;
}
