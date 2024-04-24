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
