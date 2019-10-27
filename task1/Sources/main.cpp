#include "../Headers/Cargo.h"
#include "../Headers/Transport.h"

int main() {
    Cargo("temp", 0.5, 12).print();
    Transport tr("tr", 3, 4, 5, 5, 5);
    tr.addCargo(Cargo("a", 1, 1));
    tr.print();
    tr.print(1);
    return 0;
}