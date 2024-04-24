#pragma once

#include <QWidget>
#include "ui_MembersPage.h"
#include <QLineEdit>
#include <QPushButton>
#include <QtCore/QFile>
#include <qtableview.h>
#include <QSqlTableModel>
#include <QLabel>
#include <qmessagebox.h>
#include <QDateEdit>

class MembersPage : public QWidget
{
	Q_OBJECT

public:
	MembersPage(QWidget *parent = nullptr);
	~MembersPage();
signals:
	void mySignal();

public slots:
	void addMember();
	void setSizeForLineEdit(QLineEdit*);
	void deleteSelectedRow(QTableView*, QSqlTableModel*);
	void inspectMember();
	void backToTableView();
	void lend();
	void endLendInspect();

private:
	Ui::MembersPageClass ui;
	QLineEdit* firstNameTF;
	QLineEdit* lastNameTF;
	QLineEdit* phoneTF;
	QLineEdit* streetTF;
	QLineEdit* cityTF;
	QLineEdit* zipcodeTF;
	QLineEdit* emailTF;
	QPushButton* insertBtn;

	QSqlTableModel* allMembersModel;
	QTableView* allMembersTableView;

	QPushButton* deleteMemberBtn;
	QLineEdit* searchForMemberIdTF;
	QPushButton* searchForMemberIdBtn;

	QLabel* fNameInspectL;
	QLabel* lNameInspectL;
	QLabel* emailInspectL;
	QLabel* streetInspectL;
	QLabel* cityInspectL;
	QLabel* zipcodeInspectL;
	QLabel* phoneInspectL;
	QPushButton* doneInspectingBtn;

	QSqlTableModel* borrowedBooksofMembersModel;
	QTableView* borrowedBooksofMembersTableView;
	QLineEdit* lendCopyIdTF;
	QDateEdit* lendStartDate;
	QDateEdit* lendDueDate;
	QPushButton* lendBtn;
	QPushButton* endLendBtn;


};
