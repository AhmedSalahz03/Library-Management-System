// CommonData.cpp - Implementation file
#include "CommonData.h"

CommonData::CommonData() {}

CommonData& CommonData::getInstance() {
    static CommonData instance; // Singleton instance
    return instance;
}

void CommonData::setUsername(const QString& username) {
    this->username = username;
}

QString CommonData::getUsername() const {
    return username;
}

void CommonData::setType(const QString& type) {
    this->type = type;
}

QString CommonData::getType() const {
    return type;
}
