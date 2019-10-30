//
// Created by Ivan Ramyk on 10/29/19.
//

#include "../Headers/Base1.h"
#include "../Headers/Base2.h"
#include "../Headers/Global.h"

#include <memory>

int &Base1::count() const {
    static int _count = 0;
    return _count;
}

Base1::Base1(std::shared_ptr <Base1> _base1, std::shared_ptr <Base2> _base2) :
        base1(_base1), base2(_base2) {
    N = ++count();
}

void Base1::setBase1(std::shared_ptr <Base1> base) {
    base1 = base;
}

void Base1::setBase2(std::shared_ptr <Base2> base) {
    base2 = base;
}

Base1::~Base1() {
    S = S * 2 + N - 10;
    --count();
}

int Base1::getN() {
    return N;
}
