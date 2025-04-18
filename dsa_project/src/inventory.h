#ifndef INVENTORY_H
#define INVENTORY_H

#include<string>
#include"search_utils.h"  // for ItemInfo
#include<vector>
using namespace std;


struct Item{

    string name;
    int quantity;
    double price;
};

struct AVLNode{
    Item data;
    AVLNode* left;
    AVLNode* right;
    int height;
};


class InventoryAVL{
private:
    // AVLNode* root;
    AVLNode* insert(AVLNode* node, Item item);
    AVLNode* remove(AVLNode* node, string name);
    AVLNode* update(AVLNode* node, string name, int quantity, double price);
    AVLNode* search(AVLNode* node, const string& name);
    void inorder(AVLNode* node);
    void saveToFile(AVLNode* node, const string& filename);
    AVLNode* loadFromFile(const string& filename);
    AVLNode* minValueNode(AVLNode* node);
    int height(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);

public:
    AVLNode* root;
    InventoryAVL();
    void addItem(const Item& item);
    void removeItem(const string& name);
    void updateItem(const string& name, int quantity, double price);
    void displayItems();
    void loadInventory(const string& filename);
    void saveInventory(const string& filename);
    Item* searchItem(const string& name);
};

void manageSection(int sectionID);
void initializeAllSections();

vector<ItemInfo> getAllItems(); //for searching


extern InventoryAVL fruitsTree;
extern InventoryAVL snacksTree;
extern InventoryAVL clothesTree;
extern InventoryAVL stationeryTree;
extern InventoryAVL moreTree;
extern InventoryAVL shopTree;


#endif
