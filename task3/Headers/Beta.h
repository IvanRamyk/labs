//
// Created by Ivan Ramyk on 10/29/19.
//

#ifndef TASK3_BETA_H
#define TASK3_BETA_H

#include "Base1.h"
#include "Base2.h"

#include <memory>

class Beta: public Base1 {
public:
    Beta(std::shared_ptr<Base1> _base1 = nullptr,
          std::shared_ptr<Base2> _base2 = nullptr);
    ~Beta();
};


#endif //TASK3_ALPHA_H
