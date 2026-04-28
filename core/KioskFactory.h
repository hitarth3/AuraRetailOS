#ifndef KIOSKFACTORY_H
#define KIOSKFACTORY_H

#include <string>
#include "core/Kiosk.h"

enum class KioskType {
    HOSPITAL,
    METRO,
    UNIVERSITY,
    DISASTER_ZONE
};

class KioskFactory {
public:
    static Kiosk* createKiosk(KioskType type, const std::string& id);
};

#endif
