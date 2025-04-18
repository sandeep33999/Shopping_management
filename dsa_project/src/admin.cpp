#include <iostream>
#include <string>
#include<limits>
#include "admin.h"
#include "inventory.h"
#include "discount.h"
#include "generate_qr.h"
#include "utils.h"
#include "cart.h"
#include "delivery_graph.h"

using namespace std;

void addgraph();


void adminMenu(){

    system("clear");

    int choice;

    while (true){
        cout<< "\n========= 🧑‍💼 Admin PANEL =========\n";
        cout << "1. Manage Fruits\n";
        cout<< "2. Manage Stationery\n";
        cout<< "3. Manage Snacks\n";
        cout << "4. Manage Clothes\n";
        cout << "5. Manage Shop Items\n";
        cout<< "6. Manage More Items\n";

        cout << "7. Manage Discount Coupons\n";
        cout<< "8. View Purchase History\n";
        cout<< "9. Manage UPI IDs\n";
        cout<< "10. View Top Selling Items\n";
        cout<< "11. Add Delivery Routes\n";

        cout << "0. Go to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if(cin.fail()){
            system("clear");
            cout << "❌ Invalid input. Please enter a string: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice >= 1 && choice <= 6) {
            manageSection(choice);  // Implemented in inventory.cpp
        }
        else if (choice == 7) {
            discountAdminMenu(); // Implemented in discount.cpp
        }
        else if (choice == 8) {
            viewPurchaseHistory();  // Implemented in utils.cpp
        }
        else if(choice ==9){
            adminUPIManager(); // Implemented in generate_qr.cpp
        }
        else if(choice ==10){
            Cart c;  // This ensures loadSales() is called once
            Cart::showTopSellingItems();  // Show top 5 selling products
        }
        else if(choice == 11) {
            addgraph();
        }
        
        else if (choice == 0) {
            break;
        } else {
            cout << "⚠️ Invalid choice! Try again.\n";
        }
    }
}


// <----------------- add graph -------------------->
void addgraph(){

    DeliveryGraph graph;
    graph.loadGraph("data/routes.dat");
    
    int opt;
    cout << "\n1. View Routes\n2. Add Route\nChoice: ";
    cin >> opt;

    // if(opt==1)
    if(cin.fail()){
        cout << "❌ Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // continue;
        addgraph();
    }

    if(opt==1){
        graph.displayGraph();
    }

    else if(opt ==2){
        
        string from, to;
        int distance;

        cout << "Enter source: ";
        cin >> from;
        cout << "Enter destination: ";
        cin >> to;
        cout << "Enter distance: ";
        cin >> distance;
        if(cin.fail()){
            cout << "❌ Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // continue;
            addgraph();
        }

        graph.addEdge(from, to, distance);
        graph.saveGraph("data/routes.dat");
        cout << "✅ Route added and saved.\n";
    }
}

//<----------------- admin login -------------------->
bool adminLogin(){


    string username, password;
    cout << "\n🛡️ Admin Login\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    return username == "sandeep" && password == "1234";
    
}
