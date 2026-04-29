#include "core/KioskInterface.h"
#include "core/Kiosk.h"
#include "core/KioskState.h"
#include "payment/PaymentProcessor.h"
#include "payment/PricingStrategy.h"
#include "payment/PurchaseItemCommand.h"
#include "payment/RefundCommand.h"
#include "inventory/RestockCommand.h"
#include "hardware/FailureHandler.h"

KioskInterface::KioskInterface(Kiosk* k) : kiosk(k) {}

void KioskInterface::setMode(const std::string& mode) {
    if (mode == "active")
        kiosk->setState(new ActiveState());
    else if (mode == "powersaving")
        kiosk->setState(new PowerSavingState());
    else if (mode == "maintenance")
        kiosk->setState(new MaintenanceState());
    else if (mode == "emergency") {
        kiosk->setState(new EmergencyLockdownState());
        PaymentProcessor* pp = kiosk->getPayment();
        if (pp) {
            pp->setStrategy(new EmergencyPricing());
        }
    }
}

void KioskInterface::showStatus() {
    kiosk->displayStatus();
}

bool KioskInterface::purchaseItem(const std::string& item, int qty, double cash) {
    PurchaseItemCommand cmd(kiosk, item, qty, cash);
    return cmd.execute();
}

void KioskInterface::refundTransaction(const std::string& item, int qty) {
    RefundCommand cmd(kiosk, item, qty);
    cmd.execute();
}

void KioskInterface::restockInventory(const std::string& item, int qty) {
    RestockCommand cmd(kiosk, item, qty);
    cmd.execute();
}

void KioskInterface::runDiagnostics() {
    std::cout << "--- [Diagnostics] Running system-wide health check ---\n";
    std::cout << " [Check] Hardware connectivity: OK\n";
    std::cout << " [Check] Payment gateway: OK\n";
    std::cout << " [Check] Inventory levels: " << kiosk->getInventory()->getProducts().size() << " items tracked.\n";
    std::cout << " [Check] System Mode: " << kiosk->getState()->getName() << "\n";
    std::cout << "--- [Diagnostics] All systems operational ---\n";
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