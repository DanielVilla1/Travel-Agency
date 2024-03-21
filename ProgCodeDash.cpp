#include <iostream>
#include <string>
using namespace std;

struct Traveler {
    string name;
    int age;
    double budget;
    Traveler* next = nullptr;
    Traveler* prev = nullptr;
};

struct TravelerList {
    Traveler* head = nullptr;
    Traveler* tail = nullptr;
};

struct Product {
    string name;
    double price;
    int quantity;
    Product* next = nullptr;
};

struct Vendor {
    Product* head = nullptr;
    Product* tail = nullptr;
};

struct Purchase {
    string productName;
    string travelerName;
    int quantity;
    Purchase* next = nullptr;
};

struct PurchaseHistory {
    Purchase* head = nullptr;
};

void MainMenu(int&);
void GetInfo(TravelerList&);
void TravelerLists(const TravelerList&);
double CalculateTravelerBudget(const TravelerList&);
void DeleteTraveler(TravelerList&);
void DeleteHistory(TravelerList&);
void AddProduct(Vendor&);
void ViewProducts(const Vendor&);
void PurchaseProduct(const Vendor&, TravelerList&, PurchaseHistory&);
void ViewPurchaseHistory(const PurchaseHistory&);
void RemoveProduct(Vendor&);
double CalculateTotalRevenue(const PurchaseHistory&, const Vendor&);
bool Continue(int&);

int main() {
    int option = 0;
    TravelerList travelerList;
    Vendor canteen;
    PurchaseHistory purchaseHistory;

    MainMenu(option);
    do {
        if (option == 1) {
            system("cls");
            GetInfo(travelerList);
        }
        else if (option == 2) {
            if (travelerList.head != nullptr) {
                system("pause");
                system("cls");
                TravelerLists(travelerList);
            }
            else {
                system("cls");
                cout << "No lists Yet!\n";
                system("pause");
                system("cls");
            }
        }
        else if (option == 3) {
            if (travelerList.head != nullptr) {
                system("cls");
                cout << "All Travelers Budget: " << CalculateTravelerBudget(travelerList) << "\n";
                system("pause");
                system("cls");
            }
            else {
                system("cls");
                cout << "No Travelers Budget to Calculate!\n";
                system("pause");
                system("cls");
            }
        }
        else if (option == 4) {
            if (travelerList.head != nullptr) {
                system("cls");
                DeleteTraveler(travelerList);
            }
            else {
                system("cls");
                cout << "No travelers to delete!\n";
                system("pause");
                system("cls");
            }
        }
        else if (option == 5) {
            if (travelerList.head != nullptr) {
                system("cls");
                DeleteHistory(travelerList);
            }
            else {
                system("cls");
                cout << "No travelers to delete!\n";
                system("pause");
                system("cls");
            }
        }
        else if (option == 6) {
            system("cls");
            AddProduct(canteen);
        }
        else if (option == 7) {
            system("cls");
            ViewProducts(canteen);
        }
        else if (option == 8) {
            if (travelerList.head != nullptr) {
                system("cls");
                PurchaseProduct(canteen, travelerList, purchaseHistory);
            }
            else {
                system("cls");
                cout << "No travelers to make purchases for!\n";
                system("pause");
                system("cls");
            }
        }
        else if (option == 9) {
            system("cls");
            if (purchaseHistory.head != nullptr) {
                ViewPurchaseHistory(purchaseHistory);
            }
            else {
                cout << "No Purchase Transactions Yet\n";
            }
            system("pause");
            system("cls");
        }
        else if (option == 10) {
            system("cls");
            RemoveProduct(canteen);
        }
        else if (option == 11) {
            system("cls");
            cout << "Total Revenue: Php " << CalculateTotalRevenue(purchaseHistory, canteen) << "\n";
            system("pause");
            system("cls");
        }
        else if (option == 0) {
            system("cls");
            cout << "Thank you!";
            exit(0);
        }
        else cout << "\nInvalid Input!\n";

    } while (Continue(option));

    Traveler* current = travelerList.head;
    while (current != nullptr) {
        Traveler* next = current->next;
        delete current;
        current = next;
    }

    return 0;
}

void MainMenu(int& option) {
    cout << "================================="
        << "\n        Traveler Record"
        << "\n================================="
        << "\n1. Add Traveler"
        << "\n2. Lists of Traveler"
        << "\n3. Calculate Traveler Budget"
        << "\n4. Delete One Traveler"
        << "\n5. Delete Traveler History"
        << "\n6. Add Vendor Product"
        << "\n7. View Vendor Products"
        << "\n8. Purchase Product"
        << "\n9. View Purchase History"
        << "\n10. Remove one Product"
        << "\n11. Calculate Total Revenue"
        << "\n0. Exit"
        << "\nInput choice: ";
    cin >> option;
}

void GetInfo(TravelerList& travelerList) {
    const int MAX_TRAVELERS = 100;
    int travelerSize;
    Traveler* newTraveler = nullptr;
    do {
        cout << "How many Travelers would you like to add: ";
        cin >> travelerSize;
    } while (travelerSize <= 0 || travelerSize >= MAX_TRAVELERS);

    for (int i = 0; i < travelerSize; i++) {
        newTraveler = new Traveler;
        cout << "Traveler " << i + 1 << ": " << "\n";
        cout << "Name: "; cin >> newTraveler->name;
        cout << "Age: "; cin >> newTraveler->age;
        cout << "Budget: "; cin >> newTraveler->budget;
        newTraveler->next = nullptr;
        newTraveler->prev = nullptr;
        if (travelerList.head == nullptr) {
            travelerList.head = newTraveler;
            travelerList.tail = newTraveler;
        }
        else {
            travelerList.tail->next = newTraveler;
            newTraveler->prev = travelerList.tail;
            travelerList.tail = newTraveler;
        }
        cout << "\n";
    }
}

void TravelerLists(const TravelerList& TRAVELER_LIST) {
    Traveler* current = TRAVELER_LIST.head;
    int travelerNumber = 1;
    while (current != nullptr) {
        cout << "\nTraveler " << travelerNumber << ": ";
        cout << "\nName: " << current->name
            << "\nAge: " << current->age
            << "\nBudget: " << current->budget;
        cout << "\n";
        current = current->next;
        travelerNumber++;
    }
}

void DeleteTraveler(TravelerList& travelerList) {
    Traveler* current = travelerList.head;
    string name;
    cout << "Enter the name of the traveler to delete: ";
    cin >> name;

    while (current != nullptr) {
        if (current->name == name) {
            if (current->prev != nullptr)
                current->prev->next = current->next;
            else
                travelerList.head = current->next;
            if (current->next != nullptr)
                current->next->prev = current->prev;
            else
                travelerList.tail = current->prev;
            delete current;
            cout << "\Traveler record for " << name << " deleted successfully.\n";
            return;
        }
        current = current->next;
    }
}

void DeleteHistory(TravelerList& travelerList) {
    Traveler* current = travelerList.head;
    while (current != nullptr) {
        Traveler* next = current->next;
        delete current;
        current = next;
    }
    travelerList.head = nullptr;
    travelerList.tail = nullptr;
    cout << "\nAll traveler records deleted successfully.\n";
}

void AddProduct(Vendor& canteen) {
    Product* newProduct = new Product;
    cout << "Enter Product Name: ";
    cin >> newProduct->name;
    cout << "Enter Product Price: ";
    cin >> newProduct->price;
    cout << "Enter Product Quantity: ";
    cin >> newProduct->quantity;
    if (canteen.head == nullptr) {
        canteen.head = newProduct;
        canteen.tail = newProduct;
    }
    else {
        canteen.tail->next = newProduct;
        canteen.tail = newProduct;
    }
    cout << "Product added successfully!\n";
}

void ViewProducts(const Vendor& CANTEEN) {
    Product* current = CANTEEN.head;
    int productNumber = 1;
    if (CANTEEN.head == nullptr) {
        cout << "No products available in the canteen.\n";
        return;
    }
    while (current != nullptr) {
        cout << "\nProduct " << productNumber << ": ";
        cout << "\nName: " << current->name
            << "\nPrice: " << current->price
            << "\nQuantity: " << current->quantity;
        cout << "\n";
        current = current->next;
        productNumber++;
    }
}

void PurchaseProduct(const Vendor& CANTEEN, TravelerList& travelerList, PurchaseHistory& purchaseHistory) {
    Purchase* newPurchase = new Purchase;
    Product* currentProduct = CANTEEN.head;
    Traveler* currentTraveler = travelerList.head;
    string travelerName, productName;
    int quantity;
    double totalPrice;
    cout << "Enter traveler name: ";
    cin >> travelerName;
    cout << "Enter product name: ";
    cin >> productName;
    cout << "Enter quantity: ";
    cin >> quantity;

    while (currentTraveler != nullptr) {
        if (currentTraveler->name == travelerName) {
            while (currentProduct != nullptr) {
                if (currentProduct->name == productName) {
                    if (currentProduct->quantity >= quantity) {
                        totalPrice = currentProduct->price * quantity;
                        if (currentTraveler->budget >= totalPrice) {
                            newPurchase->travelerName = travelerName;
                            newPurchase->productName = productName;
                            newPurchase->quantity = quantity;
                            newPurchase->next = purchaseHistory.head;
                            purchaseHistory.head = newPurchase;

                            currentProduct->quantity -= quantity;
                            currentTraveler->budget -= totalPrice;
                            cout << "Purchase Successful!\n";
                            return;
                        }
                        else {
                            cout << "Sorry, " << travelerName << " does not have enough budget.\n";
                            return;
                        }
                    }
                    else {
                        cout << "Sorry, " << productName << " does not have enough quantity.\n";
                        return;
                    }
                }
                currentProduct = currentProduct->next;
            }
            cout << "Product " << productName << " not found in the canteen.\n";
            return;
        }
        currentTraveler = currentTraveler->next;
    }
    cout << "Traveler " << travelerName << " not found.\n";
}

void ViewPurchaseHistory(const PurchaseHistory& PURCHASE_HISTORY) {
    Purchase* current = PURCHASE_HISTORY.head;
    if (PURCHASE_HISTORY.head == nullptr) {
        cout << "No Purchase Transactions Yet\n";
        return;
    }

    while (current != nullptr) {
        cout << "Traveler Name: " << current->travelerName << " purchased " << current->quantity << " " << current->productName << "\n";
        current = current->next;
    }
}

void RemoveProduct(Vendor& canteen) {
    string productName;
    Product* current = canteen.head;
    Product* prev = nullptr;
    cout << "Enter the name of the product to remove: ";
    cin >> productName;

    if (canteen.head == nullptr) {
        cout << "No products available in the canteen.\n";
        return;
    }

    while (current != nullptr) {
        if (current->name == productName) {
            if (prev == nullptr) {

                canteen.head = current->next;
                if (canteen.head == nullptr) {
                    canteen.tail = nullptr;
                }
            }
            else {
                prev->next = current->next;
                if (prev->next == nullptr) {
                    canteen.tail = prev;
                }
            }
            delete current;
            cout << "Product " << productName << " removed successfully!\n";
            return;
        }
        prev = current;
        current = current->next;
    }

    cout << "Product " << productName << " not found in the canteen.\n";
}

double CalculateTravelerBudget(const TravelerList& TRAVELER_LIST) {
    double sum = 0;
    int count = 0;
    Traveler* current = TRAVELER_LIST.head;
    while (current != nullptr) {
        sum += current->budget;
        count++;
        current = current->next;
    }
    if (count > 0)
        return sum + count;
    else
        return 0;
}

bool Continue(int& option) {
    int choice;
    cout << "\nDo you want to Continue?"
        << "\n1. Add another Traveler"
        << "\n2. View Traveler List"
        << "\n3. Calculate All Traveler Budget"
        << "\n4. Delete One Traveler"
        << "\n5. Delete Traveler History"
        << "\n6. Add Vendor Product"
        << "\n7. View Vendor Products"
        << "\n8. Purchase Product"
        << "\n9. View Purchase History"
        << "\n10. Remove one Product"
        << "\n11. Calculate Total Revenue"
        << "\n0. Exit"
        << "\nInput choice: ";
    cin >> choice;

    if (choice >= 0 && choice <= 11) {
        option = choice;
        return true;
    }
    return false;
}

double CalculateTotalRevenue(const PurchaseHistory& PURCHASE_HISTORY, const Vendor& CANTEEN) {
    double totalRevenue = 0.0;
    Purchase* currentPurchase = PURCHASE_HISTORY.head;
    Product* currentProduct = CANTEEN.head;

    while (currentPurchase != nullptr) {
        while (currentProduct != nullptr) {
            if (currentProduct->name == currentPurchase->productName) {
                totalRevenue += currentProduct->price * currentPurchase->quantity;
                break;
            }
            currentProduct = currentProduct->next;
        }
        currentPurchase = currentPurchase->next;
    }

    return totalRevenue;
}
