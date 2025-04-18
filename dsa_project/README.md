# 🛒 DSA-Based Shopping System (C++ Project)

This is a fully-featured online shopping system built using C++ and advanced data structures like AVL Trees, Graphs, Heaps, HashMaps, and more. It features Admin and Customer modes, inventory management, discount coupons, QR-based UPI payments, delivery simulation, and more — all through a clean CLI interface.

## 🔧 Features

### 👤 Customer
- Sign Up / Login
- Browse inventory by sections (Fruits, Stationery, Snacks, Clothes, Shop, More)
- Search items with KMP algorithm
- Add to cart, view/edit cart
- Discount coupon support
- QR Code UPI Payment
- Checkout with bill generation
- Delivery time simulation using Dijkstra (Graph)
- Purchase history tracking
- Complaint/Feedback per item

  #  Dummy account for customer Login: 
      ID : RD005 
      Name : chirag 
      Age : 20 
      password : 1234

### 🛠️ Admin
- Login (username: `sandeep`, password: `1234`)
- Add/Remove/Update items in AVL-based inventory
- View purchase history
- Track top-selling items (Priority Queue)
- Manage UPI payment ranges
- Create discount codes

---

## 💾 Data Structures Used
- **AVL Tree**: Inventory per section
- **Graph + Dijkstra**: Delivery route time calculation
- **Priority Queue**: Top-selling items & low stock alerts
- **HashMap**: Discount codes
- **KMP Algorithm**: Fast search feature
- **File I/O**: Persistent user/inventory/cart history

---

## 📂 Folder Structure

dsa_project/
├── data/
|   ├── bills/
|   ├── inventory/(fruit.dat, clothes.dat, etc)
|   ├── customers.dat
|   ├── discount.dat
|   ├── global_sales.dat
|   ├── purchase_history.dat
|   ├── routes.dat
|   ├── temp_qr_data.txt
|   ├── upi_ids.dat
|   ├── users.dat
|   ├── last_user_id.txt
|
├── src/
│   ├── main.cpp
│   ├── admin.cpp / admin.h
│   ├── customer.cpp / customer.h
│   ├── inventory.cpp / inventory.h
│   ├── cart.cpp / cart.h
│   ├── generate_qr.cpp / generate_qr.h
│   ├── delivery_graph.cpp / delivery_graph.h
│   ├── search_utils.cpp / search_utils.h
│   ├── utils.cpp / utils.h
│   ├── discount.cpp / discount.h
|
|
├── Makefile
├── README.md
└── Shopping_app



---

## 📦 Requirements

- C++17 or above
- Terminal/CLI for interaction
- g++ compiler (for Linux)

---

## ▶️ How to Run

```bash
g++ -std=c++17 -o shopping_system main.cpp ...
./shopping_system





Data Structure                     	Used For


AVL Trees	-                         - Storing and managing inventory items section-wise (Fruits, Stationery, etc.)
                                    - Allows efficient insertion, deletion, and balanced search (O(log n))

Graphs (Adjacency List)	-           - Simulating delivery routes between cities/areas
                                    - Used with Dijkstra’s algorithm to calculate shortest delivery time after checkout

Priority Queue (Max-Heap)	          - Keeping track of top 5 selling items (based on quantity sold)
                                    - Alerting low stock items to admin


Hash Map (Unordered Map)	          - Mapping discount coupon codes to their discount percentages
                                    - Fast retrieval when applying discounts during checkout


KMP Algorithm	                      - Fast pattern matching in item search
                                    - Used for searching item names based on user keyword across all sections


Linked Lists (or Vectors)	          - Representing dynamic shopping cart (add, remove, modify items)
                                    - Used for cart management and bill generation


File Streams (ifstream/ofstream)	  - Persistent storage for:
                                     → Inventory per section
                                     → User login data
                                     → Discount codes
                                     → UPI configurations
                                     → Purchase history
                                     → Generated bills (with timestamped filenames)