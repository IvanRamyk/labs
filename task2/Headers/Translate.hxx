//
// Created by Ivan Ramyk on 10/28/19.
//

//#include "../Headers/Translate.h"


template <typename NumberT>
Translate<NumberT>::Translate() = default;

template <typename NumberT>
std::string Translate<NumberT>::numeral(int num) {
    switch (num){
        case 0:
            return "zero";
        case 1:
            return "one";
        case 2:
            return "two";
        case 3:
            return "three";
        case 4:
            return "four";
        case 5:
            return "five";
        case 6:
            return "six";
        case 7:
            return "seven";
        case 8:
            return "eight";
        case 9:
            return "nine";
        default:
            return "";
    }
}

template <>
std::string Translate<int>::translate(int number) {
    switch (number){
        case 0 ... 9:
            return numeral(number);
        case 10:
            return "ten";
        case 11:
            return "eleven";
        case 12:
            return "twelve";
        case 13:
            return "thirteen";
        case 14:
            return "fourteen";
        case 15:
            return "fifteen";
        case 16:
            return "sixteen";
        case 17:
            return "seventeen";
        case 18:
            return "eighteen";
        case 19:
            return "nineteen";
        case 20 ... 99: {
            int didgit = number % 10;
            std::string ending = "-" + numeral(didgit);
            if (didgit == 0)
                ending = "";
            switch(number / 10) {
                case 2:
                    return "twenty" + ending;
                case 3:
                    return "thirty" + ending;
                case 4:
                    return "forty" + ending;
                case 5:
                    return "fifty" + ending;
                case 6:
                    return "sixty" + ending;
                case 7:
                    return "seventy" + ending;
                case 8:
                    return "eighty" + ending;
                case 9:
                    return "ninety" + ending;
            }
        }
        case 100 ... 999: {
            int hundred = number / 100;
            std::string begining = numeral(hundred)  + " hundred";
            int to99 = number % 100;
            std::string ending = translate(to99);
            switch(to99){
                case 0:
                    return begining;
                case 11 ... 19:
                    return begining + " " + ending;
                default:
                    return begining + " and " + ending;
            }
        }
        default:
            return "too big number";

    }
}

template<typename NumbertT>
std::string Translate<NumbertT>::translate(NumbertT) {
    return "sorry please try again";
}

