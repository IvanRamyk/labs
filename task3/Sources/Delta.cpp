//
// Created by Ivan Ramyk on 10/29/19.
//

#include "../Headers/Delta.h"
#include "../Headers/Global.h"

#include <iostream>

Delta::Delta(std::shared_ptr<Base1> _base1, std::shared_ptr<Base2> _base2) :
    Base2(_base1, _base2){
}

Delta::~Delta() {
    S = S + 3 * N - 9;
}
