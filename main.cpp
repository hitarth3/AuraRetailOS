#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include "core/CentralRegistry.h"
#include "core/Kiosk.h"
#include "core/KioskInterface.h"
#include "core/KioskFactory.h"
#include "payment/PurchaseItemCommand.h"
#include "core/EventBus.h"
#include "hardware/FailureHandler.h"
#include "core/PersistenceManager.h"
#include "inventory/InventoryManager.h"
#include "hardware/HardwareSimulator.h"
#include "payment/PaymentProcessor.h"

using namespace std;

// ANSI Color Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// Concrete Observer for logging & persistence
class SystemLogger : public Observer {
public:
    void onEvent(const string& eventType, const string& message) override {
        cout << BLUE << "[SystemLogger] [" << eventType << "] " << message << RESET << endl;
        PersistenceManager::logTransaction(eventType, message);
    }
};

void clearScreen() {
    for (int i = 0; i < 2; ++i) cout << "\n";
}

void pressEnterToContinue() {
    cout << "\n" << CYAN << "Press Enter to continue..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayHeader() {
    cout << MAGENTA << BOLD << "================================================\n";
    cout << "          A U R A   R E T A I L   O S\n";
    cout << "     The Future of Smart City Infrastructure\n";
    cout << "================================================\n" << RESET;
}

void displayMenu(const string& location) {
    displayHeader();
    cout << CYAN << " Location: " << RESET << location << "\n";
    cout << CYAN << " Status:   " << RESET << CentralRegistry::getInstance()->getStatus() << "\n";
    cout << MAGENTA << "------------------------------------------------\n" << RESET;
    cout << " " << YELLOW << "1." << RESET << " Show Kiosk Status\n";
    cout << " " << YELLOW << "2." << RESET << " Purchase Item (Command Pattern)\n";
    cout << " " << YELLOW << "3." << RESET << " Refund Transaction (Command Pattern)\n";
    cout << " " << YELLOW << "4." << RESET << " Restock Inventory (Command Pattern)\n";
    cout << " " << YELLOW << "5." << RESET << " Run System Diagnostics\n";
    cout << " " << YELLOW << "6." << RESET << " Change Kiosk Mode (Observer)\n";
    cout << " " << YELLOW << "7." << RESET << " Change Pricing Strategy (Strategy)\n";
    cout << " " << YELLOW << "8." << RESET << " Show Inventory\n";
    cout << " " << YELLOW << "9." << RESET << " Simulate Hardware Failure\n";
    cout << " " << YELLOW << "0." << RESET << " Exit System\n";
    cout << MAGENTA << "------------------------------------------------\n" << RESET;
    cout << BOLD << " Choice > " << RESET;
}

int main() {
    clearScreen();
    displayHeader();
    cout << "\nInitializing Aura Retail OS subsystems...\n";
    
    EventBus* bus = EventBus::getInstance();
    SystemLogger* logger = new SystemLogger();
    bus->subscribe(logger);
    
    FailureHandler* failureChain = new AutomaticRetryHandler();
    HardwareRecalibrationHandler* recalHandler = new HardwareRecalibrationHandler();
    TechnicianAlertHandler* techHandler = new TechnicianAlertHandler();
    failureChain->setNext(recalHandler);
    recalHandler->setNext(techHandler);
    
    cout << "\n" << BOLD << "Select Kiosk Environment (Abstract Factory):" << RESET << "\n";
    cout << YELLOW << " [1]" << RESET << " Hospital\n";
    cout << YELLOW << " [2]" << RESET << " Metro Station\n";
    cout << YELLOW << " [3]" << RESET << " University Campus\n";
    cout << YELLOW << " [4]" << RESET << " Disaster Zone\n";
    cout << BOLD << " Environment > " << RESET;
    
    int envChoice;
    if (!(cin >> envChoice)) envChoice = 1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    KioskType type;
    switch (envChoice) {
        case 1: type = KioskType::HOSPITAL; break;
        case 2: type = KioskType::METRO; break;
        case 3: type = KioskType::UNIVERSITY; break;
        case 4: type = KioskType::DISASTER_ZONE; break;
        default: type = KioskType::HOSPITAL; break;
    }
    
    CentralRegistry* reg = CentralRegistry::getInstance();
    string kioskId;
    switch (envChoice) {
        case 1: kioskId = "K-HOSP-001"; break;
        case 2: kioskId = "K-METR-001"; break;
        case 3: kioskId = "K-UNIV-001"; break;
        case 4: kioskId = "K-DISZ-001"; break;
        default: kioskId = "K-AURA-001"; break;
    }
    
    Kiosk* kiosk = KioskFactory::createKiosk(type, kioskId);
    reg->registerKiosk(kiosk->getId(), kiosk);
    reg->setStatus("Online");
    reg->setConfig("Env", to_string(envChoice));
    
    PersistenceManager::saveConfig(kiosk->getId(), kiosk->getLocation());
    PersistenceManager::saveInventory(kiosk->getInventory(), kiosk->getId());
    
    InventoryManager* inv = kiosk->getInventory();
    PaymentProcessor* pay = kiosk->getPayment();
    KioskInterface ui(kiosk);
    
    int choice;
    string itemCode;
    int quantity;
    double cashAmount;
    
    do {
        clearScreen();
        displayMenu(kiosk->getLocation());
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                ui.showStatus();
                pressEnterToContinue();
                break;
                
            case 2: {
                cout << "\n" << BOLD << "--- Purchase Item ---" << RESET << "\n";
                inv->showStock();
                cout << "\n Code: "; getline(cin, itemCode);
                transform(itemCode.begin(), itemCode.end(), itemCode.begin(), ::toupper);
                cout << " Qty:  "; cin >> quantity;
                
                double basePrice = inv->getPrice(itemCode);
                if (basePrice <= 0) {
                    cout << RED << " [Error] Invalid item code.\n" << RESET;
                    pressEnterToContinue();
                    break;
                }
                
                double totalDue = pay->calculateTotal(basePrice, quantity);
                cout << YELLOW << " Total Due: Rs." << totalDue << RESET << " (Strategy: " << pay->getStrategyName() << ")\n";
                cout << " Enter Cash: "; cin >> cashAmount;
                cin.ignore();
                
                if (ui.purchaseItem(itemCode, quantity, cashAmount)) {
                    PersistenceManager::saveInventory(inv, kiosk->getId());
                }
                pressEnterToContinue();
                break;
            }

            case 3:
                cout << "\n" << BOLD << "--- Refund Transaction ---" << RESET << "\n";
                cout << " Item Code: "; getline(cin, itemCode);
                transform(itemCode.begin(), itemCode.end(), itemCode.begin(), ::toupper);
                cout << " Qty:       "; cin >> quantity;
                cin.ignore();
                ui.refundTransaction(itemCode, quantity);
                PersistenceManager::saveInventory(inv, kiosk->getId());
                pressEnterToContinue();
                break;

            case 4:
                cout << "\n" << BOLD << "--- Restock Inventory ---" << RESET << "\n";
                cout << " Item Code: "; getline(cin, itemCode);
                transform(itemCode.begin(), itemCode.end(), itemCode.begin(), ::toupper);
                cout << " Qty:       "; cin >> quantity;
                cin.ignore();
                ui.restockInventory(itemCode, quantity);
                PersistenceManager::saveInventory(inv, kiosk->getId());
                pressEnterToContinue();
                break;

            case 5:
                ui.runDiagnostics();
                pressEnterToContinue();
                break;
                
            case 6:
                cout << "\n" << BOLD << "--- Change Mode ---" << RESET << "\n";
                cout << " [1] Active [2] Power-saving [3] Maintenance [4] Emergency\n Mode > ";
                cin >> choice; cin.ignore();
                if (choice == 1) ui.setMode("active");
                else if (choice == 2) ui.setMode("powersaving");
                else if (choice == 3) ui.setMode("maintenance");
                else if (choice == 4) ui.setMode("emergency");
                pressEnterToContinue();
                break;
                
            case 7:
                cout << "\n" << BOLD << "--- Change Pricing ---" << RESET << "\n";
                cout << " [1] Standard [2] Discount [3] Emergency\n Pricing > ";
                cin >> choice; cin.ignore();
                if (choice == 1) ui.setPricing("standard");
                else if (choice == 2) ui.setPricing("discount");
                else if (choice == 3) ui.setPricing("emergency");
                pressEnterToContinue();
                break;
                
            case 8:
                inv->showStock();
                pressEnterToContinue();
                break;
                
            case 9:
                cout << "\n" << BOLD << "--- Simulate Failure ---" << RESET << "\n";
                cout << " [1] Minor [2] Moderate [3] Critical\n Level > ";
                cin >> choice; cin.ignore();
                if (choice == 1) failureChain->handle(FailureLevel::MINOR, "Dispenser sensor glitch");
                else if (choice == 2) failureChain->handle(FailureLevel::MODERATE, "Dispenser mechanism jammed");
                else if (choice == 3) failureChain->handle(FailureLevel::CRITICAL, "Main motor failure");
                pressEnterToContinue();
                break;
                
            case 0:
                cout << MAGENTA << "\n Shutting down Aura Retail OS...\n" << RESET;
                reg->setStatus("Offline");
                break;
                
            default:
                break;
        }
    } while (choice != 0);
    
    delete failureChain;
    delete logger;
    return 0;
}