#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string generateCustomerID();
std::string getCurrentDateTime();
std::string sanitizeString(const std::string& str);
bool fileExists(const std::string& filename);
void viewPurchaseHistory();

#endif
