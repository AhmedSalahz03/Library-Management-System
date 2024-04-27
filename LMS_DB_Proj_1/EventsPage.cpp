#include "EventsPage.h"

EventsPage::EventsPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    int startY = 40; // Initial y-coordinate for the first QLineEdit
    int spacing = 60; 

    eventTitleTF = new QLineEdit(this);
    eventTitleTF->move(20, startY);
    setSizeForLineEdit(eventTitleTF);

    eventDescriptionTF = new QLineEdit(this);
    eventDescriptionTF->move(20, startY + spacing);
    setSizeForLineEdit(eventDescriptionTF);

    eventMaxCapacityTF = new QLineEdit(this);
    eventMaxCapacityTF->move(20, startY + 2 * spacing);
    setSizeForLineEdit(eventMaxCapacityTF);

    eventDateTF = new QDateEdit(this);
    eventDateTF->move(20, startY + 3 * spacing);
    eventDateTF->setCalendarPopup(true);
    eventDateTF->setDate(QDate::currentDate());
    
    eventTimeTF = new QTimeEdit(this);
    eventTimeTF->move(20, startY + 4 * spacing);
    eventTimeTF->setDisplayFormat("hh:mm:ss");
    eventDateTF->setTime(QTime::currentTime());
    
    insertEventBtn = new QPushButton("Insert Data", this);
    insertEventBtn->move(20, startY + 5 * spacing);
    

    // Initialize QSqlTableModel as a member variable
    allEventsTableModel = new QSqlTableModel(this);
    allEventsTableModel->setTable("Eventss"); // Replace with your actual table name
    allEventsTableModel->select(); // Fetch data from the table

    allEventsTable = new QTableView(this);
    allEventsTable->setParent(this); // Set the parent to the MembersPage widget
    allEventsTable->setModel(allEventsTableModel);
    allEventsTable->setGeometry(500, startY, 1000, 900);
    // Enable row selection
    allEventsTable->setSelectionMode(QAbstractItemView::ContiguousSelection);

    allEventsTable->show();

    allEventsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    allEventsTable->setColumnWidth(6, 150);
    allEventsTable->setColumnWidth(7, 150);

    deleteEventBtn = new QPushButton("Delete Event", this);
    deleteEventBtn->move(20, startY + 6 * spacing);

    // Connect the Stylesheet File
    QFile styleFile("stylesheet.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {

        QString styleSheet = QLatin1String(styleFile.readAll());
        eventTitleTF->setStyleSheet(styleSheet);
        eventDescriptionTF->setStyleSheet(styleSheet);
        eventMaxCapacityTF->setStyleSheet(styleSheet);
        eventDateTF->setStyleSheet(styleSheet);
        eventTimeTF->setStyleSheet(styleSheet);
        insertEventBtn->setStyleSheet(styleSheet);
        allEventsTable->setStyleSheet(styleSheet);
        deleteEventBtn->setStyleSheet(styleSheet);
        styleFile.close();


    }

    connect(insertEventBtn, &QPushButton::clicked, this, &EventsPage::addEvent);
    // Connect button's clicked signal to deleteSelectedRow slot
    connect(deleteEventBtn, &QPushButton::clicked, this, [=]() {
        deleteSelectedRow(allEventsTable, allEventsTableModel);
        });
}

EventsPage::~EventsPage()
{}
void EventsPage::addEvent() {
    if(CommonData::getInstance().getType() != "M") {
        QMessageBox::warning(this, "Error", "You are not authorized to add events");
        return;
    }
    // Retrieve data from QLineEdit fields
    QString eventTitleValue = eventTitleTF->text();
    QString eventDescriptionValue = eventDescriptionTF->text();
    QString eventMaxCapacityValue = eventMaxCapacityTF->text();
    QDate eventDateValue = eventDateTF->date();
    QTime eventTimeValue = eventTimeTF->time();
    

    // Prepare the SQL INSERT statement
    QSqlQuery query;
    query.prepare("INSERT INTO Eventss (Title, Descriptionn, MaxCapacity, Datee, Timee, OrganizerID) "
        "VALUES (:EventTitle, :EventDescription, :MaxCapacity, :Datee, :Timee, :OrganizerID)");
    query.bindValue(":EventTitle", eventTitleValue);
    query.bindValue(":EventDescription", eventDescriptionValue);
    query.bindValue(":MaxCapacity", eventMaxCapacityValue);
    query.bindValue(":Datee", eventDateValue);
    query.bindValue(":Timee", eventTimeValue);
    query.bindValue(":OrganizerID", CommonData::getInstance().getUsername());
    
    // Execute the query
    if (query.exec()) {
        qDebug() << "Data inserted successfully";
    }
    else {
        qDebug() << "Error inserting data:" << query.lastError().text();
    }
    allEventsTableModel->select();
    allEventsTable->show();


}
void EventsPage::setSizeForLineEdit(QLineEdit* LineEdit) {
    LineEdit->resize(350, 40);
}
void EventsPage::deleteSelectedRow(QTableView* tableView, QSqlTableModel* tableModel) {
    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();
    // Check if there's at least one selected row
    if (!selectedRows.isEmpty()) {
        // Remove the first selected row
        tableModel->removeRow(selectedRows.first().row());
        // Refresh the model to reflect the changes
        tableModel->select();
    }

}