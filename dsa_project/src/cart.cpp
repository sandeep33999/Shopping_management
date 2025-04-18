#include "cart.h"
#include <fstream>
#include <sstream>
#include <algorithm>

unordered_map<string, int> Cart::globalSales;

Cart::Cart(){

    //<-------Load sales data from file when cart is constructed----->
    loadSales();  // Load from file when cart is constructed
}

void Cart::addItem(const string& name,int qty,float price){
    for(auto& item : items){

        if(item.name==name){
            item.quantity += qty;
            return;
        }

    }

    items.push_back({name, qty, price});
}


//<----------------- remove item from cart -------------------->
void Cart::removeItem(const string& name) {
    items.erase(remove_if(items.begin(), items.end(), [&](const CartItem& item){

        return item.name == name;
    }), items.end());
}


//<----------------- update item quantity -------------------->
void Cart::updateQuantity(const string& name, int newQty){

    for (auto& item : items){


        if (item.name == name){


            item.quantity = newQty;
            return;
        }
    }


}


//<----------------- view cart -------------------->
void Cart::viewCart() const {

    cout << "\n🛒 Cart Contents:\n";
    cout << "Item\tQty\tPrice\tTotal\n";

    for(const auto& item:items){


        cout<<item.name<<"\t"<<item.quantity<<"\t₹"<<item.price
             << "\t₹" << item.price * item.quantity << "\n";

    }


    cout << "----------------------------\n";
    cout << "Total: ₹" << getTotal() << "\n";


}


//<----------------- get total price -------------------->
float Cart::getTotal() const{


    float total = 0;
    for(const auto& item : items)
        total += item.price * item.quantity;
    return total;
}

vector<CartItem> Cart::getItems() const{
    return items;
}

//<----------------- update global sales -------------------->
void Cart::updateSales(const string& name, int qty){


    globalSales[name] += qty;
    saveSales();
}



//<----------------- show top selling items -------------------->
void Cart::showTopSellingItems(){

    loadSales(); // Ensure sales data is loaded

    if (globalSales.empty()) {
        cout << "\n📦 No top sellers yet. Start selling to see insights!\n";
        return;
    }
    
    cout<<"\n🔥 Top Selling Items:\n";

    // Min-heap to keep top 5
    priority_queue<pair<int,string>,vector<pair<int,string>>,greater<>> pq;


    for(const auto& pair:globalSales){

        pq.push({pair.second, pair.first});
        if (pq.size() > 5) pq.pop();
    }

    vector<pair<int, string>> topItems;
    while(!pq.empty()){


        topItems.push_back(pq.top());
        pq.pop();
    }

    reverse(topItems.begin(), topItems.end());
    for(auto& [qty,name]:topItems){


        cout << name << " - " << qty << " units sold\n";
    }
}


//<----------------- load sales data from file -------------------->
void Cart::loadSales(){

    ifstream in("data/global_sales.dat");
    if (!in) return;

    string name;
    int qty;
    while(in>>name>>qty){

        globalSales[name] = qty;
    }


    in.close();
}


//<----------------- save sales data to file -------------------->
void Cart::saveSales(){


    ofstream out("data/global_sales.dat");
    for (auto& [name, qty] : globalSales){

        out<<name<<" "<<qty<<"\n";
    }


    out.close();
}
