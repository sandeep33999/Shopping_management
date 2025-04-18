#include<iostream>
#include<fstream>
#include"inventory.h"
#include"search_utils.h"
#include<vector>
#include<limits>


using namespace std;



//<---------- Initialize All Sections ----------->
void initializeAllSections(){
    fruitsTree.loadInventory("data/inventory/fruits.dat");
    snacksTree.loadInventory("data/inventory/snacks.dat");
    clothesTree.loadInventory("data/inventory/clothes.dat");
    stationeryTree.loadInventory("data/inventory/stationery.dat");
    moreTree.loadInventory("data/inventory/more.dat");
    shopTree.loadInventory("data/inventory/shop.dat");
}


//<---------- Load Inventory from file ----------->
void InventoryAVL::loadInventory(const string& filename){

    ifstream in(filename);
    string name;
    int quantity;
    double price;

    while(in>>name>>quantity>>price){


        Item item{name, quantity,price};
        addItem(item);
    }
}

//Part 1: AVL Tree Core

InventoryAVL::InventoryAVL(){

    root = nullptr;
}

int InventoryAVL::height(AVLNode* node){

    return node?node->height : 0;
}

int InventoryAVL::getBalance(AVLNode* node){

    return node ?height(node->left)-height(node->right):0;
}

AVLNode* InventoryAVL::rightRotate(AVLNode* y){

    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right =y;
    y->left=T2;
    y->height= max(height(y->left), height(y->right))+1;
    x->height= max(height(x->left), height(x->right))+1;
    return x;
}


AVLNode* InventoryAVL::leftRotate(AVLNode* x){


    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right =T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

// ➡️ Part 2: Insertion, Removal, Update

AVLNode* InventoryAVL::insert(AVLNode* node, Item item){


    if(!node){
        AVLNode* newNode = new AVLNode{item, nullptr, nullptr, 1};
        return newNode;
    }

    if(item.name < node->data.name)
        node->left = insert(node->left, item);
    else if(item.name > node->data.name)
        node->right = insert(node->right, item);
    else
        return node;

    node->height =1 + max(height(node->left), height(node->right));
    int balance =getBalance(node);

    // Perform rotations
    if(balance>1 && item.name < node->left->data.name)
        return rightRotate(node);
    if(balance<-1 && item.name > node->right->data.name)
        return leftRotate(node);
    if(balance>1 && item.name > node->left->data.name) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance<-1 && item.name < node->right->data.name) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


AVLNode* InventoryAVL::minValueNode(AVLNode* node){


    AVLNode* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}


//<-------------Remove Item------------>

AVLNode* InventoryAVL::remove(AVLNode* root, string name){


    if (!root) return root;

    if (name < root->data.name)
        root->left = remove(root->left, name);
    else if (name > root->data.name)
        root->right = remove(root->right, name);
    else {
        if(!root->left ||!root->right){
            AVLNode* temp = root->left ? root->left : root->right;
            if (!temp){
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            AVLNode* temp = minValueNode(root->right);
            root->data =temp->data;
            root->right= remove(root->right, temp->data.name);
        }
    }

    if (!root) return root;

    root->height=1+max(height(root->left),height(root->right));

    int balance=getBalance(root);

    if(balance>1 && getBalance(root->left)>=0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left)<0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) >0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}




// <------Inventory Operations + File I/O------>
void InventoryAVL::addItem(const Item& item){


    root = insert(root, item);
}


//<-------------Remove Item------------>
void InventoryAVL::removeItem(const string& name){

    root = remove(root, name);
}


//<-------------Update Item------------>
void InventoryAVL::updateItem(const string& name, int quantity, double price){


    AVLNode* node = search(root, name);
    if(node){
        node->data.quantity = quantity;
        node->data.price = price;
    }
}


//<-------------Display Items------------>
void InventoryAVL::displayItems(){


    inorder(root);
}


//<-------------Inorder Traversal------------>
void InventoryAVL::inorder(AVLNode* node){


    if (!node) return;
    inorder(node->left);
    cout << "🔸 " << node->data.name << " | Qty: " << node->data.quantity << " | Price: ₹" << node->data.price << endl;
    inorder(node->right);
}



//<-------------File Persistence + Section Management------------>
void InventoryAVL::saveInventory(const string& filename){


    ofstream out(filename);
    if (out.is_open()) {
        out.close();  // Clear file first
        saveToFile(root, filename);  // Now write new data
    }
}


//<-------------File I/O------------>
void InventoryAVL::saveToFile(AVLNode* node, const string& filename){

    if (!node) return;
    ofstream out(filename, ios::app);
    out << node->data.name << " " << node->data.quantity << " " << node->data.price << endl;
    saveToFile(node->left, filename);
    saveToFile(node->right, filename);
}


//<-------------searching------------>
Item* InventoryAVL::searchItem(const string& name){

    AVLNode* found = search(root, name);
    if (found)
        return &found->data;
    return nullptr;
}

//<-------------searching------------>
AVLNode* InventoryAVL::search(AVLNode* node, const string& name){


    if (!node || node->data.name == name) return node;
    if (name < node->data.name) return search(node->left, name);
    return search(node->right, name);
}




//<---------- Manage Section ----------->


void manageSection(int sectionID){


    string sectionFiles[] = {
        "data/inventory/fruits.dat",
        "data/inventory/stationery.dat",
        "data/inventory/snacks.dat",
        "data/inventory/clothes.dat",
        "data/inventory/shop.dat",
        "data/inventory/more.dat"
    };


    string sectionNames[] = {"Fruits", "Stationery", "Snacks", "Clothes", "Shop", "More"};

    InventoryAVL inv;
    inv.loadInventory(sectionFiles[sectionID - 1]);

    int choice;
    string name;
    int qty;
    double price;


    while(true){

        cout << "\n===== Managing " << sectionNames[sectionID - 1]<<" =====\n";
        cout << "1. Add Item\n2. Remove Item\n3. Update Item\n4. Display Items\n5. Back\n";
        cout << "Choose: ";
        cin >> choice;

        if(cin.fail()){
            system("clear");
            cout << "❌ Invalid input. Please enter a number! ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            cout << "Enter item name: ";
             cin >> name;
            if(cin.fail()){
                system("clear");
                cout << "❌ Invalid input. Please enter a string! ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            cout << "Quantity: ";
            cin >> qty;

            if(cin.fail()){
                system("clear");
                cout << "❌ Invalid input. Please enter a number! ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;

            }

            cout << "Price: ";
            cin >> price;

            if(cin.fail()){
                system("clear");
                cout << "❌ Invalid input. Please enter a number! ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            inv.addItem({name, qty, price});

        } else if (choice == 2) {
            cout << "Enter item name to remove: "; cin >> name;
            if(cin.fail()){
                system("clear");
                cout << "❌ Invalid input. Please enter a string! ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            inv.removeItem(name);

        }
        else if(choice ==3){

            cout << "Enter item name to update: ";
            cin >> name;

            if(cin.fail()){
                system("clear");
                cout << "❌ Invalid input. Please enter a string! ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            cout << "New Quantity: ";
            cin >> qty;

            if(cin.fail()){
                system("clear");
                cout << "❌ Invalid input. Please enter a number! ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            cout << "New Price: ";
            cin >> price;

            if(cin.fail()){
                system("clear");
                cout << "❌ Invalid input. Please enter a number! ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            inv.updateItem(name, qty, price);

        }else if (choice == 4){
            inv.displayItems();

        }
        else if(choice==5){
            inv.saveInventory(sectionFiles[sectionID - 1]);
            break;
        } else{


            cout << "Invalid input.\n";
        }
    }
}


//<---------- Global Inventory Trees ----------->
InventoryAVL fruitsTree, snacksTree, clothesTree, stationeryTree, moreTree, shopTree;


//<---------- Collecting Items from Trees ----------->
void collectItemsFromTree(AVLNode* node, const string& section, vector<ItemInfo>& result) {
    if (!node) return;
    collectItemsFromTree(node->left, section, result);
    ItemInfo info;
    info.name = node->data.name;
    info.price = node->data.price;
    info.stock = node->data.quantity;

    info.section = section;
    result.push_back(info);
    collectItemsFromTree(node->right, section, result);
}



//<---------- Get All Items ----------->
vector<ItemInfo> getAllItems(){
    vector<ItemInfo> result;
    collectItemsFromTree(fruitsTree.root, "Fruits", result);
    collectItemsFromTree(snacksTree.root, "Snacks", result);
    collectItemsFromTree(clothesTree.root, "Clothes", result);
    collectItemsFromTree(stationeryTree.root, "Stationery", result);
    collectItemsFromTree(moreTree.root, "More", result);
    collectItemsFromTree(shopTree.root, "Shop", result);
    return result;
}



