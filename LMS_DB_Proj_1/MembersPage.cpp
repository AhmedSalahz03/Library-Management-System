#include "MembersPage.h"
#include "CommonData.h"
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
    int startY = 40; // Initial y-coordinate for the first QLineEdit
    int spacing = 60; // Spacing between QLineEdit widgets
    addNewMemberL = new QLabel("Add New Member", this);
    addNewMemberL->move(20, 10);
    QFont font = addNewMemberL->font();
    font.setPointSize(15);
    font.setBold(true);
    addNewMemberL->setFont(font);

    firstNameTF = new QLineEdit(this);
    firstNameTF->move(20, startY);
    firstNameTF->setPlaceholderText("First Name");
    setSizeForLineEdit(firstNameTF);
    lastNameTF = new QLineEdit(this);
    lastNameTF->move(20, startY + spacing);
    lastNameTF->setPlaceholderText("Last Name");
    setSizeForLineEdit(lastNameTF);
    phoneTF = new QLineEdit(this);
    phoneTF->move(20, startY + 2 * spacing);
    phoneTF->setPlaceholderText("Phone");
    setSizeForLineEdit(phoneTF);
    streetTF = new QLineEdit(this);
    streetTF->move(20, startY + 3 * spacing);
    streetTF->setPlaceholderText("Street");
    setSizeForLineEdit(streetTF);
    cityTF = new QLineEdit(this);
    cityTF->move(20, startY + 4 * spacing);
    cityTF->setPlaceholderText("City");
    setSizeForLineEdit(cityTF);
    zipcodeTF = new QLineEdit(this);
    zipcodeTF->move(20, startY + 5 * spacing);
    zipcodeTF->setPlaceholderText("Zipcode");
    setSizeForLineEdit(zipcodeTF);
    emailTF = new QLineEdit(this);
    emailTF->move(20, startY + 6 * spacing);
    emailTF->setPlaceholderText("Email");
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
    allMembersTableView->setGeometry(500, startY , 1000, 700);
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
    
    QFont fontInspect = fNameInspectL->font();
    fontInspect.setPointSize(12);
    fontInspect.setBold(true);
    fNameInspectL->setFont(fontInspect);
    lNameInspectL->setFont(fontInspect);
    emailInspectL->setFont(fontInspect);
    phoneInspectL->setFont(fontInspect);
    zipcodeInspectL->setFont(fontInspect);
    cityInspectL->setFont(fontInspect);
    streetInspectL->setFont(fontInspect);


    fNameInspectL->move(20, startY);
    lNameInspectL->move(20, startY + spacing);
    phoneInspectL->move(20, startY + 2 * spacing);
    streetInspectL->move(20, startY + 3 * spacing);
    cityInspectL->move(20, startY + 4 * spacing);
    zipcodeInspectL->move(20, startY + 5 * spacing);
    emailInspectL->move(20, startY + 6 * spacing);

    fNameInspectL->resize(300, 40);
    lNameInspectL->resize(300, 40);
    phoneInspectL->resize(300, 40);
    streetInspectL->resize(300, 40);
    cityInspectL->resize(300, 40);
    zipcodeInspectL->resize(300, 40);
    emailInspectL->resize(300, 40);

    doneInspectingBtn = new QPushButton(this);
    doneInspectingBtn->setText("Back");
    doneInspectingBtn->move(1300, 20);

    fNameInspectL->hide();
    lNameInspectL->hide();
    emailInspectL->hide();
    phoneInspectL->hide();
    zipcodeInspectL->hide();
    cityInspectL->hide();
    streetInspectL->hide();
    doneInspectingBtn->hide();
    
    lendCopyIdTF = new QLineEdit(this);
    lendCopyIdTF->setPlaceholderText("Copy ID");
    lendStartDate = new QDateEdit(this);
    lendDueDate = new QDateEdit(this);
    lendBtn = new QPushButton(this);
    endLendBtn = new QPushButton(this);

    lendDueDate->setCalendarPopup(true);
    lendStartDate->setCalendarPopup(true);

    lendCopyIdTF->move(1000, startY);
    lendStartDate->move(1000, startY + spacing);
    lendDueDate->move(1000, startY + 2 * spacing);
    lendBtn->move(1000, startY + 3 * spacing);
    endLendBtn->move(1200, startY + 3 * spacing);

    lendStartDate->setDate(QDate::currentDate());
    lendDueDate->setDate(QDate::currentDate());
    lendBtn->setText("Lend");
    endLendBtn->setText("End Lend");

    lendCopyIdTF->hide();
    lendDueDate->hide();
    lendStartDate->hide();
    lendBtn->hide();
    endLendBtn->hide();

    borrowedBooksofMembersModel = new QSqlTableModel(this);
    borrowedBooksofMembersTableView = new QTableView(this);
    borrowedBooksofMembersTableView->setParent(this); // Set the parent to the MembersPage widget
    borrowedBooksofMembersTableView->setModel(borrowedBooksofMembersModel);
    borrowedBooksofMembersTableView->setGeometry(300, startY, 500, 400);
    borrowedBooksofMembersTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    borrowedBooksofMembersTableView->hide();

    attendedEventsModel = new QSqlTableModel(this);
    attendedEventsTable = new QTableView(this);
    attendedEventsTable->setParent(this); // Set the parent to the MembersPage widget
    attendedEventsTable->setModel(attendedEventsModel);
    attendedEventsTable->setGeometry(300, startY+400, 500, 400);
    attendedEventsTable->setSelectionMode(QAbstractItemView::ContiguousSelection);
    attendedEventsTable->hide();

    eventIdTF = new QLineEdit(this);
    eventIdTF->move(1000, startY + 8 * spacing);
    eventIdTF->setPlaceholderText("Event ID");
    addMemberToEventBtn = new QPushButton(this);
    addMemberToEventBtn->setText("Add Member to Event");
    addMemberToEventBtn->move(1000, startY + 9 * spacing);
    addMemberToEventBtn->hide();
    eventIdTF->hide();

    deleteMemberFromEventBtn = new QPushButton(this);
    deleteMemberFromEventBtn->setText("Delete Member from Event");
    deleteMemberFromEventBtn->move(1000, startY + 10 * spacing);
    deleteMemberFromEventBtn->hide();

    //fineModel = new QSqlTableModel(this);
    //fineModel->setTable("Fines");
    //fineModel->select();
    //fineTable = new QTableView(this);
    //fineTable->setParent(this);
    //fineTable->setModel(fineModel);
    //fineTable->setGeometry(800, startY + 300, 300, 100);
    //fineTable->setSelectionMode(QAbstractItemView::ContiguousSelection);
    //fineTable->hide();

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
        lendCopyIdTF->setStyleSheet(styleSheet);
        endLendBtn->setStyleSheet(styleSheet);
        lendBtn->setStyleSheet(styleSheet);
        borrowedBooksofMembersTableView->setStyleSheet(styleSheet);
        attendedEventsTable->setStyleSheet(styleSheet);
        eventIdTF->setStyleSheet(styleSheet);
        addMemberToEventBtn->setStyleSheet(styleSheet);
        deleteMemberFromEventBtn->setStyleSheet(styleSheet);
        //fineTable->setStyleSheet(styleSheet);

        styleFile.close();
        

    }

    // Connect button's clicked signal to deleteSelectedRow slot
    connect(deleteMemberBtn, &QPushButton::clicked, this, [=]() {
        deleteSelectedRow(allMembersTableView, allMembersModel);
        });
    connect(searchForMemberIdBtn, &QPushButton::clicked, this, &MembersPage::inspectMember);
	
    connect(doneInspectingBtn, &QPushButton::clicked, this, &MembersPage::backToTableView);

    connect(lendBtn, &QPushButton::clicked, this, &MembersPage::lend);
    
    // connect(endLendBtn, &QPushButton::clicked, this, [=]() {
    //    deleteSelectedRow(borrowedBooksofMembersTableView, borrowedBooksofMembersModel);
    //    });
    connect(endLendBtn, &QPushButton::clicked, this, &MembersPage::endLendInspect);

    // Connect the dataChanged signal to a custom slot
    connect(allMembersModel, &QSqlTableModel::dataChanged, this, &MembersPage::handleDataChanged);

    connect(addMemberToEventBtn, &QPushButton::clicked, this, &MembersPage::addMemberToEvent);

    connect(deleteMemberFromEventBtn, &QPushButton::clicked, this, &MembersPage::deleteMemberFromEvent);
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
void MembersPage::deleteSelectedRow(QTableView* tableView, QSqlTableModel* tableModel) {
    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();
    // Check if there's at least one selected row
    if (!selectedRows.isEmpty()) {
        // Remove the first selected row
        tableModel->removeRow(selectedRows.first().row());
        // Refresh the model to reflect the changes
        tableModel->select();
    }

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
        QMessageBox::warning(this, "Not Found", "This Member doesn't exist");
        backToTableView();
        return;
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

    QString query3 = "SELECT e.EventID, Title, Datee FROM Eventss e, Attends a WHERE MemberID = :memberId AND e.EventID = a.EventID"; // Example query
    QSqlQuery q3;
    q3.prepare(query3);
    q3.bindValue(":memberId", memberID); // Example value
    attendedEventsModel->setQuery(query3);
    if (q3.exec()) {
        attendedEventsModel->setQuery(q3);
        if (attendedEventsModel->lastError().isValid()) {
            qDebug() << "Error setting query to model:" << attendedEventsModel->lastError().text();
        }
        else {
            attendedEventsTable->setModel(attendedEventsModel);
            attendedEventsTable->show();
        }
    }
    else {
        qDebug() << "Error executing query:" << q3.lastError().text();
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
    lendCopyIdTF->show();
    lendDueDate->show();
    lendStartDate->show();
    lendBtn->show();
    endLendBtn->show();
    attendedEventsTable->show();
    eventIdTF->show();
    addMemberToEventBtn->show();
    deleteMemberFromEventBtn->show();
    //fineTable->show();

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
    addNewMemberL->hide();


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
    lendCopyIdTF->hide();
    lendDueDate->hide();
    lendStartDate->hide();
    lendBtn->hide();
    endLendBtn->hide();
    attendedEventsTable->hide();
    eventIdTF->hide();
    addMemberToEventBtn->hide();
    deleteMemberFromEventBtn->hide();
    //fineTable->hide();

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
    addNewMemberL->show();
}
void MembersPage::lend() {
    QString copyIdLend = lendCopyIdTF->text();
    QString memberIdLend = searchForMemberIdTF->text();
    QDate startDateLend = lendStartDate->date();
    QDate dueDateLend = lendDueDate->date();

    
    QString currentBranchId = getBranchId();

    QSqlQuery chkBookBranch;
    chkBookBranch.prepare("SELECT b.CopyID FROM Books b, Supplies s WHERE b.CopyID = s.CopyID AND b.CopyID = :copyId AND s.BranchID = :branchId");
    chkBookBranch.bindValue(":copyId", copyIdLend);
    chkBookBranch.bindValue(":branchId", currentBranchId);

    chkBookBranch.exec();

    if (chkBookBranch.next()) { // Check if there is a result
        // Book found in this branch, proceed with lending
    }
    else {
        QMessageBox::warning(this, "Not in this Branch", "The book is not available in this branch.");
        return;
    }
  
    


    // Prepare the SQL query to check if the copyId exists in the 'Borrows' table
    QString chkQuery = "SELECT COUNT(*) FROM Borrows WHERE CopyID = :copyId";

    // Prepare the query
    QSqlQuery checkQuery;
    checkQuery.prepare(chkQuery);

    // Bind the copyId value to the query
    checkQuery.bindValue(":copyId", copyIdLend);

    // Execute the query
    if (checkQuery.exec()) {
        // Check if any rows were returned
        if (checkQuery.next()) {
            int count = checkQuery.value(0).toInt();
            if (count > 0) {
                // The book is already borrowed
                qDebug() << "Book with copyId" << copyIdLend << "is already borrowed.";
                // Inform the user accordingly (e.g., show a message)
                QMessageBox::warning(this, "Already Lended", "This book is already lended");
                return;
            }
            else {
                // The book is available for borrowing
                qDebug() << "Book with copyId" << copyIdLend << "is available for borrowing.";
                // Proceed with the insertion logic
            }
        }
    }
    else {
        // Error executing the query
        qDebug() << "Error executing query:" << checkQuery.lastError().text();
    }


    QString query3 = "INSERT INTO Borrows (MemberID, CopyID, StartDate, DueDate) VALUES (:memberId, :copyId, :startDate, :dueDate)";
    // Prepare the query
    QSqlQuery q3;
    q3.prepare(query3);

    // Bind values to the placeholders
    q3.bindValue(":memberId", memberIdLend);
    q3.bindValue(":copyId", copyIdLend);
    q3.bindValue(":startDate", startDateLend);
    q3.bindValue(":dueDate", dueDateLend);

    // Execute the query
    if (q3.exec()) {
        // Insertion successful
        qDebug() << "Data inserted into Borrows table";
    }
    else {
        // Insertion failed
        qDebug() << "Error inserting data into Borrows table:" << q3.lastError().text();
    }
    inspectMember();
}
void MembersPage::endLendInspect() {
    // Assuming you have a QTableView named tableView
    QItemSelectionModel* select = borrowedBooksofMembersTableView->selectionModel();

    // Get selected rows
    QModelIndexList rows = select->selectedRows();

    // Since there's only one row, directly access it
    QModelIndex index = rows.at(0);
    
    QVariant data = borrowedBooksofMembersTableView->model()->data(index.siblingAtColumn(0));

    // Now you can use the data
    QString copyId =  data.toString();

    QString endLendQuery = "DELETE FROM Borrows WHERE CopyID = ?";
    QSqlQuery q4;
    q4.prepare(endLendQuery);
    q4.addBindValue(copyId);
    if(!q4.exec()) {
        qDebug() << "Error executing query: " << q4.lastError();
    }

    inspectMember();
}
// Slot to handle the dataChanged signal
void MembersPage::handleDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles)
{
    // Check if the edited cell falls within the range of the dataChanged signal
    if (topLeft.isValid() && bottomRight.isValid()) {
        // Check if the edited cell is in the first column (column index 0)
        if (topLeft.column() == 0) {
            qDebug() << "Cell edited in the first column at row:" << topLeft.row();
            // Additional processing if needed

            // Refresh the table
            allMembersModel->select();
        }
    }
}
void MembersPage::addMemberToEvent(){
    
    QString branchId = getBranchId();

    QString memberID = searchForMemberIdTF->text();
    QString eventID = eventIdTF->text();


    // Count the number of attendees
    QSqlQuery countQuery;
    countQuery.prepare("SELECT COUNT(*) FROM Attends WHERE EventID = ?");
    countQuery.addBindValue(eventID);
    countQuery.exec();
    countQuery.next();
    int attendeeCount = countQuery.value(0).toInt();

    // Get the max capacity of the event
    QSqlQuery capacityQuery;
    capacityQuery.prepare("SELECT MaxCapacity FROM Eventss WHERE EventID = ?");
    capacityQuery.addBindValue(eventID);
    capacityQuery.exec();
    capacityQuery.next();
    int maxCapacity = capacityQuery.value(0).toInt();

    // Check if the event is at full capacity
    if (attendeeCount >= maxCapacity) {
        // The event is at full capacity
        QMessageBox::warning(this, "Error", "The event is at full capacity.");
        return;
    } else {
        // The event is not at full capacity, proceed with adding the member to the event
        QString query = "INSERT INTO Attends (MemberID, EventID, BranchID) VALUES (:memberId, :eventId, :branchId)";
        QSqlQuery q;
        q.prepare(query);
        q.bindValue(":memberId", memberID);
        q.bindValue(":eventId", eventID);
        q.bindValue(":branchId", branchId);
        if(q.exec()){
            qDebug() << "Data inserted successfully";
        }
        else{
            qDebug() << "Error inserting data:" << q.lastError().text();
            QMessageBox::warning(this, "Error", "Unable to add member to event.");
        }
        inspectMember();
    }

    
   
   

}
QString MembersPage::getBranchId() {
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
void MembersPage::deleteMemberFromEvent(){
    QItemSelectionModel* select = attendedEventsTable->selectionModel();
    QModelIndexList rows = select->selectedRows();
    QModelIndex index = rows.at(0);
    QVariant data = attendedEventsTable->model()->data(index.siblingAtColumn(0));
    QString eventID = data.toString();
    QString memberID = searchForMemberIdTF->text();
    QString query = "DELETE FROM Attends WHERE MemberID = :memberId AND EventID = :eventId";
    QSqlQuery q;
    q.prepare(query);
    q.bindValue(":memberId", memberID);
    q.bindValue(":eventId", eventID);
    if(q.exec()){
        qDebug() << "Data deleted successfully";
    }
    else{
        qDebug() << "Error deleting data:" << q.lastError().text();
        QMessageBox::warning(this, "Error", "Unable to delete member from event.");
    }
    inspectMember();
}