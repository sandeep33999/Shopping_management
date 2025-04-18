#include"generate_qr.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<thread>
#include<chrono>
#include<algorithm>
#include<limits>
using namespace std;

vector<UPIInfo> upiList;


//<----------------- Load UPI IDs from file -------------------->
void loadUPIList(){

    upiList.clear();
    ifstream in("data/upi_ids.dat");
    if (!in) return;

    UPIInfo info;
    while (in >> info.upi_id >> info.min_amount >> info.max_amount)
        upiList.push_back(info);

    in.close();
}


//<----------------- Get UPI ID for a given amount -------------------->
string getUPIForAmount(float amount){

    loadUPIList();
    for(const auto& info:upiList){
        if(amount>=info.min_amount && amount<=info.max_amount)
            return info.upi_id;
    }
    return "default@ybl"; // fallback
}


//<----------------- Generate QR code using qrencode -------------------->
void generateQRCode(const string& upiID, float amount) {
    // Create UPI payment URL
    string qrData = "upi://pay?pa=" + upiID + "&pn=SARCShop&am=" + to_string(amount) + "&cu=INR";

    // Optional: Save to file (log for tracking or debugging)
    ofstream out("data/temp_qr_data.txt", ios::app);
    out << qrData << "\n";
    out.close();

    // Generate QR code in terminal using qrencode
    string command = "echo \"" + qrData + "\" | qrencode -t ANSIUTF8";
    system(command.c_str());
}


//<----------------- Generate QR code with amount -------------------->
void generateQR(const string& upi_id, float amount){


    cout<<"-----------------------------------------------------\n";
    cout<<"||       💰 Scan QR to pay ₹" << amount <<"./             ||"<< endl;
    cout<<"-----------------------------------------------------\n";
    generateQRCode(upi_id, amount); 
    cout<<"-----------------------------------------------------\n";
}


//<----------------- QR code with timer -------------------->
void qrWithTimer(const string& upi_id, float amount, int timeoutSecs){

    generateQR(upi_id, amount);
    cout<<"\n⏳ QR Code will expire in "<<timeoutSecs<<" seconds...\n";

    for(int i=0;i<timeoutSecs;++i){

        this_thread::sleep_for(chrono::seconds(1));
        if(i%2 ==0) cout<<".";

    }

    cout << "\n🚫 QR Code expired! Please retry checkout.\n";
}



//<----------------- Add UPI ID -------------------->
void addUPI(){

    string upi;
    float min_amt, max_amt;

    cout<<"Enter new UPI ID: ";
    cin>>upi;
    if(cin.fail()){

        if(cin.fail()){
            system("clear");
            cout << "❌ Invalid input. Please enter a string: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;  // or         addUPI();
        }
    }

    cout << "Enter min amount: ";
    cin >> min_amt;
    if(cin.fail()){
        system("clear");
        cout << "❌ Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        addUPI();
    }


    cout << "Enter max amount: ";
    cin >> max_amt;

    if(cin.fail()){
        system("clear");
        cout << "❌ Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // continue;
        addUPI();
    }

    ofstream out("data/upi_ids.dat", ios::app);
    out << upi << " " << min_amt << " " << max_amt << "\n";
    out.close();

    cout << "✅ UPI added successfully.\n";

}

//<----------------- Remove UPI ID -------------------->
void removeUPI(){


    string target;
    cout << "Enter UPI ID to remove: ";
    cin >> target;

    loadUPIList();
    vector<UPIInfo> updated;
    for (auto& info : upiList)
        if (info.upi_id != target) updated.push_back(info);

    ofstream out("data/upi_ids.dat");
    for (auto& info : updated)
        out << info.upi_id << " " << info.min_amount << " " << info.max_amount << "\n";
    out.close();

    cout << "✅ UPI removed if it existed.\n";


}

//<----------------- View all UPI IDs -------------------->
void viewAllUPI(){


    loadUPIList();
    cout << "\n📋 UPI Ranges:\n";
    for (auto& info : upiList)
        cout << "- " << info.upi_id << " : ₹" << info.min_amount << " - ₹" << info.max_amount << "\n";

}


//<----------------- Admin UPI Manager -------------------->
void adminUPIManager(){

    int choice;
    while (true){

        cout<< "\n==== ADMIN UPI MANAGER ====\n";
        cout<< "1. Add UPI\n2. Remove UPI\n3. View All\n4. Exit\nChoose: ";
        cin >>choice;

        if(cin.fail()){

            system("clear");
            cout << "❌ Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;

        }

        if (choice==1) addUPI();
        else if (choice==2) removeUPI();
        else if (choice==3) viewAllUPI();
        else if (choice==4) break;
        else{

            system("clear");
            cout<<"❌ Invalid choice.\n";
        }
    }


}
