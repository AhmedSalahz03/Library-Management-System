#include "HomePage.h"

HomePage::HomePage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	homeTitle = new QLabel("Home", this);
	homeTitle->resize(100, 40);
	homeTitle->move(600, 20);
	QFont fontTitle = homeTitle->font();
	fontTitle.setPointSize(20);
	fontTitle.setBold(true);
	homeTitle->setFont(fontTitle);
	int rowCount;
	// Execute the query
	QSqlQuery query;
	if (query.exec("SELECT COUNT(*) FROM Members")) {
		if (query.next()) {
			rowCount = query.value(0).toInt();
			qDebug() << "Total number of members:" << rowCount;
			
		}
		else {
			qDebug() << "Error: No result returned.";
			rowCount = -1;
		}
	}
	else {
		qDebug() << "Error executing query:" << query.lastError().text();
	}
	totalNoMembers = new QLabel(this);
	totalNoMembers->setText("Total Numbers of Members " + QString::number(rowCount));
	totalNoMembers->show();
}

HomePage::~HomePage()
{}
