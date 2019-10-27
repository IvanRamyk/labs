//
// Created by Ivan Ramyk on 10/27/19.
//

#include "../Headers/TradeSystem.h"

TradeSystem::TradeSystem(std::string passToFile) {
    if (passToFile == ""){
        isSet = false;
    }
    else {
        freopen("passToFile", "r", stdin);
        int n, m;
        std::cin >> n;
        isSet = true;
    }
}

void TradeSystem::modeling(std::string passToFile, const int TIME) {
    setGroundDist();
    std::priority_queue <std::pair <double, event>> events;
    for (int i = 0; i < airTransport.size(); ++i)
        events.push({0, event("arrive", i, -1, 0)});
    for (int i = 0; i < groundTransport.size(); ++i)
        events.push({0, event("arrive", i, -1, 0)});
    int currentTime = 0;
    while (!events.empty() && currentTime < TIME){
        event cur = events.top().second;
        currentTime = -events.top().first;
        events.pop();
        if (currentTime > TIME) break;
        int stock = cur.stock;
        int air = cur.air;
        int ground = cur.ground;
        std::string type = cur.type;
        if (cur.type == "unload"){
            if (air != - 1){
                if (loadAir(air, stock)){
                    events.push({-currentTime - airTransport[air].getLoadTime(), event("load", air, -1, stock)});
                    continue;
                }
                else {
                    int to = bestAirMove(air, stock);
                    events.push({-currentTime - airDist(stock, to)/airTransport[air].getSpeed(),
                                 event("arrive", air, -1, to)});
                    continue;
                }
            }
            else {
                if (loadGround(ground, stock)){
                    events.push({-currentTime - groundTransport[ground].getLoadTime(), event("load", -1, ground, stock)});
                    continue;
                }
                else {
                    int to = bestGroundMove(ground, stock);
                    events.push({-currentTime - groundDist(stock, to)/groundTransport[ground].getSpeed(),
                                 event("arrive", -1, ground, to)});
                    continue;
                }
            }
        }
        if (cur.type == "load"){
            if (air != - 1){
                if (loadAir(air, stock)){
                    events.push({-currentTime - airTransport[air].getLoadTime(), event("load", air, -1, stock)});
                    continue;
                }
                else {
                    int to = bestAirMove(air, stock);
                    events.push({-currentTime - airDist(stock, to)/airTransport[air].getSpeed(),
                                 event("arrive", air, -1, to)});
                    continue;
                }
            }
            else {
                if (loadGround(ground, stock)){
                    events.push({-currentTime - groundTransport[ground].getLoadTime(), event("load", -1, ground, stock)});
                    continue;
                }
                else {
                    int to = bestGroundMove(ground, stock);
                    events.push({-currentTime - groundDist(stock, to)/groundTransport[ground].getSpeed(),
                                 event("arrive", -1, ground, to)});
                    continue;
                }
            }
        }
        if (cur.type == "unload"){
            if (air != - 1){
                if (loadAir(air, stock)){
                    events.push({-currentTime - airTransport[air].getLoadTime(), event("load", air, -1, stock)});
                    continue;
                }
                else {
                    int to = bestAirMove(air, stock);
                    events.push({-currentTime - airDist(stock, to)/airTransport[air].getSpeed(),
                                 event("arrive", air, -1, to)});
                    continue;
                }
            }
            else {
                if (loadGround(ground, stock)){
                    events.push({-currentTime - groundTransport[ground].getLoadTime(), event("load", -1, ground, stock)});
                    continue;
                }
                else {
                    int to = bestGroundMove(ground, stock);
                    events.push({-currentTime - groundDist(stock, to)/groundTransport[ground].getSpeed(),
                                 event("arrive", -1, ground, to)});
                    continue;
                }
            }
        }
    }
}

void TradeSystem::finishSetting() {
    isSet = true;
}

void TradeSystem::addAirTransport(AirTransport _transport) {
    airTransport.push_back(_transport);
}

void TradeSystem::addGroundTransport(GroundTransport _transport) {
    groundTransport.push_back(_transport);
}

void TradeSystem::addStock(const Stock& A) {
    stocks.push_back(A);
    adjectiveStocks.push_back({});
    roadDistance.push_back({});
}

bool TradeSystem::addRoad(const Stock& A, const Stock& B, double dist) {
    int u = 0;
    while (u < stocks.size() && stocks[u] != A)
        u++;
    int v = 0;
    while (v < stocks.size() && stocks[v] != B)
        ++v;
    if (u < stocks.size() || v < stocks.size())
        return false;
    adjectiveStocks[u].push_back({v, dist});
    adjectiveStocks[v].push_back({u, dist});
    return true;
}

void TradeSystem::setGroundDist() {
    int n = stocks.size();
    for (int i=0; i<n; ++i)
        for (int j=0; j<n; ++j)
            roadDistance[i][j] = {-1, 1e9};
    for (int i = 0; i < n; ++i)
        for (auto j : adjectiveStocks[i])
            roadDistance[i][j.first] = {j.first, j.second};
    for (int k=0; k<n; ++k)
        for (int i=0; i<n; ++i)
            for (int j=0; j<n; ++j){
                if (roadDistance[i][k].first == -1 || roadDistance[k][j].first == -1)
                    continue;
                if (roadDistance[i][j].first == -1
                || roadDistance[i][k].second + roadDistance[k][j].second < roadDistance[i][j].second)
                    roadDistance[i][j] = {roadDistance[i][k].first,roadDistance[i][k].second + roadDistance[k][j].second};
            }
}

double TradeSystem::groundDist(int u, int v) {
    return roadDistance[u][v].second;
}

double TradeSystem::airDist(int u, int v) {
    double x1 = stocks[u].getX();
    double y1 = stocks[u].getY();
    double x2 = stocks[v].getX();
    double y2 = stocks[v].getY();
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

std::map<Stock, int> TradeSystem::needs() {
    return std::map<Stock, int>();
}

bool TradeSystem::loadAir(int transport, int stock) {
    return false;
}


bool TradeSystem::loadGround(int transport, int stock) {
    return false;
}

int TradeSystem::bestAirMove(int transport, int stock) {
    return 0;
}

int TradeSystem::bestGroundMove(int transport, int stock) {
    return 0;
}

event::event(std::string _event, int _air, int _ground, int _stock): type(_event), air(_air)
, ground(_ground), stock(_stock) {}
