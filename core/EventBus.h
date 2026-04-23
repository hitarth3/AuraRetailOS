#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <vector>
#include <string>
#include <algorithm>
#include "inventory/Observer.h"

// Event Type Constants
const std::string EVENT_LOW_STOCK = "LOW_STOCK";
const std::string EVENT_HARDWARE_FAILURE = "HARDWARE_FAILURE";
const std::string EVENT_EMERGENCY_MODE = "EMERGENCY_MODE";
const std::string EVENT_TRANSACTION = "TRANSACTION";
const std::string EVENT_MODE_CHANGE = "MODE_CHANGE";

class EventBus {
private:
    std::vector<Observer*> observers;
    static EventBus* instance;
    EventBus() {}
public:
    static EventBus* getInstance() {
        if (!instance) instance = new EventBus();
        return instance;
    }

    void subscribe(Observer* observer) {
        observers.push_back(observer);
    }

    void publish(const std::string& eventType, const std::string& message) {
        for (auto observer : observers) {
            observer->onEvent(eventType, message);
        }
    }
};

#endif
