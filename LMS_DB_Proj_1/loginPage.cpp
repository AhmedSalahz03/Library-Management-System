// loginpage.cpp
#include "loginpage.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QtDebug>
#include <qsql.h>
#include <qsqltablemodel.h>
#include <qsqlquerymodel.h>
#include <qwidget.h>
#include <QTableView>
#include <QVBoxLayout>
#include <QModelIndexList>
#include <QHeaderView>
#include <QLineEdit>
#include <QPushButton>
#include <QtCore/QFile>
#include <qtableview.h>
#include <QSqlTableModel>
#include <QLabel>
#include <qmessagebox.h>
#include <QDateEdit>

LoginPage::LoginPage(QWidget* parent) : QWidget(parent)
{
    int startX = 20;
    int startY = 40;
    int spacing = 60;
    int center = 650;


    title = new QLabel("Library Management System", this);
    title->move(startX + center-100, startY+100);
    QFont font = title->font();
    font.setPointSize(20);
    title->setFont(font);

    userIdTF = new QLineEdit(this);
    passwordTF = new QLineEdit(this);
    passwordTF->setEchoMode(QLineEdit::Password);
    loginBtn = new QPushButton("Login", this);
    librarianId = new QString();

    userIdTF->move(startX + center, startY + 5 * spacing);
    passwordTF->move(startX + center, startY + 6 * spacing);
    loginBtn->move(startX + center, startY + 7 * spacing);

    // Connect the Stylesheet File
    QFile styleFile("stylesheet.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {

        QString styleSheet = QLatin1String(styleFile.readAll());
        userIdTF->setStyleSheet(styleSheet);
        passwordTF->setStyleSheet(styleSheet);
        loginBtn->setStyleSheet(styleSheet);

        styleFile.close();

    }

    connect(loginBtn, &QPushButton::clicked, this, &LoginPage::attemptLogin);
}

void LoginPage::attemptLogin()
{
    // Assuming you have QLineEdit fields named idInput and passwordInput
    QString inputId = userIdTF->text();
    QString inputPassword = passwordTF->text();

    // Check login for Librarians
    QSqlQuery queryLibrarians;
    queryLibrarians.prepare("SELECT * FROM Librarians WHERE LibrarianID = ? AND passwordD = ?");
    queryLibrarians.addBindValue(inputId);
    queryLibrarians.addBindValue(inputPassword);
    queryLibrarians.exec();

    if (queryLibrarians.next()) {
        // If the query returned a result, then the login is successful
        CommonData::getInstance().setUsername(inputId);
        CommonData::getInstance().setType("L");
        emit loginSuccessful();
        return;
    }

    // Check login for Managers
    QSqlQuery queryManagers;
    queryManagers.prepare("SELECT * FROM Managers WHERE ManagerID = ? AND passwordD = ?");
    queryManagers.addBindValue(inputId);
    queryManagers.addBindValue(inputPassword);
    queryManagers.exec();

    if (queryManagers.next()) {
        // If the query returned a result, then the login is successful
        CommonData::getInstance().setUsername(inputId);
        CommonData::getInstance().setType("M");
        emit loginSuccessful();
        return;
    }

    // If neither query returned a result, display an error message
    QMessageBox::warning(this, "Wrong Login Info", "Wrong ID or Password");

}
QString* LoginPage::getLibrarianId() {
    return librarianId;
}
