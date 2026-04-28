#include "core/KioskFactory.h"
#include "core/KioskComponentFactory.h"
#include "core/PersistenceManager.h"

Kiosk* KioskFactory::createKiosk(KioskType type, const std::string& id) {
    std::string location;
    KioskComponentFactory* componentFactory = nullptr;
    
    switch (type) {
        case KioskType::HOSPITAL:
            location = "City Hospital";
            componentFactory = new HospitalComponentFactory();
            break;
        case KioskType::METRO:
            location = "Central Metro Station";
            componentFactory = new MetroComponentFactory();
            break;
        case KioskType::UNIVERSITY:
            location = "University Campus";
            componentFactory = new UniversityComponentFactory();
            break;
        case KioskType::DISASTER_ZONE:
            location = "Disaster Zone Alpha";
            componentFactory = new DisasterZoneComponentFactory();
            break;
    }
    
    Kiosk* kiosk = new Kiosk(id, location);
    InventoryManager* inv = new InventoryManager();
    
    // Try to load from per-kiosk CSV first
    if (!PersistenceManager::loadInventory(inv, id)) {
        // If no CSV exists, populate from factory defaults and save it
        InventoryManager* defaultInv = componentFactory->createInventory();
        for (const auto& p : defaultInv->getProducts()) {
            inv->addProduct(p);
        }
        delete defaultInv;
        PersistenceManager::saveInventory(inv, id);
        std::cout << "[Factory] Created new inventory file for " << id << "\n";
    } else {
        std::cout << "[Factory] Loaded existing inventory from inventory_" << id << ".csv\n";
    }
    
    kiosk->setInventory(inv);
    kiosk->setPayment(componentFactory->createPayment());
    kiosk->setHardware(componentFactory->createHardware());
    
    delete componentFactory;
    return kiosk;
}
