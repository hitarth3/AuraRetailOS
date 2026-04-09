#ifndef KIOSKINTERFACE_H
#define KIOSKINTERFACE_H
#include <string>
class Kiosk;
class KioskInterface {
private:
    Kiosk* kiosk;
public:
    KioskInterface(Kiosk* k);
    void setMode(const std::string& mode);
    void showStatus();
    bool buyItem(const std::string& item, int qty, double cash);
    void setPricing(const std::string& type);
};
#endif
