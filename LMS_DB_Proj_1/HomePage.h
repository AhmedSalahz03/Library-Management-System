#pragma once

#include <QWidget>
#include "ui_HomePage.h"
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QtDebug>
#include <qsql.h>
#include <qsqltablemodel.h>
#include <qsqlquerymodel.h>
#include <qwidget.h>
#include <QTableView>
#include <string>
#include <iostream>
#include <QString>

class HomePage : public QWidget
{
	Q_OBJECT

public:
	HomePage(QWidget *parent = nullptr);
	~HomePage();
signals:
	void logoutRequested();

private:
	Ui::HomePageClass ui;
	QLabel* homeTitle;
	QLabel* totalNoMembers;
};
