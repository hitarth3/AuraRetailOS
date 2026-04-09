#ifndef KIOSK_H
#define KIOSK_H
#include <string>
#include "core/KioskState.h"
class InventoryManager;
class HardwareSimulator;
class PaymentProcessor;
class Kiosk {
private:
    std::string id, location;
    KioskState* currentState;
    InventoryManager* inventory;
    HardwareSimulator* hardware;
    PaymentProcessor* payment;
public:
    Kiosk(const std::string& kioskId, const std::string& loc);
    ~Kiosk();
    void setState(KioskState* state);
    KioskState* getState() const { return currentState; }
    std::string getId() const { return id; }
    
    // ADD THESE TWO LINES:
    std::string getLocation() const { return location; }
    void setLocation(const std::string& newLoc) { location = newLoc; }
    
    void setInventory(InventoryManager* inv) { inventory = inv; }
    InventoryManager* getInventory() const { return inventory; }
    void setHardware(HardwareSimulator* hw) { hardware = hw; }
    void setPayment(PaymentProcessor* pay) { payment = pay; }
    PaymentProcessor* getPayment() const { return payment; }
    void displayStatus() const;
    bool purchaseItem(const std::string& itemCode, int quantity, double cash);
};
#endif