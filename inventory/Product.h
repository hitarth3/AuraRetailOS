#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>


class Product {
private:
    std::string code, name;
    double price;
    int stock;
public:
    Product(const std::string& c, const std::string& n, double p, int s)
        : code(c), name(n), price(p), stock(s) {}
    std::string getCode() const { return code; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }
    void reduceStock(int qty) { stock -= qty; }
    void addStock(int qty) { stock += qty; }
};
#endif
