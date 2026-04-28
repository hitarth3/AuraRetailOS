#ifndef KIOSKSTATE_H
#define KIOSKSTATE_H
#include <string>

class Kiosk;

class KioskState {
public:
    virtual ~KioskState() {}
    virtual void handle(Kiosk* kiosk) = 0;
    virtual std::string getName() const = 0;
};

class ActiveState : public KioskState {
public:
    void handle(Kiosk* kiosk) override;
    std::string getName() const override { return "Active mode"; }
};

class PowerSavingState : public KioskState {
public:
    void handle(Kiosk* kiosk) override;
    std::string getName() const override { return "Power-saving mode"; }
};

class MaintenanceState : public KioskState {
public:
    void handle(Kiosk* kiosk) override;
    std::string getName() const override { return "Maintenance mode"; }
};

class EmergencyLockdownState : public KioskState {
public:
    void handle(Kiosk* kiosk) override;
    std::string getName() const override { return "Emergency lockdown mode"; }
};

#endif
