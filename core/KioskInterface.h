#ifndef KIOSKINTERFACE_H
#define KIOSKINTERFACE_H

#include <string>

class Kiosk;

class KioskInterface {
private:
    Kiosk* kiosk;
public:
    KioskInterface(Kiosk* k);
    
    // Core requirements
    bool purchaseItem(const std::string& item, int qty, double cash);
    void refundTransaction(const std::string& item, int qty);
    void runDiagnostics();
    void restockInventory(const std::string& item, int qty);
    
    // Original methods
    void setMode(const std::string& mode);
    void showStatus();
    void setPricing(const std::string& type);
};

#endif
