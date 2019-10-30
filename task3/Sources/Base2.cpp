//
// Created by Ivan Ramyk on 10/29/19.
//

#include "../Headers/Base1.h"
#include "../Headers/Base2.h"
#include "../Headers/Global.h"


#include <iostream>
#include <memory>

int &Base2::count() const {
    static int _count = 0;
    return _count;
}

Base2::Base2(std::shared_ptr <Base1> _base1, std::shared_ptr <Base2> _base2) :
        base1(_base1), base2(_base2) {
    N = ++count();
}

void Base2::setBase1(std::shared_ptr <Base1> base) {
    base1 = base;
}

void Base2::setBase2(std::shared_ptr <Base2> base) {
    base2 = base;
}

Base2::~Base2() {
    S = S / 2 - N;
    --count();
}

int Base2::getN() {
    return N;
}

std::shared_ptr<Base1> Base1::getBase1() {
    return base1;
}

std::shared_ptr<Base2> Base1::getBase2() {
    return base2;
}


