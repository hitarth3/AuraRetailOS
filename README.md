# Aura Retail OS – Adaptive Autonomous Kiosk System

A smart kiosk system for the smart city of Zephyrus, featuring dynamic pricing, multiple operational modes, and modular architecture using OOP and Design Patterns.

---

## 🧑‍🤝‍🧑 Team Members & Design Patterns Implemented

| Member | Subsystem | Patterns Implemented (Fully Working) |
|--------|-----------|--------------------------------------|
| **Hitarth Shah** | Kiosk Core & Central Registry | Singleton, State, Facade |
| **Mahi Kansara** | Inventory System | Basic product management |
| **Nirmal Patel** | Hardware Abstraction Layer | Hardware simulation |
| **Jay Trivedi** | Payment System | Strategy (pricing) |

**Note:** The current version is a partial submission demonstrating four core patterns:  
✅ Singleton, ✅ State, ✅ Facade, ✅ Strategy.  
Additional patterns (Abstract Factory, Composite, Chain of Responsibility, Memento, Command, Observer) are stubbed for future expansion.

---

## ✅ Implemented Features

- Interactive console interface (Hospital Kiosk theme)
- Kiosk modes: **Active**, **Maintenance**, **Emergency**
- Dynamic pricing: Standard, 20% Discount, 90% Emergency
- Stock validation with immediate changes
- Emergency mode restricts purchases to emergency items (code starting with `E`)
- Hardware simulation (dispenser)
- Clean, modular code – easy to extend

---

## 🛠 How to Compile and Run

### Prerequisites

- C++ compiler with **C++11** support (g++, clang++, or MSVC)
- Terminal / Command Prompt

## 💻 Compilation & Execution

### Windows (MinGW / g++)

```bash
g++ -std=c++11 -I. core/*.cpp inventory/*.cpp hardware/*.cpp payment/*.cpp main.cpp -o aura_demo.exe
aura_demo.exe
```
### Mac
```bash
g++ -std=c++11 -I. core/*.cpp inventory/*.cpp hardware/*.cpp payment/*.cpp main.cpp -o aura_demo
./aura_demo



