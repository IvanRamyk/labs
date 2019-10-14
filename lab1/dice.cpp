//
// Created by Ivan Ramyk on 10/10/19.
//

#include "dice.h"
#include <iostream>
#include <cmath>
#include <algorithm>

using std::cout;

Dice::Dice() = default;

Dice::Dice(vector<double> prob) {
    probabilities = std::move(prob);
    check_valid();
}

void Dice::print() {
    cout <<  "Dice with " << probabilities.size() << " sides\n";
    for (int i = 0; i < probabilities.size(); ++i)
        cout << "\tFor size " << i + 1 << " probability is " << probabilities[i] << "\n";
}

void Dice::add(double prob) {
    probabilities.push_back(prob);
    check_valid();
}

void Dice::check_valid() {
    double sum = 0;
    for (auto i : probabilities)
        sum += i;
    valid = (fabs(sum - 1.0) < 1e-3);
}

bool Dice::is_valid() {
    return valid;
}

int Dice::cnt_sides(){
    return probabilities.size();
}

double Dice::get_side(int k) {
    return probabilities[k];
}

// end of class Dice

SetDices::SetDices() = default;

SetDices::SetDices(vector<Dice> d) {
    dices = std::move(d);
}

bool SetDices::add(Dice dice) {
    if (dice.is_valid()) {
        dices.push_back(dice);
        return true;
    }
    cout << "You can't add this dice because summary of probabilities is not 1\n";
    return false;
}

void SetDices::print() {
    cout << "SET WITH " << dices.size() << " dices\n";
    for (auto i : dices)
        i.print();
}

int SetDices::max_sum_value() {
    int total = 0;
    for (int i = 0; i < dices.size(); ++i)
        total += dices[i].cnt_sides();
    return total;
}

int SetDices::min_sum_value() {
    return dices.size();
}

vector<pair<int, double>> SetDices::probability_for_each_sum() {
    int min_value = min_sum_value();
    vector <double> prob_for_sum(max_sum_value() + 1, 0);
    vector <double> prob_for_second(max_sum_value() + 1, 0);
    prob_for_sum[0] = 1;
    for (int i = 0; i < dices.size(); ++i) {
        for (int j = 0; j < prob_for_sum.size(); ++j)
            for (int k = 0; k < dices[i].cnt_sides(); ++k) {
                if (j + k + 1  < prob_for_second.size())
                    prob_for_second[j + k + 1] += prob_for_sum[j] * dices[i].get_side(k);
            }
        std::swap(prob_for_second, prob_for_sum);
        std::fill(prob_for_second.begin(), prob_for_second.end(), 0);
    }
    vector <pair<int, double>> answer;
    for (int i = 0; i <= max_sum_value(); ++i)
        if (fabs(prob_for_sum[i]) > 1e-4)
            answer.push_back({i, prob_for_sum[i]});
    return answer;
}

bool SetDices::operator<(SetDices another) {
    return this->expected_sum() < another.expected_sum();
}

double SetDices::expected_sum() {
    vector <pair<int, double>> prob_for_sum = probability_for_each_sum();
    double total = 0;
    for (auto i : prob_for_sum)
        total += i.first * i.second;
    return total;
}
