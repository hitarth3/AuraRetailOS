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
    std::string getName() const override { return "Active"; }
};
class MaintenanceState : public KioskState {
public:
    void handle(Kiosk* kiosk) override;
    std::string getName() const override { return "Maintenance"; }
};
class EmergencyState : public KioskState {
public:
    void handle(Kiosk* kiosk) override;
    std::string getName() const override { return "Emergency"; }
};
#endif
