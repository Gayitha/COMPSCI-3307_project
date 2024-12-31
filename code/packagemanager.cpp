#include "packagemanager.h"

// Static instance for singleton
PackageManager* PackageManager::instance = nullptr;

// Singtleton method for getting instance
PackageManager* PackageManager::getInstance() {
    if (!instance) {
        instance = new PackageManager();
    }
    return instance;
}

// Method for adding package to internal list
void PackageManager::addPackage(const Package &package) {
    packages.append(package);
}

// Factory method for creating package objects
Package PackageManager::createPackage(const QString &recipientName, const QString &courier, const QString &trackingNumber, const QString &description) {
    return Package(recipientName, courier, trackingNumber, description);
}

// Remove package from list
void PackageManager::removePackageByTrackingNumber(const QString& trackingNumber) {
    for (int i = 0; i < packages.size(); ++i) {
        if (packages[i].getTrakingNumber() == trackingNumber) {
            packages.removeAt(i);
            break;
        }
    }
}

// Remove all packages from list
void PackageManager::clearAllPackages() {
    packages.clear();
}

// Updates package status in the list
void PackageManager::updatePackageStatus(const QString& trackingNumber, const QString& newStatus) {
    for (Package& pkg : packages) {
        if (pkg.getTrakingNumber() == trackingNumber) {
            pkg.setStatus(newStatus);
            break;
        }
    }
}
