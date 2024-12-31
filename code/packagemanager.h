#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include "package.h"
#include <QList>
#include <QString>

class PackageManager
{
public:
    static PackageManager* getInstance();

    void addPackage(const Package &package);
    static Package createPackage(const QString &recipientName, const QString &courier, const QString &trackingNumber, const QString &description);

    void removePackageByTrackingNumber(const QString& trackingNumber);
    void updatePackageStatus(const QString& trackingNumber, const QString& newStatus);
    void clearAllPackages();

private:
    PackageManager() = default;
    ~PackageManager() = default;

    PackageManager(const PackageManager&) = delete;
    PackageManager& operator=(const PackageManager&) = delete;

    static PackageManager* instance;

    QList<Package> packages;
};


#endif // PACKAGEMANAGER_H
