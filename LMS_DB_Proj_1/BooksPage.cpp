#include "BooksPage.h"
#include "CommonData.h"
#include <qbuttongroup.h>

BooksPage::BooksPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	int startX = 20;
	int startY = 40;
	int spacing = 60;

	searchLabel = new QLabel("Search Results...", this);
	searchLabel->move(200, startY + 70);
	QFont font = searchLabel->font();
	font.setPointSize(15);
	font.setBold(true);
	searchLabel->setFont(font);

	allBooksLabel = new QLabel("All Books", this);
	allBooksLabel->move(700, startY + 70);
	allBooksLabel->setFont(font);

	filterLabel = new QLabel("Filter By:", this);
	filterLabel->move(startX+200, 0);
	filterLabel->setFont(font);


	searchForBookTF = new QLineEdit(this);
	searchedBookTableModel = new QSqlTableModel(this);
	searchedBookTableView = new QTableView(this);
	searchBtn = new QPushButton(this);

	searchForBookTF->move(startX, startY);
	searchForBookTF->setPlaceholderText("Search for a book");
	searchForBookTF->setFixedWidth(160);

	searchedBookTableView->setParent(this); // Set the parent to the MembersPage widget
	searchedBookTableView->setModel(searchedBookTableModel);
	searchedBookTableView->setGeometry(200, startY+100, 450, 500);
	searchedBookTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
	
	searchBtn->move(startX, startY + spacing);
	searchBtn->setText("Search");

	bookNameTF = new QLineEdit(this);
	authorIdTF = new QLineEdit(this);
	editionTF = new QLineEdit(this);
	publisherIdTF = new QLineEdit(this);
	noOfPagesTF = new QLineEdit(this);
	languageCB = new QComboBox(this);
	noOfCopiesTF = new QLineEdit(this);
	category1CB = new QComboBox(this);
	category2CB = new QComboBox(this);
	supplierIdTF = new QLineEdit(this);
	newBatchBtn = new QPushButton(this);
	addBatchBtn = new QPushButton(this);
	backBtn = new QPushButton(this);

	bookNameTF->move(startX, startY);
	authorIdTF->move(startX, startY + spacing);
	editionTF->move(startX, startY + 2 * spacing);
	publisherIdTF->move(startX, startY + 3 * spacing);
	noOfPagesTF->move(startX, startY + 4 * spacing);
	languageCB->move(startX, startY + 5 * spacing);
	noOfCopiesTF->move(startX, startY + 6 * spacing);
	category1CB->move(startX, startY + 7 * spacing);
	category2CB->move(startX+250, startY + 7 * spacing);
	supplierIdTF->move(startX, startY + 8 * spacing);
	addBatchBtn->move(startX+250, startY + 8 * spacing);
	newBatchBtn->move(startX, startY + 11 * spacing);
	backBtn->move(startX, startY + 9 * spacing);
	backBtn->setText("Back");
	newBatchBtn->setText("+ New Batch");
	addBatchBtn->setText("Add Batch");

	bookNameTF->setPlaceholderText("Book Name");
	authorIdTF->setPlaceholderText("Author ID");
	editionTF->setPlaceholderText("Edition");
	publisherIdTF->setPlaceholderText("Publisher ID");
	noOfPagesTF->setPlaceholderText("Number of Pages");
	languageCB->setPlaceholderText("Language");
	noOfCopiesTF->setPlaceholderText("Number of Copies");
	category1CB->setPlaceholderText("Category 1");
	category2CB->setPlaceholderText("Category 2");
	supplierIdTF->setPlaceholderText("Supplier ID");
	
	category1CB->addItems({ "Action", "Adventure", "Comedy", "Drama", "Fantasy", "Horror", "Mystery", "Romance", "Thriller", "Western" });
	category2CB->addItems({ "Action", "Adventure", "Comedy", "Drama", "Fantasy", "Horror", "Mystery", "Romance", "Thriller", "Western" });
	languageCB->addItems({ "Arabic", "English", "French", "German", "Italian", "Japanese", "Korean", "Russian", "Spanish", "Turkish" });
	
	allBooksModel = new QSqlTableModel(this);
	allBooksModel->setTable("Books");
	allBooksModel->select();
	allBooksTable = new QTableView(this);
	allBooksTable->setParent(this); // Set the parent to the MembersPage widget
	allBooksTable->setModel(allBooksModel);
	allBooksTable->setGeometry(700, startY+100, 700, 500);
	allBooksTable->setSelectionMode(QAbstractItemView::ContiguousSelection);
	allBooksTable->show();

	deleteBookBtn = new QPushButton("Delete Book", this);
	deleteBookBtn->move(700, startY + 650);

	filterButtonGroup = new QButtonGroup(this);
	filterByBookName = new QRadioButton("Book Name", this);
	filterByAuthor = new QRadioButton("Author", this);
	filterByPublisher = new QRadioButton("Publisher", this);
	filterByLanguage = new QRadioButton("Language", this);
	filterByCategory = new QRadioButton("Category", this);

	filterButtonGroup->addButton(filterByBookName, 0);
	filterButtonGroup->addButton(filterByAuthor, 1);
	filterButtonGroup->addButton(filterByPublisher, 2);
	filterButtonGroup->addButton(filterByLanguage, 3);
	filterButtonGroup->addButton(filterByCategory, 4);

	filterByBookName->move(startX+100 + 100, startY);
	filterByAuthor->move(startX+350, startY);
	filterByPublisher->move(startX+500, startY);
	filterByLanguage->move(startX+650, startY);
	filterByCategory->move(startX+800, startY);

	filterByBookName->setChecked(true);

	filterCB = new QComboBox(this);
	filterCB->addItems({"Action", "Adventure", "Comedy", "Drama", "Fantasy", "Horror", "Mystery", "Romance", "Thriller", "Western"});
	filterCB->move(startX + 950, startY);
	filterCB->setCurrentIndex(0);

	bookNameTF->hide();
	authorIdTF->hide();
	editionTF->hide();
	publisherIdTF->hide();
	noOfPagesTF->hide();
	languageCB->hide();
	noOfCopiesTF->hide();
	category1CB->hide();
	category2CB->hide();
	supplierIdTF->hide();
	addBatchBtn->hide();
	backBtn->hide();



    // Connect the Stylesheet File
    QFile styleFile("stylesheet.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {

        QString styleSheet = QLatin1String(styleFile.readAll());
        searchForBookTF->setStyleSheet(styleSheet);
		searchBtn->setStyleSheet(styleSheet);
		searchedBookTableView->setStyleSheet(styleSheet);
		bookNameTF->setStyleSheet(styleSheet);
		authorIdTF->setStyleSheet(styleSheet);
		editionTF->setStyleSheet(styleSheet);
		publisherIdTF->setStyleSheet(styleSheet);
		noOfPagesTF->setStyleSheet(styleSheet);
		languageCB->setStyleSheet(styleSheet);
		noOfCopiesTF->setStyleSheet(styleSheet);
		category1CB->setStyleSheet(styleSheet);
		category2CB->setStyleSheet(styleSheet);
		supplierIdTF->setStyleSheet(styleSheet);
		addBatchBtn->setStyleSheet(styleSheet);
		newBatchBtn->setStyleSheet(styleSheet);
		backBtn->setStyleSheet(styleSheet);
		allBooksTable->setStyleSheet(styleSheet);
		deleteBookBtn->setStyleSheet(styleSheet);	
        
        styleFile.close();


    }
	connect(searchBtn, &QPushButton::clicked, this, &BooksPage::searchForBook);
	connect(newBatchBtn, &QPushButton::clicked, this, &BooksPage::newBatch);
	connect(addBatchBtn, &QPushButton::clicked, this, &BooksPage::addBatch);
	connect(backBtn, &QPushButton::clicked, this, &BooksPage::back);
	connect(deleteBookBtn, &QPushButton::clicked, [=]() {
		if(CommonData::getInstance().getType() != "M") {
			QMessageBox::information(this, "Error", "You do not have permission to delete a book");
			return;
		}
		deleteSelectedRow(allBooksTable, allBooksModel);
		});

}

BooksPage::~BooksPage()
{}

void BooksPage::searchForBook() {
	QString searchedBookName = searchForBookTF->text();
	QString searchBookQuery;
	QSqlQuery q1;
	QString categoryId;

	switch (filterButtonGroup->checkedId()) {
	case 0:
		searchBookQuery = "SELECT BookName, CopyID, Edition, CONCAT(a.FirstName, ' ', a.LastName) AS AuthorFullName FROM Books b JOIN Authors a ON b.AuthorID = a.AuthorID WHERE BookName = ? ";
		q1.prepare(searchBookQuery);
		q1.addBindValue(searchedBookName);
		break;
	case 1:
		searchBookQuery = "SELECT BookName, CopyID, Edition, CONCAT(a.FirstName, ' ', a.LastName) AS AuthorFullName FROM Books b JOIN Authors a ON b.AuthorID = a.AuthorID WHERE CONCAT(a.FirstName, ' ', a.LastName) = ? ";
		q1.prepare(searchBookQuery);
		q1.addBindValue(searchedBookName);
		break;
	case 2:
		searchBookQuery = "SELECT BookName, CopyID, Edition, CONCAT(a.FirstName, ' ', a.LastName) AS AuthorFullName FROM Books b JOIN Authors a ON b.AuthorID = a.AuthorID JOIN Publishers p ON b.PublisherID = p.PublisherID WHERE CONCAT(p.FirstName, ' ', p.LastName) = ? ";
		q1.prepare(searchBookQuery);
		q1.addBindValue(searchedBookName);
		break;
	case 3:
		searchBookQuery = "SELECT BookName, CopyID, Edition, CONCAT(a.FirstName, ' ', a.LastName) AS AuthorFullName FROM Books b JOIN Authors a ON b.AuthorID = a.AuthorID WHERE Languagee = ? ";
		q1.prepare(searchBookQuery);
		q1.addBindValue(searchedBookName);
		break;
	case 4:
		searchBookQuery = "SELECT BookName, b.CopyID, Edition, CONCAT(a.FirstName, ' ', a.LastName) AS AuthorFullName FROM Books b JOIN Authors a ON b.AuthorID = a.AuthorID JOIN Categories c ON b.CopyID = c.CopyID WHERE c.CategoryID = ? ";
		q1.prepare(searchBookQuery);
		categoryId = QString::number(filterCB->currentIndex());  
		q1.addBindValue(categoryId);
		break;
	default:
		searchBookQuery = "SELECT * FROM Books WHERE BookName = ?";
		break;
	}

	

	if (q1.exec()) {
    	searchedBookTableModel->setQuery(q1);
    	searchedBookTableView->setModel(searchedBookTableModel);
    	searchedBookTableView->show();
	} else {
    	qDebug() << "Query error:" << q1.lastError().text();
		QMessageBox::information(this, "Error", "Query error");
	}
}
void BooksPage::newBatch() {
	if(CommonData::getInstance().getType() != "M") {
		QMessageBox::information(this, "Error", "You do not have permission to add a new batch");
		return;
	}
	bookNameTF->show();
	authorIdTF->show();
	editionTF->show();
	publisherIdTF->show();
	noOfPagesTF->show();
	languageCB->show();
	noOfCopiesTF->show();
	category1CB->show();
	category2CB->show();
	addBatchBtn->show();
	supplierIdTF->show();

	searchForBookTF->hide();
	searchedBookTableView->hide();
	searchBtn->hide();
	newBatchBtn->hide();
	backBtn->show();
	searchLabel->hide();
	filterLabel->hide();
	filterByBookName->hide();
	filterByAuthor->hide();
	filterByPublisher->hide();
	filterByLanguage->hide();
	filterByCategory->hide();
	filterCB->hide();


}
void BooksPage::addBatch(){
	QString bookName = bookNameTF->text();
	QString authorId = authorIdTF->text();
	QString edition = editionTF->text();
	QString publisherId = publisherIdTF->text();
	QString noOfPages = noOfPagesTF->text();
	QString language = languageCB->currentText();
	int noOfCopies = noOfCopiesTF->text().toInt();
	QString category1 = QString::number(category1CB->currentIndex());
	QString category2 = QString::number(category2CB->currentIndex());
	QString supplierId = supplierIdTF->text();

	QSqlQuery q1;
	q1.prepare("INSERT INTO Books (BookName, AuthorID, Edition, PublisherID, PagesNo, Languagee) VALUES (:BookName, :AuthorID, :Edition, :PublisherID, :PagesNo, :Languagee)");
	q1.bindValue(":BookName", bookName);
	q1.bindValue(":AuthorID", authorId);
	q1.bindValue(":Edition", edition);
	q1.bindValue(":PublisherID", publisherId);
	q1.bindValue(":PagesNo", noOfPages);
	q1.bindValue(":Languagee", language);

	QSqlQuery supplyQuery;
	supplyQuery.prepare("INSERT INTO Supplies (CopyID, SupplierID, BranchID, DateOfSupplying) VALUES (:CopyID, :SupplierID, :BranchID, :DateOfSupplying)");
	supplyQuery.bindValue(":SupplierID", supplierId);
	supplyQuery.bindValue(":BranchID", CommonData::getInstance().getBranchId());
	supplyQuery.bindValue(":DateOfSupplying", QDateTime::currentDateTime());

	QSqlQuery categoryQuery;
	categoryQuery.prepare("INSERT INTO Categories (CategoryID, CopyID) VALUES (:CategoryID, :CopyID)");

	if (noOfCopies > 0) {
    bool success = true;
    for (int i = 0; i < noOfCopies; ++i) {
        if (!q1.exec()) {
            qDebug() << "Error inserting data:" << q1.lastError().text();
            QMessageBox::information(this, "Error", "Error inserting data");
            success = false;
            break; // Exit the loop if inserting into Books fails
        }

        int copyId = q1.lastInsertId().toInt();

        // Insert into Supplies table
        supplyQuery.bindValue(":CopyID", copyId);
        if (!supplyQuery.exec()) {
            qDebug() << "Error inserting data into Supplies:" << supplyQuery.lastError().text();
            QMessageBox::information(this, "Error", "Error inserting data into Supplies");
            success = false;
        }

        // Insert into Categories table for category1
        categoryQuery.bindValue(":CategoryID", category1);
        categoryQuery.bindValue(":CopyID", copyId);
        if (!categoryQuery.exec()) {
            qDebug() << "Error inserting data into Categories:" << categoryQuery.lastError().text();
            QMessageBox::information(this, "Error", "Error inserting data into Categories");
            success = false;
        }

        // Insert into Categories table for category2
        categoryQuery.bindValue(":CategoryID", category2);
        categoryQuery.bindValue(":CopyID", copyId);
        if (!categoryQuery.exec()) {
            qDebug() << "Error inserting data into Categories:" << categoryQuery.lastError().text();
            QMessageBox::information(this, "Error", "Error inserting data into Categories");
            success = false;
        }
    }

    if (success) {
        qDebug() << "Data inserted successfully";
        QMessageBox::information(this, "Success", "Data inserted successfully");
    } else {
        qDebug() << "Some data insertion failed";
    }
} else {
    qDebug() << "Invalid number of copies";
    QMessageBox::information(this, "Error", "Invalid number of copies");
}
	allBooksModel->select();
	allBooksTable->show();
}
void BooksPage::back() {
	bookNameTF->hide();
	authorIdTF->hide();
	editionTF->hide();
	publisherIdTF->hide();
	noOfPagesTF->hide();
	languageCB->hide();
	noOfCopiesTF->hide();
	category1CB->hide();
	category2CB->hide();
	addBatchBtn->hide();
	backBtn->hide();
	supplierIdTF->hide();

	searchForBookTF->show();
	searchedBookTableView->show();
	searchBtn->show();
	newBatchBtn->show();
	searchLabel->show();
	filterLabel->show();
	filterByBookName->show();
	filterByAuthor->show();
	filterByPublisher->show();
	filterByLanguage->show();
	filterByCategory->show();
	filterCB->show();


}
void BooksPage::deleteSelectedRow(QTableView* tableView, QSqlTableModel* tableModel) {
    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();
    // Check if there's at least one selected row
    if (!selectedRows.isEmpty()) {
        // Remove the first selected row
        tableModel->removeRow(selectedRows.first().row());
        // Refresh the model to reflect the changes
        tableModel->select();
    }

}
