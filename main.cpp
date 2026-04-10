#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include "core/CentralRegistry.h"
#include "core/Kiosk.h"
#include "core/KioskInterface.h"
#include "inventory/InventoryManager.h"
#include "hardware/HardwareSimulator.h"
#include "payment/PaymentProcessor.h"

using namespace std;

void clearScreen() {
    for (int i = 0; i < 2; ++i) cout << "\n";
}

void pressEnterToContinue() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

void displayMenu() {
    cout << "\n====================================\n";
    cout << "   AURA RETAIL OS - HOSPITAL KIOSK\n";
    cout << "====================================\n";
    cout << "1. Show Kiosk Status\n";
    cout << "2. Purchase Item\n";
    cout << "3. Change Kiosk Mode\n";
    cout << "4. Change Pricing Strategy\n";
    cout << "5. Show Inventory\n";
    cout << "0. Exit\n";
    cout << "====================================\n";
    cout << "Enter your choice: ";
}

// Check if an item code is an emergency item (starts with 'E')
bool isEmergencyItem(const string& code) {
    return !code.empty() && toupper(code[0]) == 'E';
}

void showEmergencyItems(InventoryManager* inv) {
    cout << "\n--- Emergency Items Available ---\n";
    vector<Product> emergencyItems = inv->getEmergencyItems();
    if (emergencyItems.empty()) {
        cout << "  No emergency items in stock.\n";
        return;
    }
    for (const auto& item : emergencyItems) {
        cout << "  " << item.getCode() << " - " << item.getName()
             << " (Emergency Item) - Stock: " << item.getStock()
             << " - Price: Rs." << item.getPrice() << "\n";
    }
}

int main() {
    cout << "===== Aura Retail OS - Hospital Kiosk Demo =====\n\n";
    
    CentralRegistry* reg = CentralRegistry::getInstance();
    string location = "City Hospital";
    
    Kiosk* kiosk1 = new Kiosk("K001", location);
    reg->registerKiosk("K001", kiosk1);
    
    InventoryManager* inv = new InventoryManager();
    
    // Regular Products (P) - Prices in INR (Rs.)
    inv->addProduct(Product("P006", "Ibuprofen", 30.00, 18));
    inv->addProduct(Product("P007", "Cough Syrup", 95.00, 10));
    inv->addProduct(Product("P008", "Hand Sanitizer", 50.00, 25));
    inv->addProduct(Product("P009", "Face Mask Pack", 120.00, 20));
    inv->addProduct(Product("P010", "Thermometer", 250.00, 6));
    inv->addProduct(Product("P011", "Glucose Powder", 110.00, 14));
    inv->addProduct(Product("P012", "ORS Packets", 20.00, 30));
    inv->addProduct(Product("P013", "Vitamin Tablets", 150.00, 16));
    inv->addProduct(Product("P014", "Pain Relief Spray", 180.00, 9));
    inv->addProduct(Product("P015", "Cotton Roll", 40.00, 22));

    // Emergency Items (E) - Prices in INR (Rs.)
    inv->addProduct(Product("E004", "Oxygen Mask", 180.00, 6));
    inv->addProduct(Product("E005", "Defibrillator Pads", 2500.00, 3));
    inv->addProduct(Product("E006", "IV Drip Set", 120.00, 8));
    inv->addProduct(Product("E007", "Burn Kit", 350.00, 5));
    inv->addProduct(Product("E008", "Splint Kit", 450.00, 4));
    inv->addProduct(Product("E009", "Emergency Scissors", 150.00, 10));
    inv->addProduct(Product("E010", "CPR Mask", 250.00, 7));
    inv->addProduct(Product("E011", "Stretcher Straps", 600.00, 3));
    inv->addProduct(Product("E012", "Trauma Dressing", 200.00, 6));
    inv->addProduct(Product("E013", "Saline Injection", 80.00, 9));
    
    kiosk1->setInventory(inv);
    
    HardwareSimulator* hw = new HardwareSimulator();
    kiosk1->setHardware(hw);
    PaymentProcessor* pay = new PaymentProcessor();
    kiosk1->setPayment(pay);
    
    KioskInterface ui(kiosk1);
    
    int choice;
    string itemCode;
    int quantity;
    double cash;
    
    do {
        clearScreen();
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                cout << "\n--- Kiosk Status ---\n";
                cout << "ID: " << kiosk1->getId() << "\n";
                cout << "Location: " << kiosk1->getLocation() << "\n";
                cout << "Mode: " << kiosk1->getState()->getName() << "\n";
                if (pay) {
                    cout << "Pricing Strategy: " << pay->getStrategyName() << "\n";
                }
                pressEnterToContinue();
                break;
                
            case 2: {
                string currentMode = kiosk1->getState()->getName();
                
                if (currentMode == "Maintenance") {
                    cout << "\n[ERROR] Purchases are disabled in Maintenance mode.\n";
                    pressEnterToContinue();
                    break;
                }
                
                cout << "\n--- Purchase Item ---\n";
                if (pay) {
                    cout << "Pricing Strategy: " << pay->getStrategyName() << "\n";
                }
                
                if (currentMode == "Emergency") {
                    showEmergencyItems(inv);
                    cout << "\nOnly emergency items (codes starting with 'E') can be purchased.\n";
                } else {
                    inv->showStock();
                }
                
                cout << "\nEnter item code: ";
                getline(cin, itemCode);
                transform(itemCode.begin(), itemCode.end(), itemCode.begin(), ::toupper);
                
                // Emergency mode restriction: must be an emergency item
                if (currentMode == "Emergency" && !isEmergencyItem(itemCode)) {
                    cout << "[ERROR] In Emergency mode, only emergency items allowed.\n";
                    pressEnterToContinue();
                    break;
                }
                
                cout << "Enter quantity: ";
                cin >> quantity;
                if (quantity <= 0) {
                    cout << "[ERROR] Quantity must be positive.\n";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    pressEnterToContinue();
                    break;
                }
                
                if (quantity > 100) {
                    cout << "[ERROR] Quantity too high (max 100).\n";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    pressEnterToContinue();
                    break;
                }
                
                if (!inv->hasStock(itemCode, quantity)) {
                    cout << "[ERROR] Insufficient stock! Available: " 
                         << inv->getStock(itemCode) << "\n";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    pressEnterToContinue();
                    break;
                }
                
                double unitPrice = inv->getPrice(itemCode);
                double total = pay->calculateTotal(unitPrice, quantity);
                
                pay->displayStrategyMessage();
                cout << "   Estimated total: Rs." << total << "\n";
                
                cout << "Enter cash amount (Rs.): ";
                cin >> cash;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if (cash < total) {
                    cout << "[ERROR] Insufficient cash. Need Rs." << total << "\n";
                    pressEnterToContinue();
                    break;
                }
                
                if (hw) hw->dispense(itemCode, quantity);
                pay->processPayment(total);
                inv->reduceStock(itemCode, quantity);
                
                cout << "   [OK] Purchase successful. Change: Rs." << cash - total << "\n";
                pressEnterToContinue();
                break;
            }
                
            case 3:
                cout << "\n--- Change Kiosk Mode ---\n";
                cout << "Current mode: " << kiosk1->getState()->getName() << "\n";
                cout << "1. Active\n2. Maintenance\n3. Emergency\n";
                cout << "Enter choice (1-3): ";
                cin >> choice;
                cin.ignore();
                if (choice == 1) ui.setMode("active");
                else if (choice == 2) ui.setMode("maintenance");
                else if (choice == 3) ui.setMode("emergency");
                else cout << "Invalid choice.\n";
                pressEnterToContinue();
                break;
                
            case 4:
                cout << "\n--- Change Pricing Strategy ---\n";
                cout << "Current: " << pay->getStrategyName() << "\n";
                cout << "1. Standard\n2. Discount (20% off)\n3. Emergency (90% off)\n";
                cout << "Enter choice (1-3): ";
                cin >> choice;
                cin.ignore();
                if (choice == 1) ui.setPricing("standard");
                else if (choice == 2) ui.setPricing("discount");
                else if (choice == 3) ui.setPricing("emergency");
                else cout << "Invalid choice.\n";
                pressEnterToContinue();
                break;
                
            case 5:
                cout << "\n--- Current Inventory ---\n";
                inv->showStock();
                pressEnterToContinue();
                break;
                
            case 0:
                cout << "\nExiting...\n";
                break;
                
            default:
                cout << "Invalid option.\n";
                pressEnterToContinue();
        }
    } while (choice != 0);
    
    cout << "\n===== Simulation Complete =====\n";
    
    delete kiosk1;
    delete inv;
    delete hw;
    delete pay;
    return 0;
}