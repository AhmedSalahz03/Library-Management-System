#pragma once

#include <QWidget>
#include "ui_StaffPage.h"
#include <QSqlTableModel>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>
#include <qsql.h>
#include <qsqlquery.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include <QFile>

class StaffPage : public QWidget
{
	Q_OBJECT

public:
	StaffPage(QWidget *parent = nullptr);
	~StaffPage();
public slots:
	void addStaff();
	void deleteSelectedRow(QSqlTableModel*,QTableView*);
	void handleDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles);
private:
	Ui::StaffPageClass ui;

	QSqlTableModel* staffModel;
	QTableView* staffTableView;
	QLineEdit* staffFirstNameTF;
	QLineEdit* staffLastNameTF;
	QLineEdit* staffEmailTF;
	QLineEdit* staffPhoneTF;
	QLineEdit* staffStreetTF;
	QLineEdit* staffCityTF;
	QLineEdit* staffZipcodeTF;
	QLineEdit* staffSalaryTF;
	QLineEdit* staffBranchIdTF;
	QLineEdit* staffPasswordTF;
	QDateEdit* staffStartDateTF;
	QPushButton* addStaffBtn;
	QPushButton* deleteStaffBtn;

	QSqlTableModel* branchesModel;
	QTableView* branchesTableView;
};
