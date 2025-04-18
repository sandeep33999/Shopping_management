#include<iostream>
#include<string>
#include<limits>
#include "admin.h"
#include "customer.h"
#include "cart.h"
#include "inventory.h"


using namespace std;

void showMainMenu();
bool adminLogin();




int main(){

    int choice;
    
    Cart::loadSales();
    initializeAllSections();  // in inventry.cpp

    while(true){

        showMainMenu();
        cout<<"Enter your choice: ";
        cin>>choice;

        if(cin.fail()){
            system("clear");
            cout<<"❌ Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch(choice){
            case 1:{
                if(adminLogin()){            //<-----------------in admin.cpp
                    adminMenu(); // Defined in admin.cpp
                }
                else{
                    cout << "❌ Invalid credentials! Try again.\n";
                }
                break;
            }
            case 2:{
                customerMainMenu();                    //<-----------------in customer.cpp
                break;
            }
            case 3:{

                cout<<"\n<-------------Thank you for visiting!----------------------------->\n";
                return 0;
            }
            default:
                cout<< "⚠️ Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

//
void showMainMenu(){
    cout << "\n========== 🛒 Welcome to SARC Shop ==========\n";
    cout << "1. Login as Admin\n";
    cout << "2. Customer Login/Signup\n";
    cout << "3. Exit\n";
    cout << "============================================\n";
}