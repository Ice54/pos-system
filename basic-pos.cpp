#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX = 100;
string itemName[MAX];
float itemPrice[MAX];
int itemStock[MAX];
int slotsFilled = 0;

string cartName[MAX];
int cartQuantity[MAX];
float cartPrice[MAX];
int cartFilled = 0;

void inputStock() {
    char choice;
    for (int i = slotsFilled; i < MAX; i++) {
        cout << "Add item? (Y/N): ";
        cin >> choice;
        while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
            cout << "Please enter Y or N: ";
            cin >> choice;
        }
        if (choice == 'N' || choice == 'n') break;
        cout << "Enter item name: ";
        cin.ignore();
        getline(cin, itemName[i]);
        cout << "Enter item price: ";
        cin >> itemPrice[i];
        cout << "Enter item stock: ";
        cin >> itemStock[i];
        slotsFilled++;
    }
}

void displayStock() {
    cout << left << setw(20) << "Item" << setw(10) << "Price" << setw(10) << "Stock" << endl;
    for (int i = 0; i < slotsFilled; i++) {
        cout << setw(20) << itemName[i] << setw(10) << itemPrice[i] << setw(10) << itemStock[i] << endl;
    }
}

void addItem() {
    string name;
    cout << "Item name: ";
    cin.ignore();
    getline(cin, name);
    for (int i = 0; i < slotsFilled; i++) {
        if (itemName[i] == name) {
            int qty;
            cout << "Quantity: ";
            cin >> qty;
            if (qty <= itemStock[i]) {
                cartName[cartFilled] = name;
                cartPrice[cartFilled] = itemPrice[i];
                cartQuantity[cartFilled] = qty;
                itemStock[i] -= qty;
                cartFilled++;
                cout << "Added to cart.\n";
            }
            else {
                cout << "Not enough stock.\n";
            }
            return;
        }
    }
    cout << "Item not found.\n";
}

void generateReceipt() {
    if (cartFilled == 0) {
        cout << "Cart empty.\n";
        return;
    }
    float total = 0;
    cout << "\n--- Receipt ---\n";
    cout << left << setw(20) << "Item" << setw(10) << "Qty" << setw(10) << "Price" << setw(10) << "Total" << endl;
    for (int i = 0; i < cartFilled; i++) {
        float itemTotal = cartQuantity[i] * cartPrice[i];
        total += itemTotal;
        cout << setw(20) << cartName[i] << setw(10) << cartQuantity[i] << setw(10) << cartPrice[i] << setw(10) << itemTotal << endl;
    }
    cout << "Total: " << total << "\n";
    cartFilled = 0;
}

int main() {
    cout << "Welcome to POS Terminal\n";
    inputStock();
    displayStock();
    addItem();
    generateReceipt();
    return 0;
}