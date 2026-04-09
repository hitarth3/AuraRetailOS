#include "hardware/HardwareSimulator.h"
#include <iostream>
void HardwareSimulator::dispense(const std::string& item, int qty) {
    std::cout << "   [Hardware] Dispensing " << qty << " x " << item << "\n";
}
