#include "BooksPage.h"

BooksPage::BooksPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	int startX = 20;
	int startY = 40;
	int spacing = 60;

	searchForBookTF = new QLineEdit(this);
	searchedBookTableModel = new QSqlTableModel(this);
	searchedBookTableView = new QTableView(this);
	searchBtn = new QPushButton(this);

	searchForBookTF->move(startX, startY);

	searchedBookTableView->setParent(this); // Set the parent to the MembersPage widget
	searchedBookTableView->setModel(searchedBookTableModel);
	searchedBookTableView->setGeometry(300, startY, 500, 400);
	searchedBookTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
	
	searchBtn->move(startX, startY + spacing);
	searchBtn->setText("Search");

	bookNameTF = new QLineEdit(this);
	authorNameTF = new QLineEdit(this);
	editionTF = new QLineEdit(this);
	publisherIdTF = new QLineEdit(this);
	noOfPagesTF = new QLineEdit(this);
	languageTF = new QLineEdit(this);
	noOfCopiesTF = new QLineEdit(this);
	categoryCB = new QChoiceBox(this);
	newBatchBtn = new QPushButton(this);
	addBatchBtn = new QPushButton(this);

	bookNameTF->move(startX, startY);
	authorNameTF->move(startX, startY + spacing);
	editionTF->move(startX, startY + 2 * spacing);
	publisherIdTF->move(startX, startY + 3 * spacing);
	noOfPagesTF->move(startX, startY + 4 * spacing);
	languageTF->move(startX, startY + 5 * spacing);
	noOfCopiesTF->move(startX, startY + 6 * spacing);
	categoryCB->move(startX, startY + 7 * spacing);
	addBatchBtn->move(startX, startY + 8 * spacing);
	newBatchBtn->move(startX, startY + 8 * spacing);
	newBatchBtn->setText("New Batch");

	bookNameTF->setPlaceholderText("Book Name");
	authorNameTF->setPlaceholderText("Author Name");
	editionTF->setPlaceholderText("Edition");
	publisherIdTF->setPlaceholderText("Publisher ID");
	noOfPagesTF->setPlaceholderText("Number of Pages");
	languageTF->setPlaceholderText("Language");
	noOfCopiesTF->setPlaceholderText("Number of Copies");
	categoryCB->addItem("Category");

	bookNameTF->hide();
	authorNameTF->hide();
	editionTF->hide();
	publisherIdTF->hide();
	noOfPagesTF->hide();
	languageTF->hide();
	noOfCopiesTF->hide();
	categoryCB->hide();
	addBatchBtn->hide();



    // Connect the Stylesheet File
    QFile styleFile("stylesheet.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {

        QString styleSheet = QLatin1String(styleFile.readAll());
        searchForBookTF->setStyleSheet(styleSheet);
		searchBtn->setStyleSheet(styleSheet);
		searchedBookTableView->setStyleSheet(styleSheet);
        
        styleFile.close();


    }
	connect(searchBtn, &QPushButton::clicked, this, &BooksPage::searchForBook);

}

BooksPage::~BooksPage()
{}

void BooksPage::searchForBook() {
	QString searchedBookName = searchForBookTF->text();
	QString searchBookQuery = "SELECT BookName, CopyID, Edition, CONCAT(a.FirstName, ' ', a.LastName) AS AuthorFullName FROM Books b JOIN Authors a ON b.AuthorID = a.AuthorID WHERE BookName = ? ";
	QSqlQuery q1;
	q1.prepare(searchBookQuery);
	q1.addBindValue(searchedBookName);

	if (q1.exec()) {
		searchedBookTableModel->setQuery(q1);
		searchedBookTableView->setModel(searchedBookTableModel);
		searchedBookTableView->show();

	}
}
void BooksPage::newBatch() {
	bookNameTF->show();
	authorNameTF->show();
	editionTF->show();
	publisherIdTF->show();
	noOfPagesTF->show();
	languageTF->show();
	noOfCopiesTF->show();
	categoryCB->show();
	addBatchBtn->show();
}
void BooksPage::addBatch(){
	QString bookName = bookNameTF->text();
	QString authorName = authorNameTF->text();
	QString edition = editionTF->text();
	QString publisherId = publisherIdTF->text();
	QString noOfPages = noOfPagesTF->text();
	QString language = languageTF->text();
	QString noOfCopies = noOfCopiesTF->text();
	QString category = categoryCB->currentText();

	QSqlQuery q1;
	q1.prepare("INSERT INTO Books (BookName, AuthorID, Edition, PublisherID, NoOfPages, Language, NoOfCopies, Category) VALUES (:BookName, :AuthorID, :Edition, :PublisherID, :NoOfPages, :Language, :NoOfCopies, :Category)");
	q1.bindValue(":BookName", bookName);
	q1.bindValue(":AuthorID", authorName);
	q1.bindValue(":Edition", edition);
	q1.bindValue(":PublisherID", publisherId);
	q1.bindValue(":NoOfPages", noOfPages);
	q1.bindValue(":Language", language);
	q1.bindValue(":NoOfCopies", noOfCopies);
	q1.bindValue(":Category", category);

	if (q1.exec()) {
		qDebug() << "Data inserted successfully";
	}
	else {
		qDebug() << "Error inserting data:" << q1.lastError().text();
	}
}
