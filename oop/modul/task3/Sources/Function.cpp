//
// Created by Ivan Ramyk on 10/30/19.
//

#include "../Headers/Function.h"


int Function::predict() {
    int total = S;
    std::stringstream ss(argument);
    std::string className;
    while (ss >> className){
        int N;
        std::cin >> N;
        changeValue(total, className, N);
    }
    return total;
}

void Function::addClass(Alpha cl) {
    argument += "a ";
    argument += std::to_string(cl.getN());
    argument += " ";
}

void Function::addClass(Beta cl) {
    argument += "b ";
    argument += std::to_string(cl.getN());
    argument += " ";
}

void Function::addClass(Gamma cl) {
    argument += "g ";
    argument += std::to_string(cl.getN());
    argument += " ";
}

void Function::addClass(Delta cl) {
    argument += "d ";
    argument += std::to_string(cl.getN());
    argument += " ";
}

void Function::changeValue(int &currentValue, std::string className, int N) {
    if (className == "a"){
        currentValue = currentValue - N + 10;
        currentValue = 2 * currentValue + N - 10;
    }
    if (className == "b"){
        currentValue = currentValue + N;
        currentValue = 2 * currentValue + N - 10;
    }
    if (className == "g"){
        currentValue = currentValue - N;
        currentValue = currentValue / 2 - N ;
    }
    if (className == "d"){
        currentValue = currentValue + N;
        currentValue = currentValue + 3 * N - 9;
    }
}
