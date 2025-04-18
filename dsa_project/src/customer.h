#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <cart.h>
using namespace std;


class Customer{
private:
    string name, password, userID;
    int age;

    vector<CartItem> cart;

public:
    Customer();
    void signup();
    bool login();
    void showMenu();

    void browseSections();            // Fruit / Stationery / etc.
    void addToCart(const string& section);
    void viewCart();
    void modifyCart();
    void checkout();

    void searchAndAddToCart();

    string getUserID() const;
};

void customerMainMenu();       //defined in customer.cpp


#endif
