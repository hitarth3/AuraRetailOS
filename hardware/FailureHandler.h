#ifndef FAILUREHANDLER_H
#define FAILUREHANDLER_H

#include <string>
#include <iostream>
#include "core/EventBus.h"

enum class FailureLevel {
    MINOR,
    MODERATE,
    CRITICAL
};

class FailureHandler {
protected:
    FailureHandler* next;
public:
    FailureHandler() : next(nullptr) {}
    virtual ~FailureHandler() { delete next; }
    void setNext(FailureHandler* n) { next = n; }
    virtual void handle(FailureLevel level, const std::string& description) = 0;
    
    void publishFailure(const std::string& description) {
        EventBus::getInstance()->publish(EVENT_HARDWARE_FAILURE, description);
    }
};

class AutomaticRetryHandler : public FailureHandler {
public:
    void handle(FailureLevel level, const std::string& description) override {
        publishFailure(description);
        if (level == FailureLevel::MINOR) {
            std::cout << "   [FailureHandler] Attempting automatic retry for: " << description << "...\n";
            std::cout << "   [FailureHandler] Issue resolved via automatic retry.\n";
        } else if (next) {
            next->handle(level, description);
        }
    }
};

class HardwareRecalibrationHandler : public FailureHandler {
public:
    void handle(FailureLevel level, const std::string& description) override {
        publishFailure(description);
        if (level == FailureLevel::MODERATE) {
            std::cout << "   [FailureHandler] Initiating hardware recalibration for: " << description << "...\n";
            std::cout << "   [FailureHandler] Recalibration successful.\n";
        } else if (next) {
            next->handle(level, description);
        }
    }
};

class TechnicianAlertHandler : public FailureHandler {
public:
    void handle(FailureLevel level, const std::string& description) override {
        publishFailure(description);
        if (level == FailureLevel::CRITICAL) {
            std::cout << "   [FailureHandler] CRITICAL: Issuing technician alert for: " << description << "!\n";
            std::cout << "   [FailureHandler] Technician has been notified.\n";
        } else if (next) {
            next->handle(level, description);
        }
    }
};

#endif
