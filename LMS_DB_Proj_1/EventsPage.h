#pragma once

#include <QWidget>
#include "ui_EventsPage.h"
#include <QLineEdit>
#include <QPushButton>
#include <QtCore/QFile>
#include <qtableview.h>
#include <QSqlTableModel>
#include <QLabel>
#include <qmessagebox.h>
#include <QDateEdit>
#include "CommonData.h"
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
#include <QVBoxLayout>
#include <QModelIndexList>
#include <QHeaderView>

class EventsPage : public QWidget
{
	Q_OBJECT

public:
	EventsPage(QWidget *parent = nullptr);
	~EventsPage();

public slots:
	void addEvent();

private:
	Ui::EventsPageClass ui;
	QSqlTableModel* allEventsTableModel;
	QTableView* allEventsTable;
	void setSizeForLineEdit(QLineEdit*);

	QLineEdit* eventTitleTF;
	QDateEdit* eventDateTF;
	QTimeEdit* eventTimeTF;
	QLineEdit* eventDescriptionTF;
	QLineEdit* eventMaxCapacityTF;
	QPushButton* insertEventBtn;
};
