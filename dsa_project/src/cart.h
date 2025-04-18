#ifndef CART_H
#define CART_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

struct CartItem {
    string name;
    int quantity;
    float price;
};

class Cart {
private:
    vector<CartItem> items;
    static unordered_map<string, int> globalSales;

public:
    Cart();  // constructor to load sales from file

    void addItem(const string& name, int qty, float price);
    void removeItem(const string& name);
    void updateQuantity(const string& name, int newQty);
    void viewCart() const;
    float getTotal() const;
    vector<CartItem> getItems() const;

    static void updateSales(const string& name, int qty);
    static void showTopSellingItems();
    static void loadSales();

private:
    // static void loadSales();
    static void saveSales();
};

#endif
