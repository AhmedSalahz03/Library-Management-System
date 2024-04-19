#pragma once

#include <QWidget>
#include "ui_MemberCustomPage.h"

class MemberCustomPage : public QWidget
{
	Q_OBJECT

public:
	MemberCustomPage(QWidget *parent = nullptr);
	~MemberCustomPage();

private:
	Ui::MemberCustomPageClass ui;
};
