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
    std::string eventType;
    int transport;
    int stock;
    double time;

    explicit event(std::string _event = "", int transport_number = -1, int stock = -1, double _time = 0);
};

bool operator <(event a, event b);

class TradeSystem {
private:
    bool isSet;
    std::vector <Transport *> transport;
    std::vector <Stock> stocks;
    std::vector <std::vector <std::pair<int, double>>> adjective_stocks;
    std::vector <std::vector <std::pair<int, double>>> road_distance;

    void setGroundDist();

    double groundDist(int u, int v);

    double airDist(int u, int v);

    bool unload(int transport_number, int stock);

    bool load(int transport_number, int stock);

    int bestAirMove(int transport, int stock);

    int bestGroundMove(int transport, int stock);

    event handleEvent(const event& current_event);

    std::map <Cargo, int, ByName> systemNeeds();

    Stock findStockByName(std::string _name);

public:

    explicit TradeSystem(const char *passToFile = "");

    void modeling(const char *passToFile = "", const int TIME = 200);

    void finishSetting();

    void addTransport(Transport *_transport);

    void addStock(const Stock& A);

    bool addRoad(const Stock& A, const Stock& B, double dist);

    void print();

    void updateStocks(double current_time){
        for (auto &i : stocks)
            i.update(current_time);
    }
};

#endif //TASK1_TRADESYSTEM_H
