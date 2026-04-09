#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <vector>
#include <string>
#include "inventory/Product.h"

class InventoryManager {
private:
    std::vector<Product> products;
public:
    void addProduct(const Product& p);
    bool hasStock(const std::string& code, int qty) const;
    double getPrice(const std::string& code) const;
    void reduceStock(const std::string& code, int qty);
    void showStock() const;
    int getStock(const std::string& code) const;
    
    // NEW: Return all emergency items (code starts with 'E')
    std::vector<Product> getEmergencyItems() const;
};

#endif