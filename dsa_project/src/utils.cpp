#include "utils.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <filesystem>
using namespace std;

// Generate unique 6-character customer ID (based on user count)
string generateCustomerID(){

    int count=1;
    ifstream in("data/user_count.dat");

    if(in){

        in >>count;
        in.close();
    }

    ofstream out("data/user_count.dat");
    out<<count+1;
    out.close();

    stringstream ss;
    ss<<"USR"<<setfill('0') <<setw(3)<<count;
    return ss.str(); // e.g., USR001

}

string getCurrentDateTime(){


    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss<<1900+ltm->tm_year
       << "-"
       << setfill('0') << setw(2)<<1+ltm->tm_mon
       << "-"
       << setfill('0')<<setw(2) << ltm->tm_mday
       << "_"
       << setfill('0') << setw(2)<<ltm->tm_hour
       << "-"
       << setfill('0') << setw(2)<<ltm->tm_min
       << "-"
       << setfill('0')<<setw(2)<<ltm->tm_sec;
    return ss.str(); // YYYY-MM-DD_HH-MM-SS


}

string sanitizeString(const string& str){

    string result =str;
    for (char& ch :result){

        if(ch==' ') ch='_';

    }

    return result;
}

bool fileExists(const string& filename){

    
    return filesystem::exists(filename);
}


// View purchase history

void viewPurchaseHistory(){


    ifstream in("data/purchase_history.dat");
    if(!in){
        cout<<"No purchase history found.\n";
        return;
    }

    string line;
    while(getline(in,line)){
        if(line.find("UserID:") != string::npos){

            cout<<"---------------------------\n";
            cout<<line << "\n";
        }
        else if(line.find("Discount:") !=string::npos || line.find("Total:") != string::npos) {
            cout << line << "\n";
            cout << "---------------------------\n";
        }
        else if(!line.empty()){

            cout<<"  "<<line << "\n";
        }
    }


    in.close();
}
