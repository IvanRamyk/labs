//
// Created by Ivan Ramyk on 10/29/19.
//

#ifndef TASK3_GAMMA_H
#define TASK3_GAMMA_H

#include "Base1.h"
#include "Base2.h"

#include <memory>

class Gamma: public Base2 {
public:
    Gamma(std::shared_ptr<Base1> _base1 = nullptr,
          std::shared_ptr<Base2> _base2 = nullptr);
    ~Gamma();
};


#endif //TASK3_ALPHA_H
