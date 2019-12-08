#include "../Headers/TradeSystem.h"

int main() {
    TradeSystem system("../Tests/config");
    //system.print();
    system.modeling("../Tests/result");
    return 0;
}