#include "inventory/InventoryManager.h"
#include "core/EventBus.h"
#include <iostream>
#include <cctype>

void InventoryManager::addProduct(const Product& p) {
    products.push_back(p);
}

bool InventoryManager::hasStock(const std::string& code, int qty) const {
    for (const auto& p : products)
        if (p.getCode() == code && p.getStock() >= qty) return true;
    return false;
}

double InventoryManager::getPrice(const std::string& code) const {
    for (const auto& p : products)
        if (p.getCode() == code) return p.getPrice();
    return 0.0;
}

void InventoryManager::reduceStock(const std::string& code, int qty) {
    for (auto& p : products) {
        if (p.getCode() == code) {
            p.reduceStock(qty);
            if (p.getStock() < 3) {
                EventBus::getInstance()->publish(EVENT_LOW_STOCK, "Item " + code + " (" + p.getName() + ") is low on stock: " + std::to_string(p.getStock()));
            }
        }
    }
}

void InventoryManager::increaseStock(const std::string& code, int qty) {
    for (auto& p : products) {
        if (p.getCode() == code) {
            p.addStock(qty);
        }
    }
}

void InventoryManager::showStock() const {
    std::cout << "Inventory:\n";
    for (const auto& p : products) {
        std::cout << "  " << p.getCode() << " - " << p.getName();
        if (!p.getCode().empty() && toupper(p.getCode()[0]) == 'E')
            std::cout << " (Emergency Item)";
        std::cout << " (Rs." << p.getPrice() << ") Stock: " << p.getStock() << "\n";
    }
}

int InventoryManager::getStock(const std::string& code) const {
    for (const auto& p : products)
        if (p.getCode() == code) return p.getStock();
    return -1;
}

std::vector<Product> InventoryManager::getEmergencyItems() const {
    std::vector<Product> emergencyItems;
    for (const auto& p : products) {
        if (!p.getCode().empty() && toupper(p.getCode()[0]) == 'E') {
            emergencyItems.push_back(p);
        }
    }
    return emergencyItems;
}