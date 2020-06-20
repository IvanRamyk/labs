//
// Created by Ivan Ramyk on 10/29/19.
//

#include "../Headers/Gamma.h"
#include "../Headers/Global.h"

Gamma::Gamma(std::shared_ptr<Base1> _base1, std::shared_ptr<Base2> _base2) :
        Base2(_base1, _base2){
}

Gamma::~Gamma() {
    S = S - N;
}
