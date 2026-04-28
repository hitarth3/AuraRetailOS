#include "core/KioskState.h"
#include "core/Kiosk.h"
#include <iostream>

void ActiveState::handle(Kiosk* kiosk) {
    std::cout << "   [State] Kiosk is ACTIVE - Full functionality available.\n";
}

void PowerSavingState::handle(Kiosk* kiosk) {
    std::cout << "   [State] Kiosk in POWER-SAVING - Screen dimmed, limited services.\n";
}

void MaintenanceState::handle(Kiosk* kiosk) {
    std::cout << "   [State] Kiosk in MAINTENANCE - All purchases disabled for servicing.\n";
}

void EmergencyLockdownState::handle(Kiosk* kiosk) {
    std::cout << "   [State] Kiosk in EMERGENCY LOCKDOWN - Only emergency supplies accessible.\n";
}
