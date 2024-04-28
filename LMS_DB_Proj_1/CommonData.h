// CommonData.h - Header file
#ifndef COMMONDATA_H
#define COMMONDATA_H

#include <QString>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
class CommonData {
public:
    static CommonData& getInstance();

    void setUsername(const QString& username);
    QString getUsername() const;

    void setType(const QString& type);
    QString getType() const;

    void setBranchId(const QString& branchId);
    QString getBranchId() const;

private:
    QString username;
    QString type;
    QString branchId;

    CommonData(); // Private constructor for singleton
    CommonData(const CommonData&) = delete; // Prevent copy construction
    CommonData& operator=(const CommonData&) = delete; // Prevent assignment
};

#endif // COMMONDATA_H

