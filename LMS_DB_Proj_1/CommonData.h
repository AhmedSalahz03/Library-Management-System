// CommonData.h - Header file
#ifndef COMMONDATA_H
#define COMMONDATA_H

#include <QString>

class CommonData {
public:
    static CommonData& getInstance();

    void setUsername(const QString& username);
    QString getUsername() const;

    void setType(const QString& type);
    QString getType() const;

private:
    QString username;
    QString type;

    CommonData(); // Private constructor for singleton
    CommonData(const CommonData&) = delete; // Prevent copy construction
    CommonData& operator=(const CommonData&) = delete; // Prevent assignment
};

#endif // COMMONDATA_H

