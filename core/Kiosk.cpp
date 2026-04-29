#include "core/Kiosk.h"
#include "inventory/InventoryManager.h"
#include "hardware/HardwareSimulator.h"
#include "payment/PaymentProcessor.h"
#include "core/EventBus.h"
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
    
    if (currentState->getName() == "Emergency lockdown mode") {
        EventBus::getInstance()->publish(EVENT_EMERGENCY_MODE, "Kiosk " + id + " entered EMERGENCY LOCKDOWN!");
    }
    
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
    std::string mode = currentState->getName();
    
    if (mode == "Maintenance mode") {
        std::cout << "   [ERROR] Purchases disabled in Maintenance mode.\n";
        return false;
    }
    
    if (mode == "Emergency lockdown mode") {
        // Only allow items starting with 'E'
        if (itemCode.empty() || toupper(itemCode[0]) != 'E') {
            std::cout << "   [ERROR] Lockdown active: Only emergency supplies allowed.\n";
            return false;
        }
    }
    
    if (mode == "Power-saving mode") {
        std::cout << "   [Notice] Processing in Power-saving mode... (UI response may be slower)\n";
    }

    if (!inventory) return false;
    if (!inventory->hasStock(itemCode, quantity)) {
        std::cout << "   [ERROR] Insufficient stock.\n";
        return false;
    }
    
    double price = inventory->getPrice(itemCode);
    
    if (payment) {
        payment->displayStrategyMessage();
    }
    
    double total = payment->calculateTotal(price, quantity);
    
    if (cash < total) {
        std::cout << "   [ERROR] Insufficient cash. Need Rs." << total << "\n";
        return false;
    }
    
    if (hardware && !hardware->dispense(itemCode, quantity)) {
        std::cout << "   [ERROR] Hardware failure during dispensing.\n";
        return false;
    }
    
    payment->processPayment(total);
    inventory->reduceStock(itemCode, quantity);
    
    std::cout << "   [OK] Purchase successful. Change: Rs." << cash - total << "\n";
    return true;
}