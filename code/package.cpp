#include "package.h"

// Constructor
Package::Package(QString recipientName, QString courier, QString trackingNumber, QString description) : recipientName(recipientName), courier(courier), trackingNumber(trackingNumber), description(description), dateReceived(QDateTime::currentDateTime()), status("Pending") {}

// Getter methods
QString Package::getRecipientName() const {
    return recipientName;
}

QString Package::getCourier() const {
    return courier;
}

QString Package::getTrakingNumber() const {
    return trackingNumber;
}

QString Package::getDescription() const {
    return description;
}

QDateTime Package::getDateReceived() const {
    return dateReceived;
}

QString Package::getStatus() const {
    return status;
}

// Setter methods
void Package::setStatus(const QString &newStatus) {
    status = newStatus;
}
