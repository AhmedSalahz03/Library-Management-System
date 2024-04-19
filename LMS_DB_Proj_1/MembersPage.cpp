#include "MembersPage.h"
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

MembersPage::MembersPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    int startY = 20; // Initial y-coordinate for the first QLineEdit
    int spacing = 60; // Spacing between QLineEdit widgets

    firstNameTF = new QLineEdit(this);
    firstNameTF->move(20, startY);
    setSizeForLineEdit(firstNameTF);
    lastNameTF = new QLineEdit(this);
    lastNameTF->move(20, startY + spacing);
    setSizeForLineEdit(lastNameTF);
    phoneTF = new QLineEdit(this);
    phoneTF->move(20, startY + 2 * spacing);
    setSizeForLineEdit(phoneTF);
    streetTF = new QLineEdit(this);
    streetTF->move(20, startY + 3 * spacing);
    setSizeForLineEdit(streetTF);
    cityTF = new QLineEdit(this);
    cityTF->move(20, startY + 4 * spacing);
    setSizeForLineEdit(cityTF);
    zipcodeTF = new QLineEdit(this);
    zipcodeTF->move(20, startY + 5 * spacing);
    setSizeForLineEdit(zipcodeTF);
    emailTF = new QLineEdit(this);
    emailTF->move(20, startY + 6 * spacing);
    setSizeForLineEdit(emailTF);
    insertBtn = new QPushButton("Insert Data", this);
    insertBtn->move(20, startY + 8 * spacing);
    connect(insertBtn, &QPushButton::clicked, this, &MembersPage::addMember);

    // Initialize QSqlTableModel as a member variable
    allMembersModel = new QSqlTableModel(this);
    allMembersModel->setTable("Members"); // Replace with your actual table name
    allMembersModel->select(); // Fetch data from the table

    allMembersTableView = new QTableView(this);
    allMembersTableView->setParent(this); // Set the parent to the MembersPage widget
    allMembersTableView->setModel(allMembersModel);
    allMembersTableView->setGeometry(500, startY , 1000, 900);
    // Enable row selection
    allMembersTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);

    allMembersTableView->show();

    allMembersTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    allMembersTableView->setColumnWidth(6, 150);
    allMembersTableView->setColumnWidth(7, 150);


    deleteMemberBtn = new QPushButton(this);
    deleteMemberBtn->setText("Delete Member");
    deleteMemberBtn->move(300, startY + 8 * spacing);

    
    searchForMemberIdTF = new QLineEdit(this);
    searchForMemberIdBtn = new QPushButton(this);

    searchForMemberIdTF->move(20, startY + 10 * spacing);
    searchForMemberIdBtn->move(20, startY + 11 * spacing);

    searchForMemberIdTF->setPlaceholderText("Member ID");
    searchForMemberIdBtn->setText("Inspect");
   
    fNameInspectL = new QLabel(this);
    lNameInspectL = new QLabel(this);
    emailInspectL = new QLabel(this);
    phoneInspectL = new QLabel(this);
    zipcodeInspectL = new QLabel(this);
    cityInspectL = new QLabel(this);
    streetInspectL = new QLabel(this);
    
    fNameInspectL->move(20, startY);
    lNameInspectL->move(20, startY + spacing);
    phoneInspectL->move(20, startY + 2 * spacing);
    streetInspectL->move(20, startY + 3 * spacing);
    cityInspectL->move(20, startY + 4 * spacing);
    zipcodeInspectL->move(20, startY + 5 * spacing);
    emailInspectL->move(20, startY + 6 * spacing);

    doneInspectingBtn = new QPushButton(this);
    doneInspectingBtn->setText("Back");
    doneInspectingBtn->move(1500, 20);

    fNameInspectL->hide();
    lNameInspectL->hide();
    emailInspectL->hide();
    phoneInspectL->hide();
    zipcodeInspectL->hide();
    cityInspectL->hide();
    streetInspectL->hide();
    doneInspectingBtn->hide();
    



    borrowedBooksofMembersModel = new QSqlTableModel(this);
    borrowedBooksofMembersTableView = new QTableView(this);
    borrowedBooksofMembersTableView->setParent(this); // Set the parent to the MembersPage widget
    borrowedBooksofMembersTableView->setModel(borrowedBooksofMembersModel);
    borrowedBooksofMembersTableView->setGeometry(500, startY, 1000, 900);

    borrowedBooksofMembersTableView->hide();

    // Connect the Stylesheet File
    QFile styleFile("stylesheet.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {

        QString styleSheet = QLatin1String(styleFile.readAll());
        firstNameTF->setStyleSheet(styleSheet);
        lastNameTF->setStyleSheet(styleSheet);
        phoneTF->setStyleSheet(styleSheet);
        emailTF->setStyleSheet(styleSheet);
        zipcodeTF->setStyleSheet(styleSheet);
        cityTF->setStyleSheet(styleSheet);
        streetTF->setStyleSheet(styleSheet);
        insertBtn->setStyleSheet(styleSheet);
        deleteMemberBtn->setStyleSheet(styleSheet);
        allMembersTableView->setStyleSheet(styleSheet);
        searchForMemberIdTF->setStyleSheet(styleSheet);
        searchForMemberIdBtn->setStyleSheet(styleSheet);
        doneInspectingBtn->setStyleSheet(styleSheet);
        styleFile.close();
        

    }

    // Connect button's clicked signal to deleteSelectedRow slot
    connect(deleteMemberBtn, &QPushButton::clicked, this, &MembersPage::deleteSelectedRow);

    connect(searchForMemberIdBtn, &QPushButton::clicked, this, &MembersPage::inspectMember);
	
    connect(doneInspectingBtn, &QPushButton::clicked, this, &MembersPage::backToTableView);

}

MembersPage::~MembersPage()
{}
void MembersPage::addMember() {
    // Retrieve data from QLineEdit fields
    QString firstNameValue = firstNameTF->text();
    QString lastNameValue = lastNameTF->text();
    QString phoneValue = phoneTF->text();
    QString streetValue = streetTF->text();
    QString cityValue = cityTF->text();
    QString zipcodeValue = zipcodeTF->text();
    QString emailValue = emailTF->text();

    // Prepare the SQL INSERT statement
    QSqlQuery query;
    query.prepare("INSERT INTO Members (FirstName, LastName, Phone, Street, City, ZipCode, email) "
        "VALUES (:FirstName, :LastName, :Phone, :Street, :City, :ZipCode, :Email)");
    query.bindValue(":FirstName", firstNameValue);
    query.bindValue(":LastName", lastNameValue);
    query.bindValue(":Phone", phoneValue);
    query.bindValue(":Street", streetValue);
    query.bindValue(":City", cityValue);
    query.bindValue(":ZipCode", zipcodeValue);
    query.bindValue(":Email", emailValue);
    // Execute the query
    if (query.exec()) {
        qDebug() << "Data inserted successfully";
    }
    else {
        qDebug() << "Error inserting data:" << query.lastError().text();
    }
    allMembersModel->select();
    allMembersTableView->show();

}
void MembersPage::setSizeForLineEdit(QLineEdit *LineEdit) {
    LineEdit->resize(350, 40);
}
void MembersPage::deleteSelectedRow() {
    QModelIndexList selectedRows = allMembersTableView->selectionModel()->selectedRows();
    // Remove selected rows from the model in reverse order
    for (int i = selectedRows.count() - 1; i >= 0; --i) {
        allMembersModel->removeRow(selectedRows.at(i).row());
    }
    allMembersModel->select();
    allMembersTableView->show();
    
}
void MembersPage::inspectMember() {
    QString memberID = searchForMemberIdTF->text();
    allMembersTableView->hide();
    QString fName, lName, email, phone, zipcode, street, city; // Example attributes

    // Execute a SQL query to select all attributes corresponding to the member ID
    QSqlQuery query;
    query.prepare("SELECT FirstName, LastName, Street, City, ZipCode, Email, Phone FROM Members WHERE MemberID = ?");
    query.addBindValue(memberID);
    if (query.exec() && query.next()) {
        // Retrieve the attributes from the query result
        fName = query.value(0).toString();
        lName = query.value(1).toString();
        street = query.value(2).toString();
        city = query.value(3).toString();
        zipcode = query.value(4).toString();
        email = query.value(5).toString();
        phone = query.value(6).toString();

    }
    else {
        // Handle the case where the query fails or no result is found
        // For simplicity, set default values or handle errors
        QDialog 
        fName = "Unknown";
        lName = "Unknown";
        email = "Unknown";
        phone = "Unknown";
    }

    QString query2 = "SELECT b.CopyID, BookName, StartDate, DueDate FROM Books b, Borrows bs WHERE MemberID = :memberId AND b.CopyID = bs.CopyID"; // Example query

    // Prepare the query
    QSqlQuery q2;
    q2.prepare(query2);
   
    // Bind value to the placeholder
    q2.bindValue(":memberId", memberID); // Example value
    borrowedBooksofMembersModel->setQuery(query2);
    // Execute the query
    if (q2.exec()) {
        // Set the query to the model
        borrowedBooksofMembersModel->setQuery(q2);

        // Check for errors
        if (borrowedBooksofMembersModel->lastError().isValid()) {
            qDebug() << "Error setting query to model:" << borrowedBooksofMembersModel->lastError().text();
        }
        else {
            // The query was successful, now you can use the model to display data
            // For example, you can set this model to a QTableView
            
            borrowedBooksofMembersTableView->setModel(borrowedBooksofMembersModel);
            borrowedBooksofMembersTableView->show();
        }
    }
    else {
        qDebug() << "Error executing query:" << q2.lastError().text();
    }

    // Update the text of the QLabel to display the attributes
    fNameInspectL->setText("First Name: " + fName);
    lNameInspectL->setText("Last Name: " + lName);
    streetInspectL->setText("Street: " + street);
    cityInspectL->setText("City: " + city);
    zipcodeInspectL->setText("Zipcode: " + zipcode);
    phoneInspectL->setText("Phone: " + phone);
    emailInspectL->setText("Email: " + email);

    fNameInspectL->show();
    lNameInspectL->show();
    emailInspectL->show();
    phoneInspectL->show();
    zipcodeInspectL->show();
    cityInspectL->show();
    streetInspectL->show();
    doneInspectingBtn->show();
    borrowedBooksofMembersTableView->show();

    firstNameTF->hide();
    lastNameTF->hide();
    phoneTF->hide();
    streetTF->hide();
    cityTF->hide();
    zipcodeTF->hide();
    emailTF->hide();
    insertBtn->hide();
    deleteMemberBtn->hide();
    searchForMemberIdBtn->hide();
    searchForMemberIdTF->hide();


}
void MembersPage::backToTableView() {
    fNameInspectL->hide();
    lNameInspectL->hide();
    emailInspectL->hide();
    phoneInspectL->hide();
    zipcodeInspectL->hide();
    cityInspectL->hide();
    streetInspectL->hide();
    doneInspectingBtn->hide();
    borrowedBooksofMembersTableView->hide();

    allMembersTableView->show();
    firstNameTF->show();
    lastNameTF->show();
    phoneTF->show();
    streetTF->show();
    cityTF->show();
    zipcodeTF->show();
    emailTF->show();
    insertBtn->show();
    deleteMemberBtn->show();
    searchForMemberIdBtn->show();
    searchForMemberIdTF->show();
}