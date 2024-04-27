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

class BooksPage : public QWidget
{
	Q_OBJECT

public:
	BooksPage(QWidget *parent = nullptr);
	~BooksPage();

	QLineEdit* searchForBookTF;
	QSqlTableModel* searchedBookTableModel;
	QTableView* searchedBookTableView;
	QPushButton* searchBtn;
	
	QPushButton* newBatchBtn;
	QLineEdit* bookNameTF;
	QLineEdit* authorNameTF;
	QLineEdit* editionTF;
	QLineEdit* publisherIdTF;
	QLineEdit* noOfPagesTF;
	QLineEdit* languageTF;
	QLineEdit* noOfCopiesTF;
	QChoiceBox* categoryCB;
	QLineEdit* supplierIdTF;

	QPushButton* addBatchBtn;
public slots:
	void searchForBook();
private:
	Ui::BooksPageClass ui;
};
