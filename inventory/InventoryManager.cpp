#include "inventory/InventoryManager.h"
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
    for (auto& p : products)
        if (p.getCode() == code) p.reduceStock(qty);
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