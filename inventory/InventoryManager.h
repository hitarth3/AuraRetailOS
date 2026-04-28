#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <vector>
#include <string>
#include "inventory/Product.h"

// Memento Class
class InventoryMemento {
private:
    std::vector<Product> productsState;
    friend class InventoryManager;
    InventoryMemento(const std::vector<Product>& p) : productsState(p) {}
};

class InventoryManager {
private:
    std::vector<Product> products;
public:
    void addProduct(const Product& p);
    bool hasStock(const std::string& code, int qty) const;
    double getPrice(const std::string& code) const;
    void reduceStock(const std::string& code, int qty);
    void increaseStock(const std::string& code, int qty);
    void showStock() const;
    int getStock(const std::string& code) const;
    std::vector<Product> getEmergencyItems() const;
    
    const std::vector<Product>& getProducts() const { return products; }

    // Memento Methods
    InventoryMemento* save() {
        return new InventoryMemento(products);
    }
    void restore(InventoryMemento* memento) {
        if (memento) {
            products = memento->productsState;
        }
    }
};

#endif