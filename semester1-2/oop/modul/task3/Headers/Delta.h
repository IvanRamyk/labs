//
// Created by Ivan Ramyk on 10/29/19.
//

#ifndef TASK3_DELTA_H
#define TASK3_DELTA_H

#include "Base1.h"
#include "Base2.h"

#include <memory>

class Delta: public Base2 {
public:
    Delta(std::shared_ptr<Base1> _base1 = nullptr,
          std::shared_ptr<Base2> _base2 = nullptr);
    ~Delta();
};


#endif //TASK3_ALPHA_H
