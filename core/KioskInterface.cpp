#include "core/KioskInterface.h"
#include "core/Kiosk.h"
#include "core/KioskState.h"
#include "payment/PaymentProcessor.h"
#include "payment/PricingStrategy.h"

KioskInterface::KioskInterface(Kiosk* k) : kiosk(k) {}

void KioskInterface::setMode(const std::string& mode) {
    if (mode == "active")
        kiosk->setState(new ActiveState());
    else if (mode == "maintenance")
        kiosk->setState(new MaintenanceState());
    else if (mode == "emergency") {
        kiosk->setState(new EmergencyState());
        // Automatically apply emergency pricing (90% off)
        PaymentProcessor* pp = kiosk->getPayment();
        if (pp) {
            pp->setStrategy(new EmergencyPricing());
        }
    }
}

void KioskInterface::showStatus() {
    kiosk->displayStatus();
}

bool KioskInterface::buyItem(const std::string& item, int qty, double cash) {
    return kiosk->purchaseItem(item, qty, cash);
}

void KioskInterface::setPricing(const std::string& type) {
    PaymentProcessor* pp = kiosk->getPayment();
    if (!pp) return;
    if (type == "standard")
        pp->setStrategy(new StandardPricing());
    else if (type == "discount")
        pp->setStrategy(new DiscountPricing(0.2));
    else if (type == "emergency")
        pp->setStrategy(new EmergencyPricing());
}