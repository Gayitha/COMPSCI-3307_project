#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "package.h"
#include "packagemanager.h"
#include <QMessageBox>

// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Table configuration
    ui->packageTable->setColumnCount(6);
    ui->packageTable->setHorizontalHeaderLabels({"Recipient", "Courier", "Tracking Number", "Description", "Status", "Date Received"});

    // Table customization
    ui->packageTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->packageTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->packageTable->setSelectionBehavior(QTableWidget::SelectRows);
    ui->packageTable->setEditTriggers(QTableWidget::NoEditTriggers);

    // Button linking
    connect(ui->addPackageMainButton, &QPushButton::clicked, this, &MainWindow::onNavigateToAddPackageTab);
    connect(ui->addPackageButton, &QPushButton::clicked, this, &MainWindow::onAddPackageClicked);
    connect(ui->clearTableButton, &QPushButton::clicked, this, &MainWindow::onClearTable);
    connect(ui->removePackageButton, &QPushButton::clicked, this, &MainWindow::onRemoveSelectedPackages);
    connect(ui->signoutPackageButton, &QPushButton::clicked, this, &MainWindow::onSignOutSelectedPackages);
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// Method for switching tabs
void MainWindow::onNavigateToAddPackageTab() {
    ui->tabWidget->setCurrentIndex(1);
}

// Method for adding packages
void MainWindow::onAddPackageClicked() {
    QString recipientName = ui->recipientNameEdit->text();
    QString courier = ui->courierComboBox->currentText();
    QString trackingNumber = ui->trackingNumberEdit->text();
    QString description = ui->descriptionEdit->toPlainText();

    // Input handling
    if (recipientName.isEmpty() || courier.isEmpty() || trackingNumber.isEmpty() || description.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled!");
        return;
    }

    // Creating package through factory method
    Package pkg = PackageManager::createPackage(recipientName, courier, trackingNumber, description);
    PackageManager::getInstance()->addPackage(pkg);

    // Adding package to table
    int row = ui->packageTable->rowCount();
    ui->packageTable->insertRow(row);
    ui->packageTable->setItem(row, 0, new QTableWidgetItem(pkg.getRecipientName()));
    ui->packageTable->setItem(row, 1, new QTableWidgetItem(pkg.getCourier()));
    ui->packageTable->setItem(row, 2, new QTableWidgetItem(pkg.getTrakingNumber()));
    ui->packageTable->setItem(row, 3, new QTableWidgetItem(pkg.getDescription()));
    ui->packageTable->setItem(row, 4, new QTableWidgetItem(pkg.getStatus()));
    ui->packageTable->setItem(row, 5, new QTableWidgetItem(pkg.getDateReceived().toString("yyyy-MM-dd HH:mm:ss")));

    // Clearing inputs
    ui->recipientNameEdit->clear();
    ui->courierComboBox->setCurrentIndex(0);
    ui->trackingNumberEdit->clear();
    ui->descriptionEdit->clear();

    // Tab switch
    ui->tabWidget->setCurrentIndex(0);

    // Updating status label
    ui->label->setText("Package Added: " + pkg.getTrakingNumber());
}

// Method for signing out selected packages
void MainWindow::onSignOutSelectedPackages() {
    // Confirmation dialog
    if (!showConfirmationDialog("Confirm Sign-Out", "Are you sure you want to sign-out the selected packages?\n\nThis action cannot be undone.")) {
        return;
    }

    // Get all selected rows
    QList<QTableWidgetItem*> selectedItems = ui->packageTable->selectedItems();

    // Condition for when no package is selected
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "No Selection", "Please select rows to sign out.");
        return;
    }

    // Halding for duplicate selection
    QSet<int> rowsToUpdate;
    for (QTableWidgetItem* item : selectedItems) {
        rowsToUpdate.insert(item->row());
    }

    // Updating status of packages
    for (int row : rowsToUpdate) {
        QTableWidgetItem* trackingItem = ui->packageTable->item(row, 4);
        if (trackingItem) {
            QString trackingNumber = trackingItem->text();
            PackageManager::getInstance()->updatePackageStatus(trackingNumber, "Delivered");

            QTableWidgetItem* statusItem = ui->packageTable->item(row, 4);
            if (statusItem) {
                statusItem->setText("Delivered");
            }
        }
    }

    ui->label->setText("Status updated: Delivered.");
}

// Method for removing selected packages
void MainWindow::onRemoveSelectedPackages() {
    // Confirmation dialog
    if (!showConfirmationDialog("Confirm Package Removal", "Are you sure you want to remove the selected packages?\n\nThis action cannot be undone.")) {
        return;
    }

    // Get all selected rows
    QList<QTableWidgetItem*> selectedItems = ui->packageTable->selectedItems();

    // Condition if no package is selected
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "No Selection", "Please select rows to remove.");
        return;
    }

    // Hanlding for duplicate selection
    QSet<int> rowsToRemove;
    for (QTableWidgetItem* item : selectedItems) {
        rowsToRemove.insert(item->row());
    }

    // Removing packages from table
    QList<int> sortedRows = rowsToRemove.values();
    std::sort(sortedRows.begin(), sortedRows.end(), std::greater<int>());

    for (int row : sortedRows) {
        QTableWidgetItem* trackingItem = ui->packageTable->item(row, 2);
        if (trackingItem) {
            QString trackingNumber = trackingItem->text();
            PackageManager::getInstance()->removePackageByTrackingNumber(trackingNumber);
        }
        ui->packageTable->removeRow(row);
    }

    ui->label->setText("Selected packages removed.");
}

// Method for clearing package table and label
void MainWindow::onClearTable() {
    // Confirmation dialog
    if (!showConfirmationDialog("Confirm Table Clear", "Are you sure you want to remove all packages?\n\nThis action cannot be undone.")) {
        return;
    }

    PackageManager::getInstance()->clearAllPackages();

    ui->packageTable->setRowCount(0);
    ui->label->setText("Package table cleared.");
}

// Method to show confirmation dialog
bool MainWindow::showConfirmationDialog(const QString title, const QString message) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, title, message, QMessageBox::Yes | QMessageBox::No);
    return (reply == QMessageBox::Yes);
}
