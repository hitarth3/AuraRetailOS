#include "payment/PaymentProcessor.h"
#include <iostream>

PaymentProcessor::PaymentProcessor() : strategy(new StandardPricing()) {}
PaymentProcessor::~PaymentProcessor() { delete strategy; }

void PaymentProcessor::setStrategy(PricingStrategy* s) {
    delete strategy;
    strategy = s;
    strategy->displayMessage();
}

double PaymentProcessor::calculateTotal(double basePrice, int quantity) const {
    return strategy->calculatePrice(basePrice) * quantity;
}

void PaymentProcessor::processPayment(double amount) const {
    std::cout << "   [Payment] Processed ₹" << amount << "\n";
}

void PaymentProcessor::displayStrategyMessage() const {
    strategy->displayMessage();
}

std::string PaymentProcessor::getStrategyName() const {
    return strategy->getName();
}