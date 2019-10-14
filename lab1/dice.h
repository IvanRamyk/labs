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
    void check_valid();

public:
    Dice();

    Dice(vector <double> prob);

    void add(double prob);

    void print();

    bool is_valid();

    int cnt_sides();

    double get_side(int k);
};

class SetDices{
private:
    vector <Dice> dices;
    double expected_sum();

public:
    SetDices();

    SetDices(vector <Dice> d);

    bool add(Dice dice);

    void print();

    int max_sum_value();

    int min_sum_value();

    vector<pair<int, double>> probability_for_each_sum();

    bool operator <(SetDices another);
};

#endif //DICE_H
