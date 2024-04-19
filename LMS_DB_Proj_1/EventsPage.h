#pragma once

#include <QWidget>
#include "ui_EventsPage.h"

class EventsPage : public QWidget
{
	Q_OBJECT

public:
	EventsPage(QWidget *parent = nullptr);
	~EventsPage();

private:
	Ui::EventsPageClass ui;
};
