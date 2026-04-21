#ifndef RESTOCKCOMMAND_H
#define RESTOCKCOMMAND_H

#include "core/Command.h"
#include "core/Kiosk.h"
#include "inventory/InventoryManager.h"
#include "core/EventBus.h"
#include <string>

class RestockCommand : public Command {
private:
    Kiosk* kiosk;
    std::string itemCode;
    int quantity;
public:
    RestockCommand(Kiosk* k, const std::string& code, int qty)
        : kiosk(k), itemCode(code), quantity(qty) {}

    bool execute() override {
        if (kiosk->getInventory()) {
            kiosk->getInventory()->increaseStock(itemCode, quantity);
            std::cout << "   [Restock] Restocked " << quantity << " units of " << itemCode << "\n";
            EventBus::getInstance()->publish(EVENT_TRANSACTION, "Restock executed: " + itemCode + " +" + std::to_string(quantity));
            return true;
        }
        return false;
    }

    void undo() override {
        std::cout << "[Command] Restock undo not supported.\n";
    }
};

#endif
