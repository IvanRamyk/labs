//
// Created by Ivan Ramyk on 10/28/19.
//

#ifndef TASK2_TRANSLATE_H
#define TASK2_TRANSLATE_H

#include <string>

template <typename NumbertT>
class Translate {
private:
    std::string numeral(int num);

public:
    Translate();

    std::string translate(NumbertT);
};

#include "Translate.hxx"

#endif //TASK2_TRANSLATE_H
