#ifndef PACKAGE_H
#define PACKAGE_H

#include <QString>
#include <QDateTime>

class Package
{
public:
    Package(QString recipientName, QString courier, QString trackingNumber, QString description);

    QString getRecipientName() const;
    QString getCourier() const;
    QString getTrakingNumber() const;
    QString getDescription() const;
    QDateTime getDateReceived() const;
    QString getStatus() const;

    void setStatus(const QString &newStatus);

private:
    QString recipientName;
    QString courier;
    QString trackingNumber;
    QString description;
    QDateTime dateReceived;
    QString status;
};

#endif // PACKAGE_H
