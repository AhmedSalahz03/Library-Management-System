#pragma once

#include <QWidget>
#include "ui_AuthorsPublishersPage.h"
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
#include <qsqltablemodel.h>
#include "CommonData.h"

class AuthorsPublishersPage : public QWidget
{
	Q_OBJECT

public:
	AuthorsPublishersPage(QWidget *parent = nullptr);
	~AuthorsPublishersPage();
public slots:
	void addAuthor();
	void addPublisher();
	void deleteSelectedRow(QSqlTableModel* tableModel, QTableView* tableView);

private:
	Ui::AuthorsPublishersPageClass ui;
	QSqlTableModel* authorsModel;
	QTableView* authorsTableView;
	QSqlTableModel* publishersModel;
	QTableView* publishersTableView;

	QLineEdit* authorFirstNameTF;
	QLineEdit* authorLastNameTF;
	QPushButton* addAuthorBtn;
	QPushButton* deleteAuthorBtn;

	QLineEdit* publisherFirstNameTF;
	QLineEdit* publisherLastNameTF;
	QPushButton* addPublisherBtn;
	QPushButton* deletePublisherBtn;


};
