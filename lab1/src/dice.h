//
// Created by Ivan Ramyk on 10/10/19.
//

#ifndef DICE_H
#define DICE_H

#include <vector>

using std::vector;
using std::pair;

class Dice{
private:
    vector <double> probabilities;
    bool valid = false;

    void checkValid();

public:
    Dice(bool random = false);

    Dice(vector <double> prob);

    void add(double prob);

    void print();

    bool isValid();

    int cntSides();

    double getSide(int k);

    bool operator ==(Dice another);
};

class SetDices{
private:
    vector <Dice> dices;

public:
    SetDices(bool random = false, int n = 10);

    SetDices(vector <Dice> d);

    double expectedSum();

    bool add(Dice dice);

    void print();

    int maxSumValue();

    int minSumValue();

    vector<pair<int, double>> probabilityForEachSum();

    SetDices operator +(SetDices another);
};

bool operator <(SetDices a, SetDices b);

bool operator ==(SetDices a, SetDices b);

#endif //DICE_H
