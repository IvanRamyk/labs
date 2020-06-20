//
// Created by Ivan Ramyk on 10/27/19.
//

#include "../Headers/TradeSystem.h"
#include <string>
#include <sstream>

bool isEnd(std::string s){
    int i = 0;
    while (i < s.size() && s[i] == ' ')
        ++i;
    return i < s.size() && s[i] == '}';
}

TradeSystem::TradeSystem(const char *passToFile) {
    if (passToFile == ""){
        isSet = false;
    }
    else {
        freopen(passToFile, "r", stdin);
        std::string buffer;
        while (std::getline(std::cin, buffer)){
            if (buffer.empty()) continue;
            std::stringstream ss(buffer);
            std::string class_name;
            ss >> class_name;
            if (class_name == "Stock"){
                Stock stock;
                while(std::getline(std::cin, buffer)){
                    if (buffer.empty()) continue;
                    if (isEnd(buffer)) break;
                    ss.clear();
                    std::stringstream ss_next(buffer);
                    std::string field;
                    ss_next >> field;
                    if (field == "name"){
                        ss_next >> field;
                        ss_next >> field;
                        field.erase(field.end() - 1);
                        field.erase(field.end() - 1);
                        field.erase(field.begin());
                        stock.setName(field);
                    }
                    else if (field == "x"){
                        ss_next >> field;
                        ss_next >> field;
                        field.erase(field.end() - 1);
                        stock.setX(atof(field.c_str()));
                    }
                    else if (field == "y"){
                        ss_next >> field;
                        ss_next >> field;
                        field.erase(field.end() - 1);
                        stock.setY(atof(field.c_str()));
                    }
                    else if (field == "CargoProduction" || field == "CargoNeeds"){
                        std::string type = field;
                        double period = 0;
                        int count = 0;
                        Cargo cargo;
                        while (getline(std::cin, buffer)){
                            if (buffer.empty()) continue;
                            if (isEnd(buffer)) break;
                            ss.clear();
                            std::stringstream for_cargo_production(buffer);
                            for_cargo_production >> field;
                            if (field == "period"){
                                for_cargo_production >> field;
                                for_cargo_production >> field;
                                field.erase(field.end() - 1);
                                period = atof(field.c_str());
                            }
                            else if (field == "count"){
                                for_cargo_production >> field;
                                for_cargo_production >> field;
                                field.erase(field.end() - 1);
                                count = atoi(field.c_str());
                            }
                            else if (field == "Cargo"){
                                while (getline(std::cin, buffer)) {
                                    if (buffer.empty()) continue;
                                    if (isEnd(buffer)) break;
                                    std::stringstream for_cargo(buffer);
                                    for_cargo >> field;
                                    if(field == "name") {
                                        for_cargo >> field;
                                        for_cargo >> field;
                                        field.erase(field.end() - 1);
                                        cargo.setName(field);
                                    }
                                    else if (field == "weight"){
                                        for_cargo >> field;
                                        for_cargo >> field;
                                        field.erase(field.end() - 1);
                                        cargo.setWeight(atof(field.c_str()));
                                    }
                                    else if (field == "size"){
                                        for_cargo >> field;
                                        for_cargo >> field;
                                        field.erase(field.end() - 1);
                                        cargo.setSize(atof(field.c_str()));
                                    }
                                }
                            }
                        }
                        if (type == "CargoProduction")
                            stock.addProduction(cargo, period, count);
                        else
                            stock.addNeeds(cargo, period, count);
                    }
                }
                addStock(stock);
            }
            else if (class_name == "Transport"){
                Transport  * cur_transport = new Transport;
                std::string field;
                while (getline(std::cin, buffer)) {
                    if (buffer.empty()) continue;
                    if (isEnd(buffer)) break;
                    ss.clear();
                    std::stringstream for_transport(buffer);
                    for_transport >> field;
                    if(field == "name") {
                        for_transport >> field;
                        for_transport >> field;
                        field.erase(field.end() - 1);
                        cur_transport->setName(field);
                    }
                    else if(field == "type") {
                        for_transport >> field;
                        for_transport >> field;
                        field.erase(field.end() - 1);
                        field.erase(field.end() - 1);
                        field.erase(field.begin());
                        cur_transport->setType(field);
                    }
                    else if (field == "max_weight"){
                        for_transport >> field;
                        for_transport >> field;
                        field.erase(field.end() - 1);
                        cur_transport->setMaxWeight(atof(field.c_str()));
                    }
                    else if (field == "max_size"){
                        for_transport >> field;
                        for_transport >> field;
                        field.erase(field.end() - 1);
                        cur_transport->setMaxSize(atof(field.c_str()));
                    }
                    else if (field == "unload_time"){
                        for_transport >> field;
                        for_transport >> field;
                        field.erase(field.end() - 1);
                        cur_transport->setUnloadTime(atof(field.c_str()));
                    }
                    else if (field == "load_time"){
                        for_transport >> field;
                        for_transport >> field;
                        field.erase(field.end() - 1);
                        cur_transport->setLoadTime(atof(field.c_str()));
                    }
                    else if (field == "speed"){
                        for_transport >> field;
                        for_transport >> field;
                        field.erase(field.end() - 1);
                        cur_transport->setSpeed(atof(field.c_str()));
                    }
                }
                addTransport(cur_transport);
            }
            else if (class_name == "Road"){
                std::string field;
                Stock from, to;
                double dist = 0;
                while (getline(std::cin, buffer)) {
                    if (buffer.empty()) continue;
                    if (isEnd(buffer)) break;
                    ss.clear();
                    std::stringstream for_transport(buffer);
                    for_transport >> field;
                    if (field == "from") {
                        for_transport >> field;
                        for_transport >> field;
                        field.erase(field.end() - 1);
                        field.erase(field.end() - 1);
                        field.erase(field.begin());
                        from = findStockByName(field);
                    } else if (field == "to") {
                        for_transport >> field;
                        for_transport >> field;
                        field.erase(field.end() - 1);
                        field.erase(field.end() - 1);
                        field.erase(field.begin());
                        to = findStockByName(field);
                    }
                    else if (field == "dist") {
                        for_transport >> field;
                        for_transport >> field;
                        field.erase(field.end() - 1);
                        dist = atof(field.c_str());
                    }
                }
                addRoad(from, to, dist);
            }
        }
        isSet = true;
    }
}

void TradeSystem::modeling(const char *passToFile, const int TIME) {
    freopen(passToFile, "w", stdout);
    setGroundDist();
    std::priority_queue <event> events;
    for (int i = 0; i < transport.size(); ++i)
        events.push(event("arrive", i,  0));
    double current_time = 0;
    while (!events.empty() && current_time < TIME){
        event cur = events.top();
        std::cout << cur.time << ": " << cur.transport << " " << cur.eventType
        <<  " " <<cur.stock  << "\n";
        current_time = cur.time;
        updateStocks(current_time);
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
    if (u > stocks.size() || v > stocks.size())
        return false;
    adjective_stocks[u].push_back({v, dist});
    adjective_stocks[v].push_back({u, dist});
    return true;
}

void TradeSystem::setGroundDist() {
    int n = stocks.size();
    for (int i = 0; i < n; ++i)
        road_distance[i].resize(n);
    for (int i=0; i<n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j)
                road_distance[i][j] = {-1, 1e9};
            else
                road_distance[i][j] = {-1, 0};
        }
    }
    for (int i = 0; i < n; ++i)
        for (auto j : adjective_stocks[i]) {
            road_distance[i][j.first] = {j.first, j.second};
        }
    for (int k=0; k<n; ++k)
        for (int i=0; i<n; ++i)
            for (int j=0; j<n; ++j){
                if (road_distance[i][k].first == -1 || road_distance[k][j].first == -1)
                    continue;
                if (road_distance[i][k].second + road_distance[k][j].second < road_distance[i][j].second) {
                    road_distance[i][j] = {road_distance[i][k].first,
                                           road_distance[i][k].second + road_distance[k][j].second};
                }
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

int TradeSystem::bestAirMove(int transport, int stock) {
    return stock^1;
}

int TradeSystem::bestGroundMove(int transport, int stock) {
    return stock^1;
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
    for (auto &i : stocks){
        std::map <Cargo, int, ByName> temp = i.getNeeds();
        for (auto &j : temp)
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

void TradeSystem::print() {
    for (auto i : transport)
        i->print();
    for (auto i : stocks)
        i.print();
}

Stock TradeSystem::findStockByName(std::string _name) {
    for (int i = 0; i < stocks.size(); ++i)
        if (stocks[i].getName() == _name)
            return stocks[i];
    return Stock();
}


event::event(std::string _event, int transport_number, int _stock, double _time):
eventType(_event), transport(transport_number), stock(_stock), time(_time) {}

bool operator <(event a, event b) {
    return a.time > b.time;
}
