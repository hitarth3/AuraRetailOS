#ifndef HARDWARESIMULATOR_H
#define HARDWARESIMULATOR_H

#include <string>

class HardwareSimulator {
public:
    bool dispense(const std::string& itemCode, int qty);
};

#endif
