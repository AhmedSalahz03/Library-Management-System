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

QString CommonData::getBranchId() const {
    if(CommonData::getInstance().getType() == "L") {
        
    
        // Prepare the query to call the SQL function
        QString librarianId = CommonData::getInstance().getUsername();
        QSqlQuery query;
        query.prepare("SELECT dbo.GetBranchIdByLibrarianId(:librarianId) AS BranchId");
        query.bindValue(":librarianId", librarianId); // Bind the LibrarianID parameter

        // Execute the query
        if (query.exec()) {
            // Check if the query returned a result
            if (query.next()) {
                // Retrieve the BranchID from the result
                QString branchId = query.value("BranchId").toString();
                return branchId;
                // Now you have the BranchID associated with the LibrarianID
            }
            else {
                // The query didn't return any result
                qDebug() << "No branch ID found for librarian ID:" << librarianId;
            }
        }
        else {
            // The query execution failed
            qDebug() << "Error executing query:" << query.lastError().text();
        }
    }
    else if(CommonData::getInstance().getType() == "M") {
        // Retrieve the ManagerID
        QString managerId = CommonData::getInstance().getUsername();
        QSqlQuery query;
        query.prepare("SELECT dbo.GetBranchIDFromManagerID(:managerId) AS BranchID");
        query.bindValue(":managerId", managerId);

        // Execute the query
        if (query.exec()) {
            // Check if the query returned a result
            if (query.next()) {
                // Retrieve the BranchID from the result
                QString branchId = query.value("BranchID").toString();
                return branchId;
                // Now you have the BranchID associated with the ManagerID
            }
            else {
                // The query didn't return any result
                qDebug() << "No branch ID found for manager ID:" << managerId;
            }
        }
        else {
            // The query execution failed
            qDebug() << "Error executing query:" << query.lastError().text();
        }
    }
}