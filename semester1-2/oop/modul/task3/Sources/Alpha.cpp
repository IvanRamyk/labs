//
// Created by Ivan Ramyk on 10/29/19.
//

#include "../Headers/Alpha.h"
#include "../Headers/Global.h"

Alpha::Alpha(std::shared_ptr<Base1> _base1, std::shared_ptr<Base2> _base2) :
        Base1(_base1, _base2){
}

Alpha::~Alpha() {
    S = S - N + 10;
}
