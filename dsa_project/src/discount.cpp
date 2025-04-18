#include "discount.h"
#include <iostream>
#include <fstream>
#include<limits>
#include <iomanip>
using namespace std;


//DiscountManager class implementation
DiscountManager::DiscountManager(){

    loadDiscounts();
}


//Load discounts from file
void DiscountManager::addDiscountCode(const string& code, int percentage){

    discounts[code] = percentage;
    saveDiscounts();
    cout<< "✅ Coupon added: "<<code<<" - "<<percentage<< "% off\n";


}


// Add a new discount code
int DiscountManager::getDiscount(const string& code){


    if (discounts.count(code))
        return discounts[code];
    return 0;

}


// get discount percentage for a code
void DiscountManager::loadDiscounts(){

    discounts.clear();
    ifstream in(filename);
    string code;
    int percent;
    while (in >> code >> percent)
        discounts[code] = percent;
    in.close();

}


//load discounts from file
void DiscountManager::saveDiscounts(){


    ofstream out(filename);
    for (auto& [code, percent] : discounts)
        out << code << " " << percent << endl;
    out.close();

}

//Save discounts to file
void DiscountManager::displayAllDiscounts(){


    cout << "\n🎟️ Available Coupons:\n";
    for (auto& [code, percent] : discounts)
        cout << "🔸 " << setw(10) << code << " : " << percent << "% off\n";
}



// Display all discount codes
// Admin menu for managing discount codes
void discountAdminMenu(){

    DiscountManager manager;
    int choice;
    string code;
    float percent;

    while(true){

        cout<< "\n==== Discount Code Admin ====\n";
        cout<< "1. Add Coupon Code\n2. View All Coupons\n3. Back\n";
        cout<< "Choose: ";
        cin>> choice;

        if(cin.fail()){
            system("clear");
            cout << "❌ Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;


        }

        if(choice==1){


            cout<< "Enter coupon code (no spaces): ";
            cin>>code;

            if(cin.fail()){
                system("clear");
                cout << "❌ Invalid input. Please enter a string: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            cout<<"Enter discount %: ";
            cin>>percent;

            if(cin.fail()){


                system("clear");
                cout << "❌ Invalid input. Please enter a number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if(percent>=1&&percent<= 90)
                manager.addDiscountCode(code,percent);
            else{

                system("clear");
                cout << "❌ Invalid discount percentage.\n";
            }

        }

        else if(choice==2){
            manager.displayAllDiscounts();
        } else if(choice==3){
            break;
        }else{

            cout << "Invalid input!\n";

        }

    }

}
