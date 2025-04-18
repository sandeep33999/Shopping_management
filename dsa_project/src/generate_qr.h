#ifndef GENERATE_QR_H
#define GENERATE_QR_H

#include <string>
using namespace std;

struct UPIInfo{


    string upi_id;
    float min_amount;
    float max_amount;
};

void loadUPIList();
string getUPIForAmount(float amount);
void generateQR(const string& upi_id, float amount);
void qrWithTimer(const string& upi_id, float amount, int timeoutSecs = 10);     // expiry time for QR code

void adminUPIManager(); // Add, Remove, View

#endif
