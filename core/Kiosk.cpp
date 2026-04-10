#include "core/Kiosk.h"
#include "inventory/InventoryManager.h"
#include "hardware/HardwareSimulator.h"
#include "payment/PaymentProcessor.h"
#include <iostream>

Kiosk::Kiosk(const std::string& kioskId, const std::string& loc)
    : id(kioskId), location(loc), currentState(new ActiveState()),
      inventory(nullptr), hardware(nullptr), payment(nullptr) {
    std::cout << "[Kiosk] Created " << id << " at " << location << "\n";
}

Kiosk::~Kiosk() {
    delete currentState;
}

void Kiosk::setState(KioskState* state) {
    delete currentState;
    currentState = state;
    std::cout << "[Kiosk " << id << "] Mode changed to " << currentState->getName() << "\n";
    currentState->handle(this);
}

void Kiosk::displayStatus() const {
    std::cout << "\n=== Kiosk " << id << " ===\n";
    std::cout << "Location: " << location << "\n";
    std::cout << "Mode: " << currentState->getName() << "\n";
    if (payment) {
        std::cout << "Pricing: " << payment->getStrategyName() << "\n";
    }
    if (inventory) inventory->showStock();
}

bool Kiosk::purchaseItem(const std::string& itemCode, int quantity, double cash) {
    if (currentState->getName() == "Maintenance") {
        std::cout << "   [ERROR] Cannot purchase in Maintenance mode.\n";
        return false;
    }
    if (currentState->getName() == "Emergency" && itemCode != "E001") {
        std::cout << "   [ERROR] Emergency mode: Only FirstAid (E001) allowed.\n";
        return false;
    }
    if (!inventory) return false;
    if (!inventory->hasStock(itemCode, quantity)) {
        std::cout << "   [ERROR] Insufficient stock.\n";
        return false;
    }
    
    double price = inventory->getPrice(itemCode);
    
    // Show pricing strategy message (discount info)
    if (payment) {
        payment->displayStrategyMessage();
    }
    
    double total = payment->calculateTotal(price, quantity);
    
    if (cash < total) {
        std::cout << "   [ERROR] Insufficient cash. Need Rs." << total << "\n";
        return false;
    }
    
    if (hardware) hardware->dispense(itemCode, quantity);
    payment->processPayment(total);
    inventory->reduceStock(itemCode, quantity);
    
    std::cout << "   [OK] Purchase successful. Change: Rs." << cash - total << "\n";
    return true;
}