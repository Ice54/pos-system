#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX = 100;
string itemName[MAX];
float itemPrice[MAX];
int itemStock[MAX];
int slotsFilled = 0;

string discountCode[MAX];
float discountValue[MAX];
int discountFilled = 0;

string cartName[MAX];
int cartQuantity[MAX];
float cartPrice[MAX];
int cartFilled_Start = 0, cartFilled_End = 0;
float cartDiscount = 0;
float stockAlertValue = 5;

void inputStock() {
    char choice;
    for (int i = slotsFilled; i < MAX; i++) {
        cout << "Add item? (Y/N): ";
        cin >> choice;
        while (choice != 'n' && choice != 'Y' && choice != 'y' && choice != 'N') {
            cout << "Please enter Y or N!";
            cin >> choice;
        }
        if (choice == 'Y' || choice == 'y') {
            cout << "Enter item name: ";
            cin.ignore();
            getline(cin, itemName[i]);
            cout << "Enter item price: ";
            cin >> itemPrice[i];
            while (itemPrice[i] <= 0) {
                cout << "Invalid item price!";
                cin >> itemPrice[i];
            }
            cout << "Enter item stock: ";
            cin >> itemStock[i];
            while (itemStock[i] <= 0) {
                cout << "Invalid item stock!";
                cin >> itemStock[i];
            }
            slotsFilled++;
        }
        else break;
    }
}

void displayStock() {
    for (int i = 0; i < slotsFilled; i++) {
        cout << setw(10) << "Item Name: " << itemName[i] << setw(10) << "Stock: " << itemStock[i] << setw(10) << "Price: " << itemPrice[i] << endl;
    }
}

void inputDiscountCode() {
    char choice;
    for (int i = discountFilled; i < MAX; i++) {
        cout << "Enter Code? (Y/N)";
        cin >> choice;
        while (choice != 'n' && choice != 'Y' && choice != 'y' && choice != 'N') {
            cout << "Please enter Y or N!";
            cin >> choice;
        }
        if (choice == 'Y' || choice == 'y') {
            cout << "Enter Discount Code: ";
            cin >> discountCode[i];
            cout << "Enter Discount Value: (x%)";
            cin >> discountValue[i];
            while (discountValue[i] <= 0 || discountValue[i] > 100) {
                cout << "Invalid Discount Value!";
                cin >> discountValue[i];
            }
            discountFilled++;
        }
        else break;
    }
}

void displayDiscountCode() {
    for (int i = 0; i < discountFilled; i++) {
        cout << setw(10) << "Code: " << discountCode[i] << setw(10) << "Value: " << discountValue[i] << endl;
    }
}

void stockAlerts() {
    for (int i = 0; i < slotsFilled; i++) {
        if (itemStock[i] < stockAlertValue) {
            cout << setw(10) << "Item Name: " << itemName[i] << setw(10) << "Stock: " << itemStock[i] << endl;
        }
    }
}

void displayMenu() {
    cout << "Main Menu:" << endl;
    cout << "1. Add Item to cart" << endl;
    cout << "2. Remove Item from cart" << endl;
    cout << "3. Apply Discount" << endl;
    cout << "4. Generate Receipt" << endl;
    cout << "5. Administrative Features" << endl;
    cout << "-1. Exit" << endl << endl;
    cout << "Select an option:" << endl;
}

void displayAdminMenu() {
    cout << "\nAdmin Menu\n";
    cout << "1. Add Stock\n";
    cout << "2. Display Stock\n";
    cout << "3. Add Discount Code\n";
    cout << "4. Display Discount Codes\n";
    cout << "5. Stock Alerts\n";
    cout << "-1. Back to Main Menu\n";
}

int checkCart(string itemToCheck) {
    if (cartFilled_End == cartFilled_Start) return 0;
    for (int i = cartFilled_Start; i < cartFilled_End; i++) {
        if (cartName[i] == itemToCheck) {
            cout << "Item already in cart!" << endl;
            return 1;
        }
    }
    return 0;
}

void addItem() {
    string AI_itemName;
    int AI_itemQuantity;
    cout << "Enter item name:" << endl;
    cin.ignore();
    getline(cin, AI_itemName);
    if (checkCart(AI_itemName) == 1) {
        cout << "Item already in cart." << endl;
        return;
    }
    bool itemFound = false;
    while (!itemFound) {
        for (int i = 0; i < slotsFilled; i++) {
            if (itemName[i] == AI_itemName) {
                itemFound = true;
                cartName[cartFilled_End] = itemName[i];
                cartPrice[cartFilled_End] = itemPrice[i];
                cout << "Enter item quantity: " << endl;
                cin >> AI_itemQuantity;
                while (AI_itemQuantity <= 0) {
                    cout << "Quantity must be at least 1. Re-enter: ";
                    cin >> AI_itemQuantity;
                }
                while (AI_itemQuantity > itemStock[i]) {
                    cout << "Insufficient stock. Available: " << itemStock[i] << ". Re-enter: ";
                    cin >> AI_itemQuantity;
                }
                cartQuantity[cartFilled_End] = AI_itemQuantity;
                itemStock[i] -= AI_itemQuantity;
                cartFilled_End++;
                cout << "Item added to cart successfully!" << endl;
                return;
            }
        }
        cout << "Item not found!\n1. Re-enter item name\n2. Exit\nChoice: ";
        char AI_choice;
        cin >> AI_choice;
        if (AI_choice == '1') {
            addItem();
            return;
        }
        else if (AI_choice == '2') {
            cout << "Returning to main menu." << endl;
            return;
        }
    }
}

void removeItem() {
    if (cartFilled_End == cartFilled_Start) {
        cout << "Cart is empty." << endl;
        return;
    }
    string RI_itemName;
    cout << "Enter item name to remove: ";
    cin.ignore();
    getline(cin, RI_itemName);
    for (int i = cartFilled_Start; i < cartFilled_End; i++) {
        if (cartName[i] == RI_itemName) {
            for (int j = 0; j < slotsFilled; j++) {
                if (itemName[j] == cartName[i]) {
                    itemStock[j] += cartQuantity[i];
                    break;
                }
            }
            for (int j = i; j < cartFilled_End - 1; j++) {
                cartName[j] = cartName[j + 1];
                cartPrice[j] = cartPrice[j + 1];
                cartQuantity[j] = cartQuantity[j + 1];
            }
            cartFilled_End--;
            cout << "Item removed from cart." << endl;
            return;
        }
    }
    cout << "Item not found in cart." << endl;
}

void applyDiscount() {
    string code;
    cout << "Enter discount code: ";
    cin >> code;
    for (int i = 0; i < discountFilled; i++) {
        if (discountCode[i] == code) {
            cartDiscount = discountValue[i];
            cout << "Discount applied: " << cartDiscount << "%" << endl;
            return;
        }
    }
    cout << "Invalid discount code." << endl;
}

void generateReceipt() {
    if (cartFilled_End == cartFilled_Start) {
        cout << "Cart is empty.\n";
        return;
    }
    float totalCost = 0;
    cout << "\n*******************************" << endl;
    cout << "Example Store For POS Demo" << endl;
    cout << "Thank You for Shopping" << endl;
    cout << "*******************************" << endl;
    cout << left << setw(20) << "Item" << setw(10) << "Qty" << setw(10) << "Price" << "Total" << endl;
    cout << "--------------------------------" << endl;
    for (int i = cartFilled_Start; i < cartFilled_End; i++) {
        float totalItem = cartQuantity[i] * cartPrice[i];
        totalCost += totalItem;
        cout << left << setw(20) << cartName[i] << setw(10) << cartQuantity[i] << fixed << setprecision(2) << setw(10) << cartPrice[i] << totalItem << endl;
    }
    cout << "--------------------------------" << endl;
    cout << left << setw(20) << "Subtotal:" << right << setw(20) << fixed << setprecision(2) << totalCost << endl;
    if (cartDiscount > 0) {
        double discountAmount = totalCost * (cartDiscount / 100.0);
        totalCost -= discountAmount;
        cout << left << setw(20) << "(Discount " << static_cast<int>(cartDiscount) << "%):" << right << setw(20) << "-" << discountAmount << endl;
    }
    cout << left << setw(20) << "Total Amount:" << right << setw(20) << totalCost << endl;
    cout << "****************************************" << endl;
    cout << "Visit Again!" << endl;
    cout << "****************************************" << endl;
}

void resetCart() {
    for (int i = cartFilled_Start; i < cartFilled_End; i++) {
        cartName[i] = "";
        cartPrice[i] = 0.0;
        cartQuantity[i] = 0;
    }
    cartFilled_Start = cartFilled_End = 0;
    cartDiscount = 0;
}

int main() {
    cout << "Welcome to the POS Terminal\nEnter Stock!\n";
    inputStock();
    displayStock();
    cout << "Enter Discount Codes\n";
    inputDiscountCode();
    displayDiscountCode();
    cout << "Enter Stock Alert Amount: ";
    cin >> stockAlertValue;
    while (stockAlertValue < 0) {
        cout << "Invalid Input! Enter a positive number: ";
        cin >> stockAlertValue;
    }

    int mainLoopChoice = 0;
    while (mainLoopChoice != -1) {
        displayMenu();
        cin >> mainLoopChoice;
        switch (mainLoopChoice) {
        case 1: addItem(); break;
        case 2: removeItem(); break;
        case 3: applyDiscount(); break;
        case 4: generateReceipt(); resetCart(); break;
        case 5: {
            int secondLoopChoice = 0;
            while (secondLoopChoice != -1) {
                displayAdminMenu();
                cin >> secondLoopChoice;
                switch (secondLoopChoice) {
                case 1: inputStock(); break;
                case 2: displayStock(); break;
                case 3: inputDiscountCode(); break;
                case 4: displayDiscountCode(); break;
                case 5: stockAlerts(); break;
                case -1: secondLoopChoice = -1; continue;
                default: cout << "Invalid Input!"; break;
                }
            }
            break;
        }
        case -1: return 0;
        default: cout << "Invalid choice!"; break;
        }
    }
    return 0;
}