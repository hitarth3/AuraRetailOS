#ifndef PAYMENTPROCESSOR_H
#define PAYMENTPROCESSOR_H

#include "payment/PricingStrategy.h"
#include <string>

class PaymentProcessor {
private:
    PricingStrategy* strategy;
public:
    PaymentProcessor();
    ~PaymentProcessor();
    void setStrategy(PricingStrategy* s);
    double calculateTotal(double basePrice, int quantity) const;
    void processPayment(double amount) const;
    void displayStrategyMessage() const;
    std::string getStrategyName() const;   // new
};

#endif