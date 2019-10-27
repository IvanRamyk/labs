//
// Created by Ivan Ramyk on 10/27/19.
//

#ifndef TASK1_TRADESYSTEM_H
#define TASK1_TRADESYSTEM_H

#include "Transport.h"
#include "Stock.h"
#include "Cargo.h"

#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <queue>
#include <map>

struct event {
    std::string type;
    int air;
    int ground;
    int stock;

    explicit event(std::string _event = "", int air = - 1, int ground = -1, int stock = -1);
};

class TradeSystem {
private:
    bool isSet;
    std::vector <AirTransport> airTransport;
    std::vector <GroundTransport> groundTransport;
    std::vector <Stock> stocks;
    std::vector <std::vector <std::pair<int, double>>> adjectiveStocks;
    std::vector <std::vector <std::pair<int, double>>> roadDistance;
    std::vector <int> airTransportStart;
    std::vector <int> groundTransportStart;

    void setGroundDist();

    double groundDist(int u, int v);

    double airDist(int u, int v);

    std::map <Stock, int> needs();

    bool loadAir(int transport, int stock);

    bool loadGround(int transport, int stock);

    int bestAirMove(int transport, int stock);

    int bestGroundMove(int transport, int stock);

public:

    explicit TradeSystem(std::string passToFile = "");

    void modeling(std::string passToFile = "", const int TIME = 200);

    void finishSetting();

    void addAirTransport(AirTransport _transport);

    void addGroundTransport(GroundTransport _transport);

    void addStock(const Stock& A);

    bool addRoad(const Stock& A, const Stock& B, double dist);
};

#endif //TASK1_TRADESYSTEM_H
