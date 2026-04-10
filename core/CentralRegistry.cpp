#include "core/CentralRegistry.h"
#include "core/Kiosk.h"
#include <iostream>
CentralRegistry* CentralRegistry::instance = nullptr;
CentralRegistry* CentralRegistry::getInstance() {
    if (!instance) instance = new CentralRegistry();
    return instance;
}
void CentralRegistry::registerKiosk(const std::string& id, Kiosk* kiosk) {
    kiosks[id] = kiosk;
    std::cout << "[Registry] Kiosk " << id << " registered.\n";
}
Kiosk* CentralRegistry::getKiosk(const std::string& id) {
    return kiosks.count(id) ? kiosks[id] : nullptr;
}
