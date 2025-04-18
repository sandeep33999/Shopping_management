#ifndef SEARCH_UTILS_H
#define SEARCH_UTILS_H

#include <string>
#include <vector>
using namespace std;

struct ItemInfo{
    string name;
    string section;
    float price;
    int stock;
};


vector<int> buildLPS(const string& pattern);
bool kmpSearch(const string& text,const string& pattern);
vector<ItemInfo> searchItems(const string& keyword); // return matching items

#endif
