//
// Created by Ivan Ramyk on 10/28/19.
//

#ifndef TASK2_FUNCTION_H
#define TASK2_FUNCTION_H

#include  "Translate.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <set>

class Function {
public:
    template <typename ArgumentT>
    std::string calculate(ArgumentT x);

    template <typename FirstArgumentT, typename SecondArgumentT>
    std::string calculate(std::pair<FirstArgumentT, SecondArgumentT> x);

    template <typename ArgumentT>
    std::string calculate(std::vector<ArgumentT> x);
};


#include "Function.hxx"

#endif //TASK2_FUNCTION_H
