#include "AuthorsPublishersPage.h"

AuthorsPublishersPage::AuthorsPublishersPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	authorsModel = new QSqlTableModel(this);
	authorsModel->setTable("Authors");
	authorsModel->select();
	authorsTableView = new QTableView(this);
	authorsTableView->setParent(this); // Set the parent to the AuthorsPublishersPage widget
	authorsTableView->setModel(authorsModel);
	authorsTableView->setGeometry(20, 20, 500, 400);
	authorsTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);

	authorFirstNameTF = new QLineEdit(this);
	authorFirstNameTF->move(20, 450);
	authorFirstNameTF->setPlaceholderText("First Name");
	authorLastNameTF = new QLineEdit(this);
	authorLastNameTF->move(20, 500);
	authorLastNameTF->setPlaceholderText("Last Name");
	addAuthorBtn = new QPushButton("Add Author", this);
	addAuthorBtn->move(20, 550);
	deleteAuthorBtn = new QPushButton("Delete Author", this);
	deleteAuthorBtn->move(20, 600);

	publishersModel = new QSqlTableModel(this);
	publishersModel->setTable("Publishers");
	publishersModel->select();
	publishersTableView = new QTableView(this);
	publishersTableView->setParent(this); // Set the parent to the AuthorsPublishersPage widget
	publishersTableView->setModel(publishersModel);
	publishersTableView->setGeometry(600, 20, 500, 400);
	publishersTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);

	publisherFirstNameTF = new QLineEdit(this);
	publisherFirstNameTF->setPlaceholderText("First Name");
	publisherFirstNameTF->move(600, 450);
	publisherLastNameTF = new QLineEdit(this);
	publisherLastNameTF->setPlaceholderText("Last Name");
	publisherLastNameTF->move(600, 500);
	addPublisherBtn = new QPushButton("Add Publisher", this);
	addPublisherBtn->move(600, 550);
	deletePublisherBtn = new QPushButton("Delete Publisher", this);
	deletePublisherBtn->move(600, 600);

    // Connect the Stylesheet File
    QFile styleFile("stylesheet.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {

        QString styleSheet = QLatin1String(styleFile.readAll());
        authorsTableView->setStyleSheet(styleSheet);
		publishersTableView->setStyleSheet(styleSheet);
		authorFirstNameTF->setStyleSheet(styleSheet);
		authorLastNameTF->setStyleSheet(styleSheet);
		addAuthorBtn->setStyleSheet(styleSheet);
		publisherFirstNameTF->setStyleSheet(styleSheet);
		publisherLastNameTF->setStyleSheet(styleSheet);
		addPublisherBtn->setStyleSheet(styleSheet);
		deleteAuthorBtn->setStyleSheet(styleSheet);
		deletePublisherBtn->setStyleSheet(styleSheet);
        
        styleFile.close();


    }
	connect(addAuthorBtn, &QPushButton::clicked, this, &AuthorsPublishersPage::addAuthor);
	connect(addPublisherBtn, &QPushButton::clicked, this, &AuthorsPublishersPage::addPublisher);
	connect(deleteAuthorBtn, &QPushButton::clicked, this, [=]() {
		
		deleteSelectedRow(authorsModel, authorsTableView);
        });
	connect(deletePublisherBtn, &QPushButton::clicked, this, [=]() {
		deleteSelectedRow(publishersModel, publishersTableView);
		});
}

AuthorsPublishersPage::~AuthorsPublishersPage()
{}
void AuthorsPublishersPage::addAuthor() {
	if(CommonData::getInstance().getType() != "M") {
		QMessageBox::information(this, "Error", "You do not have permission to add an author");
		return;
	}
	QSqlQuery query;
	query.prepare("INSERT INTO Authors (FirstName, LastName) VALUES (:FirstName, :LastName)");
	query.bindValue(":FirstName", authorFirstNameTF->text());
	query.bindValue(":LastName", authorLastNameTF->text());

	

    
    // Execute the query
    if (query.exec()) {
        qDebug() << "Data inserted successfully";
    }
    else {
        qDebug() << "Error inserting data:" << query.lastError().text();
    }
    authorsModel->select();
    authorsTableView->show();
}
void AuthorsPublishersPage::addPublisher() {
	if(CommonData::getInstance().getType() != "M") {
		QMessageBox::information(this, "Error", "You do not have permission to add a publisher");
		return;
	}
	QSqlQuery query;
	query.prepare("INSERT INTO Publishers (FirstName, LastName) VALUES (:FirstName, :LastName)");
	query.bindValue(":FirstName", publisherFirstNameTF->text());
	query.bindValue(":LastName", publisherLastNameTF->text());

	

	// Execute the query
	if (query.exec()) {
		qDebug() << "Data inserted successfully";
	}
	else {
		qDebug() << "Error inserting data:" << query.lastError().text();
	}
	publishersModel->select();
	publishersTableView->show();
}
void AuthorsPublishersPage::deleteSelectedRow(QSqlTableModel* tableModel, QTableView* tableView) {
    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();
    // Check if there's at least one selected row
    if (!selectedRows.isEmpty()) {
        // Remove the first selected row
        tableModel->removeRow(selectedRows.first().row());
        // Refresh the model to reflect the changes
        tableModel->select();
    }

}
