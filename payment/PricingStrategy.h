#ifndef PRICINGSTRATEGY_H
#define PRICINGSTRATEGY_H

#include <iostream>
#include <string>

class PricingStrategy {
public:
    virtual ~PricingStrategy() {}
    virtual double calculatePrice(double basePrice) const = 0;
    virtual void displayMessage() const {}
    virtual std::string getName() const = 0;   // new method
};

class StandardPricing : public PricingStrategy {
public:
    double calculatePrice(double basePrice) const override { return basePrice; }
    std::string getName() const override { return "Standard"; }
};

class DiscountPricing : public PricingStrategy {
private:
    double discountRate;
public:
    DiscountPricing(double rate) : discountRate(rate) {}
    double calculatePrice(double basePrice) const override {
        return basePrice * (1.0 - discountRate);
    }
    void displayMessage() const override {
        std::cout << "   [Discount] " << (discountRate * 100) << "% off applied!\n";
    }
    std::string getName() const override { return "Discount (" + std::to_string(int(discountRate*100)) + "% off)"; }
};

class EmergencyPricing : public PricingStrategy {
public:
    double calculatePrice(double basePrice) const override {
        return basePrice * 0.10;   // 90% off
    }
    void displayMessage() const override {
        std::cout << "   [Emergency] 90% discount applied!\n";
    }
    std::string getName() const override { return "Emergency (90% off)"; }
};

// Additional pricing strategies can be added here
#endif