//
// Created by Ivan Ramyk on 10/29/19.
//

#include "../Headers/Beta.h"
#include "../Headers/Global.h"

Beta::Beta(std::shared_ptr<Base1> _base1, std::shared_ptr<Base2> _base2) :
        Base1(_base1, _base2){
}

Beta::~Beta() {
    S = S + N;
}
