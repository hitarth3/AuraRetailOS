# 🏪 Aura Retail OS — Adaptive Autonomous Kiosk System

> A modular, pattern-driven smart kiosk operating system for the smart city of **Zephyrus**, built with C++11. Designed to power autonomous retail kiosks across hospitals, metro stations, universities, and disaster zones — each with environment-specific inventory, dynamic pricing, and resilient failure handling.

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Team Members & Contributions](#team-members)
- [Design Patterns Implemented](#-design-patterns-implemented)
- [Project Structure](#-project-structure)
- [Features](#-features)
- [Build & Run](#-build--run)
- [Usage Guide](#-usage-guide)
- [Data Persistence](#-data-persistence)
- [Environment Profiles](#-environment-profiles)

---

## 🌐 Overview

Aura Retail OS is an object-oriented C++ application that simulates an intelligent retail kiosk ecosystem for a smart city. The system demonstrates **10 Gang-of-Four (GoF) design patterns** across four modular subsystems — **Core**, **Inventory**, **Hardware**, and **Payment** — to deliver a maintainable, extensible, and enterprise-ready architecture.

### Key Highlights

- **Multi-environment kiosks** — Hospital, Metro, University, and Disaster Zone profiles
- **Dynamic pricing engine** — Standard, Discount (20% off), and Emergency (90% off) strategies
- **Transactional integrity** — Memento-based rollback on failed purchases
- **Failure escalation** — Chain of Responsibility from auto-retry → recalibration → technician alert
- **Event-driven communication** — Decoupled subsystems via a publish-subscribe EventBus
- **Persistent state** — CSV-backed inventory, configuration, and transaction logs

---

## <h2 id="team-members">🧑‍🤝‍🧑 Team Members & Contributions

| Member | Subsystem | Key Patterns Implemented |
|---|---|---|
| **Hitarth Shah** | Kiosk Core & Central Registry | Singleton, State, Facade, Abstract Factory, Observer (EventBus) |
| **Mahi Kansara** | Inventory System | Memento, Command (Restock), Observer |
| **Nirmal Patel** | Hardware Abstraction Layer | Chain of Responsibility |
| **Jay Trivedi** | Payment System | Strategy, Command (Purchase/Refund) |

---

## 🧩 Design Patterns Implemented

### Creational Patterns

| # | Pattern | Class(es) | Purpose |
|---|---------|-----------|---------|
| 1 | **Singleton** | `CentralRegistry`, `EventBus` | Single shared instance for kiosk registry and event bus |
| 2 | **Abstract Factory** | `KioskComponentFactory` → `HospitalComponentFactory`, `MetroComponentFactory`, `UniversityComponentFactory`, `DisasterZoneComponentFactory` | Creates environment-specific inventory, payment, and hardware components |

### Structural Patterns

| # | Pattern | Class(es) | Purpose |
|---|---------|-----------|---------|
| 3 | **Facade** | `KioskInterface` | Simplifies complex kiosk interactions (mode switching, purchasing, pricing) behind a unified API |

### Behavioral Patterns

| # | Pattern | Class(es) | Purpose |
|---|---------|-----------|---------|
| 4 | **State** | `KioskState` → `ActiveState`, `MaintenanceState`, `EmergencyState` | Kiosk behavior changes dynamically based on operational mode |
| 5 | **Strategy** | `PricingStrategy` → `StandardPricing`, `DiscountPricing`, `EmergencyPricing` | Interchangeable pricing algorithms at runtime |
| 6 | **Command** | `Command` → `PurchaseItemCommand`, `RefundCommand`, `RestockCommand` | Encapsulates transactions as undoable objects |
| 7 | **Memento** | `InventoryMemento` (inside `InventoryManager`) | Saves and restores inventory state for transaction rollback |
| 8 | **Observer** | `Observer` interface + `EventBus` | Publish-subscribe event system for decoupled inter-subsystem communication |
| 9 | **Chain of Responsibility** | `FailureHandler` → `AutomaticRetryHandler`, `HardwareRecalibrationHandler`, `TechnicianAlertHandler` | Escalating failure handling: retry → recalibrate → alert technician |
| 10 | **Factory Method** | `KioskFactory::createKiosk()` | Creates pre-configured kiosk instances by environment type |

---



## 📁 Project Structure

```
AuraRetailOS/
│
├── main.cpp                          # Application entry point & console UI
├── Makefile                          # Automated build configuration
│
├── core/                             # Core kiosk framework
│   ├── CentralRegistry.h / .cpp      # Singleton — global kiosk registry & config
│   ├── Kiosk.h / .cpp                # Core kiosk entity with subsystem composition
│   ├── KioskState.h / .cpp           # State — Active, Maintenance, Emergency modes
│   ├── KioskInterface.h / .cpp       # Facade — simplified API for kiosk operations
│   ├── KioskFactory.h / .cpp         # Factory Method — creates kiosks by environment type
│   ├── KioskComponentFactory.h       # Abstract Factory — environment-specific components
│   ├── Command.h                     # Command interface (execute/undo)
│   ├── EventBus.h / .cpp             # Observer — singleton event publish-subscribe bus
│   └── PersistenceManager.h          # CSV-based state persistence (inventory, config, logs)
│
├── inventory/                        # Inventory management subsystem
│   ├── Product.h                     # Product data model (code, name, price, stock)
│   ├── InventoryManager.h / .cpp     # Stock management with Memento save/restore
│   ├── Observer.h                    # Observer interface for event subscriptions
│   └── RestockCommand.h             # Command — restocking with event publishing
│
├── hardware/                         # Hardware abstraction layer
│   ├── HardwareSimulator.h / .cpp    # Simulated dispenser hardware
│   └── FailureHandler.h             # Chain of Responsibility — failure escalation
│
├── payment/                          # Payment processing subsystem
│   ├── PricingStrategy.h             # Strategy — Standard, Discount, Emergency pricing
│   ├── PaymentProcessor.h / .cpp     # Payment processing with pluggable strategies
│   ├── PurchaseItemCommand.h         # Command — purchase with Memento rollback
│   └── RefundCommand.h              # Command — refund with inventory restoration
│
├── config.csv                        # Persisted kiosk configuration
├── transactions.csv                  # Transaction audit log
├── inventory_K-HOSP-001.csv          # Persistent inventory — Hospital kiosk
├── inventory_K-METR-001.csv          # Persistent inventory — Metro kiosk
├── inventory_K-UNIV-001.csv          # Persistent inventory — University kiosk
└── inventory_K-DISZ-001.csv          # Persistent inventory — Disaster Zone kiosk
```

---

## ✅ Features

### Kiosk Operations
- **Interactive console interface** with menu-driven navigation
- **Multi-mode operation** — Active (full service), Maintenance (locked), Emergency (restricted to emergency items)
- **Mode-aware access control** — purchases disabled in Maintenance; only `E`-prefixed items in Emergency

### Pricing Engine
- **Standard Pricing** — full retail price
- **Discount Pricing** — configurable percentage discount (default 20% off)
- **Emergency Pricing** — 90% discount for crisis scenarios
- **Real-time strategy switching** — change pricing at any time during operation

### Inventory Management
- **20 products** — 10 regular items (`P`-codes) and 10 emergency items (`E`-codes)
- **Real-time stock validation** — prevents overselling with immediate quantity checks
- **Emergency item filtering** — automatic categorization based on item code prefix
- **Memento-based rollback** — inventory state is saved before each transaction and restored on failure

### Failure Handling
- **Three-tier escalation chain:**
  1. `AutomaticRetryHandler` — resolves minor issues automatically
  2. `HardwareRecalibrationHandler` — recalibrates hardware for moderate failures
  3. `TechnicianAlertHandler` — issues critical alerts for unrecoverable failures

### Persistence
- **CSV-backed inventory** — per-kiosk inventory files survive restarts
- **Transaction logging** — all purchases and refunds are appended to `transactions.csv`
- **Configuration persistence** — kiosk ID and location saved to `config.csv`

---

## 🛠 Build & Run

### Prerequisites

- C++ compiler with **C++11** support (`g++`, `clang++`, or MSVC)
- `make` (optional, for Makefile-based build)
- Terminal / Command Prompt

### Option 1: Using Make (Recommended)

```bash
make
./aura_demo
```

To clean build artifacts:

```bash
make clean
```

### Option 2: Manual Compilation

#### macOS / Linux

```bash
g++ -std=c++11 -I. core/*.cpp inventory/*.cpp hardware/*.cpp payment/*.cpp main.cpp -o aura_demo
./aura_demo
```

#### Windows (MinGW / g++)

```bash
g++ -std=c++11 -I. core/*.cpp inventory/*.cpp hardware/*.cpp payment/*.cpp main.cpp -o aura_demo.exe
.\aura_demo.exe
```



---

## 🎮 Usage Guide

Upon launch, you are presented with the main menu:

```
====================================
   AURA RETAIL OS - HOSPITAL KIOSK
====================================
1. Show Kiosk Status
2. Purchase Item
3. Change Kiosk Mode
4. Change Pricing Strategy
5. Show Inventory
0. Exit
====================================
```

| Option | Description |
|--------|-------------|
| **1 — Show Kiosk Status** | Displays kiosk ID, location, current mode, and active pricing strategy |
| **2 — Purchase Item** | Browse available items, enter item code and quantity, pay with cash |
| **3 — Change Kiosk Mode** | Switch between Active, Maintenance, and Emergency modes |
| **4 — Change Pricing Strategy** | Switch between Standard, Discount (20% off), and Emergency (90% off) |
| **5 — Show Inventory** | View all products with codes, names, prices, and current stock |
| **0 — Exit** | Gracefully terminate the application |

### Sample Purchase Flow

1. Select option **5** to view available items
2. Select option **2** to initiate a purchase
3. Enter the item code (e.g., `P006` for Ibuprofen)
4. Enter the quantity
5. The system calculates the total based on the active pricing strategy
6. Enter the cash amount — change is returned automatically

---

## 💾 Data Persistence

| File | Format | Description |
|------|--------|-------------|
| `config.csv` | `ID,Location` | Stores kiosk identity and deployment location |
| `transactions.csv` | `Type,Message` | Append-only audit log of all purchases, refunds, and restocks |
| `inventory_<KioskID>.csv` | `Code,Name,Price,Stock` | Per-kiosk inventory snapshot for state recovery |

---

## 🌍 Environment Profiles

The **Abstract Factory** pattern enables seamless creation of environment-specific kiosk configurations:

| Environment | Kiosk ID | Default Pricing | Sample Products |
|-------------|----------|-----------------|-----------------|
| **Hospital** | `K-HOSP-001` | Standard | Ibuprofen, Oxygen Mask, Defibrillator Pads |
| **Metro Station** | `K-METR-001` | Standard | Bottled Water, Granola Bar, Metro Card |
| **University** | `K-UNIV-001` | Standard | Wireless Earbuds, Power Bank, USB-C Cable |
| **Disaster Zone** | `K-DISZ-001` | Emergency (90% off) | Emergency Blanket, First Aid Kit, Clean Water |

Each factory (`HospitalComponentFactory`, `MetroComponentFactory`, etc.) produces a fully configured `InventoryManager`, `PaymentProcessor`, and `HardwareSimulator` tailored to its deployment context.

---


