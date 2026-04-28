#ifndef OBSERVER_H
#define OBSERVER_H
#include <string>

class Observer {
public:
    virtual ~Observer() {}
    virtual void onEvent(const std::string& eventType, const std::string& message) = 0;
};

#endif
