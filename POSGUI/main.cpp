#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QGroupBox>
#include <QHeaderView>
#include <QFormLayout>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QInputDialog>
#include <QString>
#include <QTabWidget>
#include <QFrame>
#include <QFont>
#include <QComboBox>

#include <vector>
#include <string>

using namespace std;

vector<string> itemName;
vector<float> itemPrice;
vector<int> itemStock;

vector<string> discountCode;
vector<float> discountValue;

vector<string> cartName;
vector<int> cartQuantity;
vector<float> cartPrice;

float cartDiscount = 0.0f;
float stockAlertValue = 5;

void addStock(const string& name, float price, int stock) {
    itemName.push_back(name);
    itemPrice.push_back(price);
    itemStock.push_back(stock);
}

void addDiscount(const string& code, float value) {
    discountCode.push_back(code);
    discountValue.push_back(value);
}

class POSWindow : public QWidget {

public:

    QTableWidget* stockTable;
    QTableWidget* discountTable;
    QTableWidget* cartTable;
    QTableWidget* receiptTable;
    QTableWidget* lowStockTable;

    QLabel* totalItemsLabel;
    QLabel* totalStockLabel;
    QLabel* totalSalesLabel;
    QLabel* discountStatus;

    QLineEdit* itemNameEdit;
    QDoubleSpinBox* itemPriceSpin;
    QSpinBox* itemStockSpin;

    QLineEdit* discountCodeEdit;
    QDoubleSpinBox* discountValueSpin;

    QSpinBox* stockAlertSpin;

    POSWindow(QWidget* parent = nullptr) : QWidget(parent) {

        setWindowTitle("POS Terminal Management System");
        resize(1400, 850);

        QFont titleFont;
        titleFont.setPointSize(14);
        titleFont.setBold(true);

        // ===================== TOP DASHBOARD =====================

        totalItemsLabel = createDashboardCard("Total Products", "0");
        totalStockLabel = createDashboardCard("Total Stock", "0");
        totalSalesLabel = createDashboardCard("Current Cart Total", "0.00");

        QHBoxLayout* dashboardLayout = new QHBoxLayout;
        dashboardLayout->addWidget(totalItemsLabel->parentWidget());
        dashboardLayout->addWidget(totalStockLabel->parentWidget());
        dashboardLayout->addWidget(totalSalesLabel->parentWidget());

        // ===================== TABS =====================

        QTabWidget* tabs = new QTabWidget;

        QWidget* inventoryTab = new QWidget;
        QWidget* cartTab = new QWidget;
        QWidget* adminTab = new QWidget;

        tabs->addTab(inventoryTab, "Inventory");
        tabs->addTab(cartTab, "Cart & Checkout");
        tabs->addTab(adminTab, "Admin");

        // =========================================================
        // INVENTORY TAB
        // =========================================================

        stockTable = new QTableWidget;
        stockTable->setColumnCount(3);
        stockTable->setHorizontalHeaderLabels({"Item Name", "Price", "Stock"});
        stockTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        stockTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        stockTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

        QPushButton* addToCartBtn = new QPushButton("Add Selected To Cart");
        QPushButton* refreshBtn = new QPushButton("Refresh");

        QVBoxLayout* inventoryLayout = new QVBoxLayout(inventoryTab);

        QLabel* stockTitle = new QLabel("Available Inventory");
        stockTitle->setFont(titleFont);

        inventoryLayout->addWidget(stockTitle);
        inventoryLayout->addWidget(stockTable);

        QHBoxLayout* invButtons = new QHBoxLayout;
        invButtons->addWidget(addToCartBtn);
        invButtons->addWidget(refreshBtn);

        inventoryLayout->addLayout(invButtons);

        // =========================================================
        // CART TAB
        // =========================================================

        cartTable = new QTableWidget;
        cartTable->setColumnCount(4);
        cartTable->setHorizontalHeaderLabels({"Item", "Qty", "Price", "Total"});
        cartTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        cartTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        cartTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

        QPushButton* removeCartBtn = new QPushButton("Remove Selected");
        QPushButton* applyDiscountBtn = new QPushButton("Apply Discount");
        QPushButton* clearCartBtn = new QPushButton("Clear Cart");
        QPushButton* checkoutBtn = new QPushButton("Checkout");

        discountStatus = new QLabel("Discount Applied: 0%");

        receiptTable = new QTableWidget;
        receiptTable->setColumnCount(4);
        receiptTable->setHorizontalHeaderLabels({"Item", "Qty", "Price", "Total"});
        receiptTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        QVBoxLayout* cartLayout = new QVBoxLayout(cartTab);

        QLabel* cartTitle = new QLabel("Shopping Cart");
        cartTitle->setFont(titleFont);

        cartLayout->addWidget(cartTitle);
        cartLayout->addWidget(cartTable);

        QHBoxLayout* cartButtons = new QHBoxLayout;
        cartButtons->addWidget(removeCartBtn);
        cartButtons->addWidget(applyDiscountBtn);
        cartButtons->addWidget(clearCartBtn);
        cartButtons->addWidget(checkoutBtn);

        cartLayout->addLayout(cartButtons);
        cartLayout->addWidget(discountStatus);

        QLabel* receiptTitle = new QLabel("Receipt");
        receiptTitle->setFont(titleFont);

        cartLayout->addWidget(receiptTitle);
        cartLayout->addWidget(receiptTable);

        // =========================================================
        // ADMIN TAB
        // =========================================================

        // ADD STOCK GROUP

        QGroupBox* stockGroup = new QGroupBox("Add New Product");

        itemNameEdit = new QLineEdit;

        itemPriceSpin = new QDoubleSpinBox;
        itemPriceSpin->setRange(1, 100000);
        itemPriceSpin->setDecimals(2);

        itemStockSpin = new QSpinBox;
        itemStockSpin->setRange(1, 10000);

        QPushButton* addStockBtn = new QPushButton("Add Product");

        QFormLayout* stockForm = new QFormLayout;
        stockForm->addRow("Name:", itemNameEdit);
        stockForm->addRow("Price:", itemPriceSpin);
        stockForm->addRow("Stock:", itemStockSpin);
        stockForm->addRow(addStockBtn);

        stockGroup->setLayout(stockForm);

        // ADD DISCOUNT GROUP

        QGroupBox* discountGroup = new QGroupBox("Discount Management");

        discountCodeEdit = new QLineEdit;

        discountValueSpin = new QDoubleSpinBox;
        discountValueSpin->setRange(1, 100);
        discountValueSpin->setSuffix("%");

        QPushButton* addDiscountBtn = new QPushButton("Add Discount");

        QFormLayout* discountForm = new QFormLayout;
        discountForm->addRow("Code:", discountCodeEdit);
        discountForm->addRow("Value:", discountValueSpin);
        discountForm->addRow(addDiscountBtn);

        discountGroup->setLayout(discountForm);

        // DISCOUNT TABLE

        discountTable = new QTableWidget;
        discountTable->setColumnCount(2);
        discountTable->setHorizontalHeaderLabels({"Code", "Discount"});
        discountTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        // LOW STOCK GROUP

        QGroupBox* lowStockGroup = new QGroupBox("Low Stock Alerts");

        stockAlertSpin = new QSpinBox;
        stockAlertSpin->setRange(1, 1000);
        stockAlertSpin->setValue(5);

        QPushButton* checkLowStockBtn = new QPushButton("Check Alerts");

        lowStockTable = new QTableWidget;
        lowStockTable->setColumnCount(2);
        lowStockTable->setHorizontalHeaderLabels({"Item", "Remaining Stock"});
        lowStockTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        QVBoxLayout* lowStockLayout = new QVBoxLayout;
        lowStockLayout->addWidget(new QLabel("Alert Below Quantity:"));
        lowStockLayout->addWidget(stockAlertSpin);
        lowStockLayout->addWidget(checkLowStockBtn);
        lowStockLayout->addWidget(lowStockTable);

        lowStockGroup->setLayout(lowStockLayout);

        // ADMIN MAIN LAYOUT

        QGridLayout* adminLayout = new QGridLayout(adminTab);

        adminLayout->addWidget(stockGroup, 0, 0);
        adminLayout->addWidget(discountGroup, 0, 1);
        adminLayout->addWidget(discountTable, 1, 0, 1, 2);
        adminLayout->addWidget(lowStockGroup, 0, 2, 2, 1);

        // =========================================================
        // MAIN LAYOUT
        // =========================================================

        QVBoxLayout* mainLayout = new QVBoxLayout(this);

        QLabel* title = new QLabel("Point Of Sale System");
        title->setAlignment(Qt::AlignCenter);
        title->setFont(titleFont);

        mainLayout->addWidget(title);
        mainLayout->addLayout(dashboardLayout);
        mainLayout->addWidget(tabs);

        // =========================================================
        // DEFAULT DATA
        // =========================================================

        addStock("Laptop", 1000, 5);
        addStock("Mouse", 20, 12);
        addStock("Keyboard", 50, 8);
        addStock("Desk", 300, 2);
        addStock("Chair", 150, 3);

        addDiscount("SAVE10", 10);
        addDiscount("HALF", 50);

        refreshStockTable();
        refreshDiscountTable();
        refreshDashboard();

        // =========================================================
        // BUTTON CONNECTIONS
        // =========================================================

        connect(addStockBtn, &QPushButton::clicked, [this]() {

            string name = itemNameEdit->text().toStdString();

            if (name.empty()) {
                QMessageBox::warning(this, "Error", "Enter product name.");
                return;
            }

            addStock(
                name,
                itemPriceSpin->value(),
                itemStockSpin->value()
                );

            refreshStockTable();
            refreshDashboard();

            itemNameEdit->clear();
            itemPriceSpin->setValue(1);
            itemStockSpin->setValue(1);
        });

        connect(addDiscountBtn, &QPushButton::clicked, [this]() {

            string code = discountCodeEdit->text().toStdString();

            if (code.empty()) {
                QMessageBox::warning(this, "Error", "Enter discount code.");
                return;
            }

            addDiscount(
                code,
                discountValueSpin->value()
                );

            refreshDiscountTable();

            discountCodeEdit->clear();
            discountValueSpin->setValue(1);
        });

        connect(addToCartBtn, &QPushButton::clicked, [this]() {

            int row = stockTable->currentRow();

            if (row < 0) {
                QMessageBox::warning(this, "Error", "Select an item.");
                return;
            }

            int available = itemStock[row];

            if (available <= 0) {
                QMessageBox::warning(this, "Stock", "Item out of stock.");
                return;
            }

            bool ok;

            int qty = QInputDialog::getInt(
                this,
                "Quantity",
                "Enter Quantity",
                1,
                1,
                available,
                1,
                &ok
                );

            if (!ok) return;

            bool found = false;

            for (int i = 0; i < (int)cartName.size(); i++) {

                if (cartName[i] == itemName[row]) {

                    cartQuantity[i] += qty;

                    found = true;

                    break;
                }
            }

            if (!found) {

                cartName.push_back(itemName[row]);
                cartQuantity.push_back(qty);
                cartPrice.push_back(itemPrice[row]);
            }

            itemStock[row] -= qty;

            refreshStockTable();
            refreshCartTable();
            refreshDashboard();
        });

        connect(removeCartBtn, &QPushButton::clicked, [this]() {

            int row = cartTable->currentRow();

            if (row < 0) return;

            for (int i = 0; i < (int)itemName.size(); i++) {

                if (itemName[i] == cartName[row]) {

                    itemStock[i] += cartQuantity[row];

                    break;
                }
            }

            cartName.erase(cartName.begin() + row);
            cartQuantity.erase(cartQuantity.begin() + row);
            cartPrice.erase(cartPrice.begin() + row);

            refreshCartTable();
            refreshStockTable();
            refreshDashboard();
        });

        connect(applyDiscountBtn, &QPushButton::clicked, [this]() {

            bool ok;

            QString code = QInputDialog::getText(
                this,
                "Discount Code",
                "Enter Discount Code",
                QLineEdit::Normal,
                "",
                &ok
                );

            if (!ok) return;

            bool found = false;

            for (int i = 0; i < (int)discountCode.size(); i++) {

                if (discountCode[i] == code.toStdString()) {

                    cartDiscount = discountValue[i];

                    found = true;

                    break;
                }
            }

            if (found) {

                discountStatus->setText(
                    QString("Discount Applied: %1%").arg(cartDiscount)
                    );

                refreshDashboard();
            }
            else {

                QMessageBox::warning(this, "Invalid", "Discount code invalid.");
            }
        });

        connect(clearCartBtn, &QPushButton::clicked, [this]() {

            for (int i = 0; i < (int)cartName.size(); i++) {

                for (int j = 0; j < (int)itemName.size(); j++) {

                    if (cartName[i] == itemName[j]) {

                        itemStock[j] += cartQuantity[i];

                        break;
                    }
                }
            }

            cartName.clear();
            cartQuantity.clear();
            cartPrice.clear();

            cartDiscount = 0;

            discountStatus->setText("Discount Applied: 0%");

            refreshCartTable();
            refreshStockTable();
            refreshDashboard();
        });

        connect(checkoutBtn, &QPushButton::clicked, [this]() {

            if (cartName.empty()) {

                QMessageBox::information(this, "Cart", "Cart is empty.");

                return;
            }

            receiptTable->setRowCount(0);

            float total = 0;

            for (int i = 0; i < (int)cartName.size(); i++) {

                float itemTotal = cartQuantity[i] * cartPrice[i];

                total += itemTotal;

                int row = receiptTable->rowCount();

                receiptTable->insertRow(row);

                receiptTable->setItem(
                    row,
                    0,
                    new QTableWidgetItem(
                        QString::fromStdString(cartName[i])
                        )
                    );

                receiptTable->setItem(
                    row,
                    1,
                    new QTableWidgetItem(
                        QString::number(cartQuantity[i])
                        )
                    );

                receiptTable->setItem(
                    row,
                    2,
                    new QTableWidgetItem(
                        QString::number(cartPrice[i], 'f', 2)
                        )
                    );

                receiptTable->setItem(
                    row,
                    3,
                    new QTableWidgetItem(
                        QString::number(itemTotal, 'f', 2)
                        )
                    );
            }

            if (cartDiscount > 0) {

                total -= total * (cartDiscount / 100.0f);
            }

            QMessageBox::information(
                this,
                "Checkout Complete",
                QString("Final Total: %1").arg(total)
                );

            cartName.clear();
            cartQuantity.clear();
            cartPrice.clear();

            cartDiscount = 0;

            discountStatus->setText("Discount Applied: 0%");

            refreshCartTable();
            refreshDashboard();
        });

        connect(checkLowStockBtn, &QPushButton::clicked, [this]() {

            lowStockTable->setRowCount(0);

            stockAlertValue = stockAlertSpin->value();

            for (int i = 0; i < (int)itemName.size(); i++) {

                if (itemStock[i] < stockAlertValue) {

                    int row = lowStockTable->rowCount();

                    lowStockTable->insertRow(row);

                    lowStockTable->setItem(
                        row,
                        0,
                        new QTableWidgetItem(
                            QString::fromStdString(itemName[i])
                            )
                        );

                    lowStockTable->setItem(
                        row,
                        1,
                        new QTableWidgetItem(
                            QString::number(itemStock[i])
                            )
                        );
                }
            }
        });

        connect(refreshBtn, &QPushButton::clicked, [this]() {

            refreshStockTable();
            refreshDashboard();
        });
    }

    QLabel* createDashboardCard(const QString& title, const QString& value) {

        QFrame* card = new QFrame;

        card->setFrameShape(QFrame::StyledPanel);

        QVBoxLayout* layout = new QVBoxLayout(card);

        QLabel* titleLabel = new QLabel(title);

        QLabel* valueLabel = new QLabel(value);

        QFont f;
        f.setPointSize(18);
        f.setBold(true);

        valueLabel->setFont(f);

        layout->addWidget(titleLabel);
        layout->addWidget(valueLabel);

        card->setLayout(layout);

        return valueLabel;
    }

    void refreshStockTable() {

        stockTable->setRowCount(itemName.size());

        for (int i = 0; i < (int)itemName.size(); i++) {

            stockTable->setItem(
                i,
                0,
                new QTableWidgetItem(
                    QString::fromStdString(itemName[i])
                    )
                );

            stockTable->setItem(
                i,
                1,
                new QTableWidgetItem(
                    QString::number(itemPrice[i], 'f', 2)
                    )
                );

            stockTable->setItem(
                i,
                2,
                new QTableWidgetItem(
                    QString::number(itemStock[i])
                    )
                );
        }
    }

    void refreshDiscountTable() {

        discountTable->setRowCount(discountCode.size());

        for (int i = 0; i < (int)discountCode.size(); i++) {

            discountTable->setItem(
                i,
                0,
                new QTableWidgetItem(
                    QString::fromStdString(discountCode[i])
                    )
                );

            discountTable->setItem(
                i,
                1,
                new QTableWidgetItem(
                    QString::number(discountValue[i]) + "%"
                    )
                );
        }
    }

    void refreshCartTable() {

        cartTable->setRowCount(cartName.size());

        float total = 0;

        for (int i = 0; i < (int)cartName.size(); i++) {

            float itemTotal = cartQuantity[i] * cartPrice[i];

            total += itemTotal;

            cartTable->setItem(
                i,
                0,
                new QTableWidgetItem(
                    QString::fromStdString(cartName[i])
                    )
                );

            cartTable->setItem(
                i,
                1,
                new QTableWidgetItem(
                    QString::number(cartQuantity[i])
                    )
                );

            cartTable->setItem(
                i,
                2,
                new QTableWidgetItem(
                    QString::number(cartPrice[i], 'f', 2)
                    )
                );

            cartTable->setItem(
                i,
                3,
                new QTableWidgetItem(
                    QString::number(itemTotal, 'f', 2)
                    )
                );
        }
    }

    void refreshDashboard() {

        totalItemsLabel->setText(
            QString::number(itemName.size())
            );

        int stock = 0;

        for (int val : itemStock) {
            stock += val;
        }

        totalStockLabel->setText(
            QString::number(stock)
            );

        float total = 0;

        for (int i = 0; i < (int)cartName.size(); i++) {

            total += cartQuantity[i] * cartPrice[i];
        }

        if (cartDiscount > 0) {

            total -= total * (cartDiscount / 100.0f);
        }

        totalSalesLabel->setText(
            QString::number(total, 'f', 2)
            );
    }
};

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    POSWindow window;

    window.show();

    return app.exec();
}