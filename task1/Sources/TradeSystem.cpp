//
// Created by Ivan Ramyk on 10/27/19.
//

#include "../Headers/TradeSystem.h"
#include <string>
#include <sstream>

TradeSystem::TradeSystem(const char *passToFile) {
    if (passToFile == ""){
        isSet = false;
    }
    else {
        freopen(passToFile, "r", stdin);
        std::cout << "ok";
        std::string buffer;
        while (std::getline(std::cin, buffer)){
            if (buffer.empty()) continue;
            std::stringstream ss(buffer);
            std::string class_name;
            ss >> class_name;
        }
        isSet = true;
    }
}

void TradeSystem::modeling(std::string passToFile, const int TIME) {
    freopen("passToFile", "w", stdout);
    setGroundDist();
    std::priority_queue <event> events;
    for (int i = 0; i < transport.size(); ++i)
        events.push(event("arrive", i,  transport_start[i]));
    double currentTime = 0;
    while (!events.empty() && currentTime < TIME){
        event cur = events.top();
        currentTime = cur.time;
        events.pop();
        events.push(handleEvent(cur));
    }
}

void TradeSystem::finishSetting() {
    isSet = true;
}

void TradeSystem::addTransport(Transport *_transport) {
    transport.push_back(_transport);
}

void TradeSystem::addStock(const Stock& A) {
    stocks.push_back(A);
    adjective_stocks.push_back({});
    road_distance.push_back({});
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
    adjective_stocks[u].push_back({v, dist});
    adjective_stocks[v].push_back({u, dist});
    return true;
}

void TradeSystem::setGroundDist() {
    int n = stocks.size();
    for (int i=0; i<n; ++i)
        for (int j=0; j<n; ++j)
            road_distance[i][j] = {-1, 1e9};
    for (int i = 0; i < n; ++i)
        for (auto j : adjective_stocks[i])
            road_distance[i][j.first] = {j.first, j.second};
    for (int k=0; k<n; ++k)
        for (int i=0; i<n; ++i)
            for (int j=0; j<n; ++j){
                if (road_distance[i][k].first == -1 || road_distance[k][j].first == -1)
                    continue;
                if (road_distance[i][j].first == -1
                || road_distance[i][k].second + road_distance[k][j].second < road_distance[i][j].second)
                    road_distance[i][j] = {road_distance[i][k].first,road_distance[i][k].second + road_distance[k][j].second};
            }
}

double TradeSystem::groundDist(int u, int v) {
    return road_distance[u][v].second;
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

int TradeSystem::bestAirMove(int transport, int stock) {
    return 0;
}

int TradeSystem::bestGroundMove(int transport, int stock) {
    return 0;
}

event TradeSystem::handleEvent(const event &current_event) {
    int transport_number = current_event.transport;
    int stock_number = current_event.stock;
    std::string eventType = current_event.eventType;
    double current_time = current_event.time;
    if (eventType != "unload" && unload(transport_number, stock_number))
        return event("unload", transport_number, stock_number,
                     current_time + transport[transport_number]->getUnloadTime());
    if (eventType != "load" && load(transport_number, stock_number))
        return event("load", transport_number, stock_number,
                     current_time + transport[transport_number]->getLoadTime());
    if (transport[transport_number]->getType() == "air"){
        int stock_to_move = bestAirMove(transport_number, stock_number);
        double move_time = airDist(stock_number, stock_to_move) / transport[transport_number]->getSpeed();
        return event("arrive", transport_number, stock_to_move, current_time + move_time);
    }
    if (transport[transport_number]->getType() == "ground"){
        int stock_to_move = bestGroundMove(transport_number, stock_number);
        double move_time = groundDist(stock_number, stock_to_move) / transport[transport_number]->getSpeed();
        return event("arrive", transport_number, stock_to_move, current_time + move_time);
    }
}

bool TradeSystem::unload(int transport_number, int stock) {
    bool result = false;
    std::map<Cargo, int, ByName> needs = stocks[stock].getNeeds();
    std::map<Cargo, int, ByName> goods = transport[transport_number]->getGoods();
    for (auto i : needs)
        for (auto j : goods)
            if (i.first.getName() == j.first.getName()){
                result = true;
                int count = std::min(i.second, j.second);
                stocks[stock].unload(i.first, count);
                transport[transport_number]->unload(i.first, count);
            }
    return result;
}

std::map<Cargo, int, ByName> TradeSystem::systemNeeds() {
    std::map <Cargo, int, ByName> result;
    for (auto i : stocks){
        std::map <Cargo, int, ByName> temp = i.getNeeds();
        for (auto j : temp)
            if (result.count(j.first))
                result[j.first] += j.second;
            else
                result[j.first] = j.second;
    }
    return result;
}

bool TradeSystem::load(int transport_number, int stock) {
    bool result = false;
    std::map <Cargo, int, ByName> products = stocks[stock].getProducts();
    std::map <Cargo, int, ByName> system_needs = systemNeeds();
    for (auto i : products)
        if (system_needs.count(i.first)){
            int count = std::min(i.second, system_needs[i.first]);
            int k = transport[transport_number]->load(i.first, count);
            if (k > 0)
                result = true;
            stocks[stock].load(i.first, k);
        }
    return result;
}


event::event(std::string _event, int transport_number, int _stock, double _time):
eventType(_event), transport(transport_number), stock(_stock), time(_time) {}

bool operator <(event a, event b) {
    return a.time > b.time;
}
