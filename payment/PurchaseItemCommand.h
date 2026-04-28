#ifndef PURCHASEITEMCOMMAND_H
#define PURCHASEITEMCOMMAND_H

#include "core/Command.h"
#include "core/Kiosk.h"
#include "inventory/InventoryManager.h"
#include "core/EventBus.h"
#include <string>
#include <iostream>

class PurchaseItemCommand : public Command {
private:
    Kiosk* kiosk;
    std::string itemCode;
    int quantity;
    double cash;
    InventoryMemento* memento;
public:
    PurchaseItemCommand(Kiosk* k, const std::string& code, int qty, double amt)
        : kiosk(k), itemCode(code), quantity(qty), cash(amt), memento(nullptr) {}
    
    ~PurchaseItemCommand() {
        if (memento) delete memento;
    }

    bool execute() override {
        if (kiosk->getInventory()) {
            memento = kiosk->getInventory()->save();
        }
        
        double price = kiosk->getInventory()->getPrice(itemCode);
        double total = price * quantity; // Base total
        
        // Note: Actual total might be different if pricing strategies are applied inside kiosk->purchaseItem
        // But we want to show the calculation here.
        
        std::cout << "\n   [Calculation] " << itemCode << " x " << quantity << "\n";
        std::cout << "   [Calculation] Unit Price: Rs." << price << "\n";
        
        bool success = kiosk->purchaseItem(itemCode, quantity, cash);
        
        if (success) {
            EventBus::getInstance()->publish(EVENT_TRANSACTION, "Purchase executed: " + itemCode + " x" + std::to_string(quantity));
        } else {
            undo();
            EventBus::getInstance()->publish(EVENT_TRANSACTION, "Purchase failed & rolled back: " + itemCode);
        }
        return success;
    }

    void undo() override {
        if (memento && kiosk->getInventory()) {
            kiosk->getInventory()->restore(memento);
            std::cout << "[Command] Transaction rolled back using Memento.\n";
        }
    }
};

#endif
