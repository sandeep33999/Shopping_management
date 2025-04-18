#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <string>
#include <unordered_map>
using namespace std;

class DiscountManager{

private:
    unordered_map<string, int> discounts;
    const string filename = "data/discounts.dat";

public:

    DiscountManager();
    void addDiscountCode(const string& code, int percentage);
    int getDiscount(const string& code);
    void loadDiscounts();
    void saveDiscounts();
    void displayAllDiscounts();

};


void discountAdminMenu();

#endif
