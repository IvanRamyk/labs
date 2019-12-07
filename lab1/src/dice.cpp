//
// Created by Ivan Ramyk on 10/10/19.
//
#include "dice.h"

#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

using std::cout;

int randomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

double randomDouble(double begin, double end) {
    double d = end - begin;
    double a = randomInt(0, 1000);
    return begin + (a / 1000.0) * d;
}

Dice::Dice(bool random) {
    if (random){
        int n = randomInt(1, 5) * 2;
        //probabilities.resize(n);
        double total = 1;
        for (int i = 0; i < n - 1; ++i) {
            probabilities.push_back(randomDouble(0, total));
            total -= probabilities[i];
        }
        probabilities.push_back(total);
    }
    checkValid();
}

Dice::Dice(vector<double> prob) {
    probabilities = std::move(prob);
    checkValid();
}

void Dice::print() {
    cout <<  "Dice with " << probabilities.size() << " sides\n";
    for (int i = 0; i < probabilities.size(); ++i)
        cout << "\tFor size " << i + 1 << " probability is " << probabilities[i] << "\n";
}

void Dice::add(double prob) {
    probabilities.push_back(prob);
    checkValid();
}

void Dice::checkValid() {
    double sum = 0;
    for (auto i : probabilities)
        sum += i;
    valid = (fabs(sum - 1.0) < 1e-3);
}

bool Dice::isValid() {
    return valid;
}

int Dice::cntSides(){
    return probabilities.size();
}

double Dice::getSide(int k) {
    return probabilities[k];
}

bool Dice::operator==(Dice another) {
    return probabilities == another.probabilities;
}

// end of class Dice

SetDices::SetDices(bool random, int n){
    if (random){
        for (int i = 0; i < n; ++i)
            dices.push_back(Dice(true));
    }
}

SetDices::SetDices(vector<Dice> d) {
    dices = std::move(d);
}

bool SetDices::add(Dice dice) {
    if (dice.isValid()) {
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

int SetDices::maxSumValue() {
    int total = 0;
    for (int i = 0; i < dices.size(); ++i)
        total += dices[i].cntSides();
    return total;
}

int SetDices::minSumValue() {
    return dices.size();
}

vector<pair<int, double>> SetDices::probabilityForEachSum() {
    int min_value = minSumValue();
    vector <double> prob_for_sum(maxSumValue() + 1, 0);
    vector <double> prob_for_second(maxSumValue() + 1, 0);
    prob_for_sum[0] = 1;
    for (int i = 0; i < dices.size(); ++i) {
        for (int j = 0; j < prob_for_sum.size(); ++j)
            for (int k = 0; k < dices[i].cntSides(); ++k) {
                if (j + k + 1  < prob_for_second.size())
                    prob_for_second[j + k + 1] += prob_for_sum[j] * dices[i].getSide(k);
            }
        std::swap(prob_for_second, prob_for_sum);
        std::fill(prob_for_second.begin(), prob_for_second.end(), 0);
    }
    vector <pair<int, double>> answer;
    for (int i = 0; i <= maxSumValue(); ++i)
        if (fabs(prob_for_sum[i]) > 1e-4)
            answer.push_back({i, prob_for_sum[i]});
    return answer;
}

bool operator==(SetDices a, SetDices b) {
    return a.expectedSum() == b.expectedSum();
}

bool operator<(SetDices a, SetDices b) {
    return a.expectedSum() < b.expectedSum();
}

double SetDices::expectedSum() {
    vector <pair<int, double>> prob_for_sum = probabilityForEachSum();
    double total = 0;
    for (auto i : prob_for_sum)
        total += i.first * i.second;
    return total;
}

SetDices SetDices::operator+(SetDices another) {
    SetDices res;
    for (auto i : dices)
        res.add(i);
    for (auto i : another.dices)
        res.add(i);
    return res;
}