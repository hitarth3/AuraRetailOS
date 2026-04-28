#ifndef KIOSKCOMPONENTFACTORY_H
#define KIOSKCOMPONENTFACTORY_H

#include "inventory/InventoryManager.h"
#include "payment/PaymentProcessor.h"
#include "hardware/HardwareSimulator.h"
#include "payment/PricingStrategy.h"

// Abstract Factory
class KioskComponentFactory {
public:
    virtual ~KioskComponentFactory() {}
    virtual InventoryManager* createInventory() = 0;
    virtual PaymentProcessor* createPayment() = 0;
    virtual HardwareSimulator* createHardware() = 0;
};

// Concrete Factory for Hospital
class HospitalComponentFactory : public KioskComponentFactory {
public:
    InventoryManager* createInventory() override {
        InventoryManager* inv = new InventoryManager();
        inv->addProduct(Product("P006", "Ibuprofen", 30.00, 18));
        inv->addProduct(Product("P007", "Cough Syrup", 95.00, 10));
        inv->addProduct(Product("P008", "Hand Sanitizer", 50.00, 25));
        inv->addProduct(Product("E004", "Oxygen Mask", 180.00, 6));
        inv->addProduct(Product("E005", "Defibrillator Pads", 2500.00, 3));
        inv->addProduct(Product("FAIL", "Defective Item (Test)", 1.00, 10)); // For testing rollback
        return inv;
    }
    PaymentProcessor* createPayment() override {
        PaymentProcessor* pay = new PaymentProcessor();
        pay->setStrategy(new StandardPricing());
        return pay;
    }
    HardwareSimulator* createHardware() override {
        return new HardwareSimulator();
    }
};

// Concrete Factory for Metro
class MetroComponentFactory : public KioskComponentFactory {
public:
    InventoryManager* createInventory() override {
        InventoryManager* inv = new InventoryManager();
        inv->addProduct(Product("M001", "Bottled Water", 20.00, 50));
        inv->addProduct(Product("M002", "Granola Bar", 40.00, 30));
        inv->addProduct(Product("M003", "Phone Charger", 499.00, 10));
        inv->addProduct(Product("M004", "Metro Card (Preloaded)", 200.00, 20));
        inv->addProduct(Product("FAIL", "Defective Item (Test)", 1.00, 10));
        return inv;
    }
    PaymentProcessor* createPayment() override {
        PaymentProcessor* pay = new PaymentProcessor();
        pay->setStrategy(new StandardPricing());
        return pay;
    }
    HardwareSimulator* createHardware() override {
        return new HardwareSimulator();
    }
};

// Concrete Factory for University
class UniversityComponentFactory : public KioskComponentFactory {
public:
    InventoryManager* createInventory() override {
        InventoryManager* inv = new InventoryManager();
        inv->addProduct(Product("U001", "Wireless Earbuds", 1999.00, 5));
        inv->addProduct(Product("U002", "Power Bank", 1200.00, 8));
        inv->addProduct(Product("U003", "USB-C Cable", 299.00, 15));
        inv->addProduct(Product("U004", "Notebook", 80.00, 40));
        inv->addProduct(Product("FAIL", "Defective Item (Test)", 1.00, 10));
        return inv;
    }
    PaymentProcessor* createPayment() override {
        PaymentProcessor* pay = new PaymentProcessor();
        pay->setStrategy(new StandardPricing());
        return pay;
    }
    HardwareSimulator* createHardware() override {
        return new HardwareSimulator();
    }
};

// Concrete Factory for Disaster Zone
class DisasterZoneComponentFactory : public KioskComponentFactory {
public:
    InventoryManager* createInventory() override {
        InventoryManager* inv = new InventoryManager();
        inv->addProduct(Product("E001", "Emergency Blanket", 100.00, 100));
        inv->addProduct(Product("E002", "First Aid Kit", 500.00, 20));
        inv->addProduct(Product("E003", "Canned Food Pack", 150.00, 50));
        inv->addProduct(Product("E004", "Clean Water (5L)", 50.00, 80));
        inv->addProduct(Product("FAIL", "Defective Item (Test)", 1.00, 10));
        return inv;
    }
    PaymentProcessor* createPayment() override {
        PaymentProcessor* pay = new PaymentProcessor();
        pay->setStrategy(new EmergencyPricing());
        return pay;
    }
    HardwareSimulator* createHardware() override {
        return new HardwareSimulator();
    }
};

#endif
