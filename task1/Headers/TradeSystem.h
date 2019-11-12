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

    explicit event(std::string _event = "", int transportNumber = -1, int stock = -1);
};

class TradeSystem {
private:
    bool isSet;
    std::vector <Transport> transport;
    std::vector <Stock> stocks;
    std::vector <std::vector <std::pair<int, double>>> adjectiveStocks;
    std::vector <std::vector <std::pair<int, double>>> roadDistance;
    std::vector <int> airTransportStart;
    std::vector <int> groundTransportStart;

    void setGroundDist();

    double groundDist(int u, int v);

    double airDist(int u, int v);

    std::map <Stock, int> needs();

    bool load(int transportNumber, int stock){
        return true;
    }

    bool upload(int transportNumber, int stock){
        return true;
    }

    int bestAirMove(int transport, int stock);

    int bestGroundMove(int transport, int stock);

    std::pair<double, event> handleEvent(const event& currentEvent, double currentTime){
        int transportNumber = currentEvent.transport;
        int stockNumber = currentEvent.stock;
        std::string eventType = currentEvent.eventType;
        if (eventType != "unload" && upload(transportNumber, stockNumber))
            return {currentTime + transport[transportNumber].getUploadTime(),
                    {event("upload", transportNumber, stockNumber)}};
        if (eventType != "load" && load(transportNumber, stockNumber))
            return {currentTime + transport[transportNumber].getLoadTime(),
                    {event("load", transportNumber, stockNumber)}};
        if (transport[transportNumber].getType() == "air"){

        }
    }

public:

    explicit TradeSystem(std::string passToFile = "");

    void modeling(std::string passToFile = "", const int TIME = 200);

    void finishSetting();

    void addTransport(Transport _transport);

    void addStock(const Stock& A);

    bool addRoad(const Stock& A, const Stock& B, double dist);
};

#endif //TASK1_TRADESYSTEM_H
