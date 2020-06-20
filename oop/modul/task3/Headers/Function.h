//
// Created by Ivan Ramyk on 10/29/19.
//

#ifndef TASK3_FUNCTION_H
#define TASK3_FUNCTION_H

#include "Alpha.h"
#include "Beta.h"
#include "Gamma.h"
#include "Delta.h"
#include "Global.h"

#include <string>
#include <sstream>
#include <iostream>

class Function {
private:
    std::string argument;
    static void changeValue(int &currentValue, std::string className, int N);
public:
    int predict();

    void addClass(Alpha cl);
    void addClass(Beta cl);
    void addClass(Gamma cl);
    void addClass(Delta cl);
};


#endif //TASK3_FUNCTION_H
