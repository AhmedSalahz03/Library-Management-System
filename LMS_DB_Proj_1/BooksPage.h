#pragma once

#include <QWidget>
#include "ui_BooksPage.h"
#include <QLineEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QtCore/QFile>
#include <qtableview.h>
#include <QSqlTableModel>
#include <QLabel>
#include <qmessagebox.h>
#include <QDateEdit>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QtDebug>
#include <qsql.h>
#include <QSqlDatabase>
#include <qcombobox.h>
#include <qradiobutton.h>

class BooksPage : public QWidget
{
	Q_OBJECT

public:
	BooksPage(QWidget *parent = nullptr);
	~BooksPage();

	QLabel* searchLabel;
	QLabel* allBooksLabel;
	QLabel* filterLabel;

	QLineEdit* searchForBookTF;
	QSqlTableModel* searchedBookTableModel;
	QTableView* searchedBookTableView;
	QPushButton* searchBtn;
	
	QPushButton* newBatchBtn;
	QLineEdit* bookNameTF;
	QLineEdit* authorIdTF;
	QLineEdit* editionTF;											
	QLineEdit* publisherIdTF;
	QLineEdit* noOfPagesTF;
	QComboBox* languageCB;
	QLineEdit* noOfCopiesTF;
	QComboBox* category1CB;
	QComboBox* category2CB;
	QLineEdit* supplierIdTF;

	QPushButton* addBatchBtn;
	QPushButton* backBtn;

	QSqlTableModel* allBooksModel;
	QTableView* allBooksTable;
	QPushButton* deleteBookBtn;

	QButtonGroup* filterButtonGroup;
	QRadioButton* filterByBookName;
	QRadioButton* filterByAuthor;
	QRadioButton* filterByPublisher;
	QRadioButton* filterByLanguage;
	QRadioButton* filterByCategory;

	QComboBox* filterCB;


public slots:
	void searchForBook();
	void newBatch();
	void addBatch();
	void back();
	void deleteSelectedRow(QTableView* tableView, QSqlTableModel* tableModel);

private:
	Ui::BooksPageClass ui;
};
