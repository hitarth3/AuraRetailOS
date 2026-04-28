#ifndef REFUNDCOMMAND_H
#define REFUNDCOMMAND_H

#include "core/Command.h"
#include "core/Kiosk.h"
#include "inventory/InventoryManager.h"
#include "core/EventBus.h"
#include <string>
#include <iostream>

class RefundCommand : public Command {
private:
    Kiosk* kiosk;
    std::string itemCode;
    int quantity;
    double calculatedRefund;
    bool isValid;

public:
    RefundCommand(Kiosk* k, const std::string& code, int qty)
        : kiosk(k), itemCode(code), quantity(qty), calculatedRefund(0.0), isValid(false) {}

    bool execute() override {
        if (!kiosk->getInventory()) return false;

        // Check if item belongs to this inventory
        double price = kiosk->getInventory()->getPrice(itemCode);
        if (price <= 0) {
            std::cout << "   [ERROR] Refund rejected: Item " << itemCode << " does not belong to this kiosk's inventory.\n";
            return false;
        }

        isValid = true;
        calculatedRefund = price * quantity;
        
        std::cout << "\n   [Calculation] Refund for " << itemCode << " x " << quantity << "\n";
        std::cout << "   [Calculation] Refund Amount: Rs." << calculatedRefund << " (Rs." << price << " per unit)\n";

        kiosk->getInventory()->increaseStock(itemCode, quantity);
        
        std::cout << "   [Refund] Refunded Rs." << calculatedRefund << " for " << quantity << " x " << itemCode << "\n";
        EventBus::getInstance()->publish(EVENT_TRANSACTION, "Refund executed: " + itemCode + " x" + std::to_string(quantity) + " (Rs." + std::to_string(calculatedRefund) + ")");
        return true;
    }

    void undo() override {
        if (isValid) {
            kiosk->getInventory()->reduceStock(itemCode, quantity);
            std::cout << "[Command] Refund undone.\n";
        }
    }
};

#endif
