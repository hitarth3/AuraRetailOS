#ifndef PERSISTENCEMANAGER_H
#define PERSISTENCEMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "inventory/Product.h"
#include "inventory/InventoryManager.h"

class PersistenceManager {
public:
    static void saveInventory(const InventoryManager* inv, const std::string& kioskId) {
        std::string filename = "inventory_" + kioskId + ".csv";
        std::ofstream file(filename);
        if (!file.is_open()) return;
        
        file << "Code,Name,Price,Stock\n";
        for (const auto& p : inv->getProducts()) {
            file << p.getCode() << "," << p.getName() << "," << p.getPrice() << "," << p.getStock() << "\n";
        }
        file.close();
    }

    static bool loadInventory(InventoryManager* inv, const std::string& kioskId) {
        std::string filename = "inventory_" + kioskId + ".csv";
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        std::string line;
        std::getline(file, line); // Skip header
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string code, name, priceStr, stockStr;
            std::getline(ss, code, ',');
            std::getline(ss, name, ',');
            std::getline(ss, priceStr, ',');
            std::getline(ss, stockStr, ',');
            
            if (!code.empty()) {
                inv->addProduct(Product(code, name, std::stod(priceStr), std::stoi(stockStr)));
            }
        }
        file.close();
        return true;
    }

    static void logTransaction(const std::string& type, const std::string& message) {
        std::ofstream file("transactions.csv", std::ios::app);
        if (!file.is_open()) return;
        
        file << type << "," << message << "\n";
        file.close();
    }

    static void saveConfig(const std::string& id, const std::string& loc) {
        std::ofstream file("config.csv");
        if (!file.is_open()) return;
        
        file << "ID,Location\n";
        file << id << "," << loc << "\n";
        file.close();
    }
};

#endif
