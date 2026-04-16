#include "hardware/HardwareSimulator.h"
#include <iostream>

bool HardwareSimulator::dispense(const std::string& itemCode, int qty) {
    if (itemCode == "FAIL") {
        std::cout << "   [Hardware] [FATAL] Dispenser mechanical failure for " << itemCode << "!\n";
        return false;
    }
    std::cout << "   [Hardware] Dispensing " << qty << " x " << itemCode << "\n";
    return true;
}
