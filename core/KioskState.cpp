#include "core/KioskState.h"
#include "core/Kiosk.h"
#include <iostream>
void ActiveState::handle(Kiosk* kiosk) {
    std::cout << "   [State] Kiosk is ACTIVE full functionality.\n";
}
void MaintenanceState::handle(Kiosk* kiosk) {
    std::cout << "   [State] Kiosk in MAINTENANCE purchases disabled.\n";
}
void EmergencyState::handle(Kiosk* kiosk) {
    std::cout << "   [State] Kiosk in EMERGENCY only emergency items allowed.\n";
}
