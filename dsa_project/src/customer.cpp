#include "customer.h"
#include "utils.h"
#include "discount.h"
#include "generate_qr.h"
#include "cart.h"
#include "search_utils.h"
#include "inventory.h"
#include "delivery_graph.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <vector>
#include<limits>
#include <cstdlib>
#include <algorithm>

using namespace std;

Customer::Customer() {}


// test done
//create a new customer account
void Customer::signup(){
    cout << "\n📝 SIGNUP FORM\n";
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter age: ";
    cin >> age;
    cout << "Create password: ";
    cin >> password;

    // Generate userID
    ifstream in("data/last_user_id.txt");
    int id = 1;
    if (in >> id) id++;
    in.close();

    userID = "RD" + to_string(1000 + id).substr(1); // USR001, USR002...
    ofstream out("data/last_user_id.txt");
    out << id;
    out.close();

    // Save to file
    ofstream userFile("data/customers.dat", ios::app);
    userFile<<userID<< " " << name << " " << age << " " << password << "\n";
    userFile.close();

    cout<<"✅ Signup successful! Your user ID is: "<<userID<<endl;
}


// after test cases running good;

// login function for customer
bool Customer::login(){

    cout<<"\n🔐 CUSTOMER LOGIN\n";
    cout<< "Enter user ID: ";
    cin>> userID;

    if(cin.fail()){

        cout << "❌ Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // continue;
        // return;
        login();
    }

    cout<<"Enter password: ";
    cin >> password;

    if(cin.fail()){
        cout << "❌ Invalid input. Please enter a string: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // continue;
        // return;
        login();

    }

    ifstream in("data/customers.dat");
    string uid, uname, pass;
    int uage;

    while (in>>uid>>uname>>uage>>pass){


        if(uid==userID && pass==password){

            name =uname;
            age =uage;
            cout<<"✅ Login successful! Welcome, "<<name << "!\n";

            return true;
        }
    }


    cout << "❌ Invalid credentials!\n";
    return false;
}



//<-------------------Search for items using KMP algorithm--------------->
void Customer::searchAndAddToCart(){

    cout << "🔍 Enter item to search: ";
    string keyword;
    cin >> keyword;

    auto results=searchItems(keyword);  // Uses KMP internally

    if(results.empty()){


        system("clear");
        cout << "❌ No matching items found.\n";
    }
    else{
        cout << "✅ Matches Found's:\n";

            // Header
    cout << left << setw(5) << "No."
    << setw(35) << "Item"
    << setw(10) << "Qty"
    << setw(10) << "Price" << endl;
    cout << string(60, '-') << endl;  // separator line

    for(int i=0;i<results.size();++i){


        string fullName = results[i].name + " (" + results[i].section + ")";
        cout << left << setw(5) << (to_string(i + 1) + ".")
             << setw(35) << fullName
             << setw(10) << results[i].stock
             << "₹" << results[i].price << endl;

    }

        cout << string(60, '-') << endl;  // separator line

        cout << "\nSelect item number to add to cart (0 to cancel): ";
        int choice;
        cin >> choice;

        if(choice>0&&choice <=results.size()){
            ItemInfo selected=results[choice-1];

            int qty;
            cout << "Enter quantity: ";
            cin >> qty;

            if(qty>0&&qty<=selected.stock){

                cart.push_back({selected.name, qty, selected.price});
                cout << "✅ Item added to cart.\n";
            } 
            else{
                cout << "❌ Invalid quantity.\n";
            }

        }
    }

}


// test done
void Customer::showMenu(){


    int choice;

    while(true){
        // system("clear");
        cout<<"\n=================CUSTOMER MENU =================\n";
        cout<<"0. Search item\n";
        cout<<"1. Browse Sections\n";
        cout<<"2. View Cart\n";
        cout<<"3. Modify Cart\n";
        cout<<"4. Checkout\n";
        cout<<"5. Logout\n";
        cout<<"Choose: ";

        cin >> choice;
        if(cin.fail()){

            cout << "❌ Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;

        }

        if(choice==0){
            searchAndAddToCart();  // call this function where ever you want to search option


        }


        else if (choice == 1)
            browseSections();
        else if (choice == 2)
            viewCart();
        else if (choice == 3)
            modifyCart();
        else if (choice == 4)
            checkout();
        else if (choice == 5)
            break;
        else
            cout << "Invalid choice!\n";
    }


}

// test done
void Customer::browseSections(){

    cout << "\nAvailable Sections:\n";
    cout <<"0. Go TO Back\n";
    cout<<"1. Fruits\n";
    cout<<"2. Stationery\n";
    cout<<"3. Snacks\n";
    cout<<"4. Clothes\n";
    cout<<"5. Shop\n";
    cout<<"6. More\n";
    cout<<"99. Search item \n";
    cout << "Choose section: ";

    int choice;
    cin>>choice;

    if(cin.fail()){

        system("clear");
        cout << "❌ Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        browseSections();


    }

    if(choice==99){


        searchAndAddToCart();  // global search
        return;
    }

    switch (choice){


        case 1: addToCart("fruits"); break;
        case 2: addToCart("stationery"); break;
        case 3: addToCart("snacks"); break;
        case 4: addToCart("clothes"); break;
        case 5: addToCart("shop"); break;
        case 6: addToCart("more"); break;
        default: cout << "Invalid!\n";

    }


}

// <--- test done
void Customer::addToCart(const string& section){

    cout<<"\n📦 Items in avilable In "<<section<< " :\n";

    //add
    cout<<left<<setw(5)<<"No."<<setw(15)<<"Item"<<setw(10)<<"Qty"<<"Price\n";
    cout << string(40, '-') <<"\n"; // optional separator
    

    string filename = "data/inventory/"+section+".dat";
    ifstream in(filename);


    if(!in){
        cout << "❌ Section data not found.\n";
        return;
    }

    string item;
    float price;
    int avilable_quantity;
    int index = 1;

    vector<pair<string,float>>items;

    while(in>>item>>price>>avilable_quantity){

        cout<<left<<setw(5)<<index<<setw(15)<<item<<setw(9)<<price<< "₹"<<setw(10)<<avilable_quantity<<endl;
        items.push_back({item, price});
        index++;

    }


    cout<<"99. Search item\n";
    cout<<"Enter item number to add (0 to cancel): ";
    int choice;
    cin >> choice;

    if(cin.fail()){
        system("clear");
        cout << "❌ Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        addToCart(section);


    }

    if(choice==99){

        searchAndAddToCart();  // call this function where ever you want to search option
    }
    else if(choice <= 0 || choice > items.size()) return;

    cout << "Enter quantity: ";
    int qty;
    cin >> qty;

    if(cin.fail()){


        system("clear");
        cout << "❌ Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        addToCart(section);


    }

    CartItem ci;
    ci.name = items[choice-1].first;
    ci.price = items[choice-1].second;
    ci.quantity=qty;
    cart.push_back(ci);

    system("clear");
    cout << "\n ✅ Added to cart: "<<ci.name<<" x" << ci.quantity<<endl;


}


// test done

//<----------------- view cart -------------------->
void Customer::viewCart() {
    cout << "\n🛒 Your Cart:\n";
    float total = 0;
    for (int i = 0; i < cart.size(); ++i) {
        cout << i+1 << ". " << cart[i].name << " x" << cart[i].quantity << " - ₹" 
             << cart[i].price * cart[i].quantity << endl;
        total += cart[i].price * cart[i].quantity;
    }
    cout << "Total: ₹" << total << "\n";
}

// test done
//<----------------- modify cart -------------------->
void Customer::modifyCart(){


    viewCart();
    cout << "Enter item number to modify (0 to cancel): ";
    int idx;
    cin>>idx;
    if(idx<=0||idx>cart.size()) return;

    cout<<"1. Change Quantity\n2. Remove Item\nChoice: ";

    int ch;
    cin>>ch;

    if(ch==1){
        cout << "New quantity: ";
        int qty;
        cin>>qty;
        cart[idx-1].quantity=qty;
        cout<<"✅ Quantity updated.\n";
    }
    else if(ch==2){
        cart.erase(cart.begin()+idx-1);
        cout<<"✅ Item removed.\n";

    }


}



//test done
//<----------------- checkout -------------------->

void Customer::checkout(){



    viewCart();
    float total=0;
    for (auto& item : cart)
        total +=item.price*item.quantity;

    // Apply discount
    DiscountManager dman;
    string code;
    float discount = 0;
    float discountAmount=0;


    cout<<"Enter coupon code (or 0 to skip): ";
    cin>>code;


    if(code!="0"){

        discount = dman.getDiscount(code);  // float

        if(discount>0){
            discountAmount=total*(discount/100.0f);
            cout<<"✅ Discount applied: " << discount << "%\n";
            total -=discountAmount;
        }
        else{
            cout << "❌ Invalid code.\n";

        }

    }

    cout<<"Final Total: ₹" <<total << "\n";

    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream filename;
    filename << "data/bills/" << userID << "_"
             << 1900 + ltm->tm_year << ltm->tm_mon + 1 << ltm->tm_mday << "_"
             << ltm->tm_hour << ltm->tm_min << ".txt";



    ofstream out(filename.str());


    out<<"Customer ID: "<<userID<<"\n";
    out<<"Item\tQty\tPrice\tTotal\n";

    for(auto& item:cart){
        out << item.name << "\t" << item.quantity << "\t" << item.price << "\t"
            << item.quantity * item.price << "\n";
    }


    out<< "Discount: " << discount << "% (-₹" << fixed << setprecision(2) << discountAmount << ")\n";
    out << "Total Paid: ₹" << total << "\n";
    out.close();



    //<------------Save Purchase Summary to purchase_history.dat--------------------->
    ofstream hist("data/purchase_history.dat", ios::app);
    hist << "UserID: " << userID << "\n";

    for(auto& item :cart){
        hist << item.name << " x" << item.quantity<<" = ₹"<<item.price*item.quantity<<"\n";
    }


    hist<<"Discount: "<<discount<<"% (-₹"<<fixed<<setprecision(2)<<discountAmount << ")\n";
    hist<<"Total: ₹"<<total<<"\n";

    hist<<"Timestamp: " << 1900 + ltm->tm_year << "-" << ltm->tm_mon + 1 << "-" << ltm->tm_mday
         << " " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << "\n";
    hist << "--------------------------------------------------------\n";
    hist.close();


    // QR Payment
    string upi = getUPIForAmount(total);
    qrWithTimer(upi, total);

    cout << "✅ Bill generated and saved.\n";
    for (auto& item : cart)
    Cart::updateSales(item.name, item.quantity);


    
    cart.clear();

    string delevry_option;    
    cout<<"You want Home Delivery (Y/n): ";
    cin>>delevry_option;


    if(delevry_option =="Y"|| delevry_option=="y"){
        DeliveryGraph graph;
        graph.loadGraph("data/routes.dat");
        cout<<"Product will deliver from O4\n";
        cout << "\n📦 Available Delivery Locations:\n";
        unordered_map<string, vector<pair<string,int>>> addressMap = graph.getAdjList();
        for (const auto& [node, _] : addressMap){
            if (node != "O4") // Exclude the shop itself
            cout<< " - " << node << "\n";
        }


        string address;

        cout << "\n📍 Enter your delivery location: ";
        cin.ignore();
        getline(cin, address);

        // Trim leading/trailing spaces if needed (optional but safe)
        address.erase(address.begin(),find_if(address.begin(),address.end(),[](unsigned char ch){

            return !isspace(ch);
        }));

        address.erase(find_if(address.rbegin(), address.rend(), [](unsigned char ch) {
            return !isspace(ch);

        }).base(), address.end());

        // Check if address is valid
        if(addressMap.find(address)==addressMap.end()||address=="O4"){

            cout << "❌ Delivery is only available at above mentioned location's.\n";
        }

        else{
            string shopLocation = "O4"; // shop location
            graph.dijkstra(shopLocation, address);
        }

    }

    cout<<"\n----------------------------------------------------------------------------------\n";
    cout << "Thank you for shopping with us!\n";
    cout<<"                               :Regard's SARC Brother's"<<endl;
    cout<<"----------------------------------------------------------------------------------\n";
    return;

}




string Customer::getUserID() const{

    return userID;
}

// test done
void customerMainMenu(){

    system("clear");
    Customer cust;
    int ch;
    
    while(true){

        cout<<"\n------------------------Customer Panel------------------------------\n";
        cout<<"\n1. Signup\n2. Login\n3. Back\n";
        cout<<"Enter Choice: ";
        cin>>ch;


        if(cin.fail()){


            system("clear");
            cout << "❌ Invalid input. Please enter a number: ....";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch(ch)
        {
        case 1:

            cust.signup();
            break;
        case 2:

            if(cust.login()){
                system("clear");
                cust.showMenu();
            }

            break;    
        case 3:

            cout<<"👋 Thank you for visiting! Exiting...\n";
            return;
        default:
        
            system("clear");
            cout << "❌ Invalid choice. Please try again!\n";;
        }
        
    }
}
