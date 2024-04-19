#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LMS_DB_Proj_1.h"


#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include "loginpage.h"
#include "Homepage.h"
#include "MembersPage.h"
#include "MemberCustomPage.h"
//#include "settingspage.h"

class LMS_DB_Proj_1 : public QMainWindow
{
    Q_OBJECT

public:
    LMS_DB_Proj_1(QWidget* parent = nullptr);
    ~LMS_DB_Proj_1();

private:
    QWidget* centralWidget;
    QStackedWidget* stackedWidget;
    LoginPage* loginPage;
    HomePage* homePage;
    MembersPage* membersPage;
    MemberCustomPage* memberCustomPage;
    QWidget* sidebarWidget; // Sidebar container
    QVBoxLayout* sidebarLayout; // Layout for sidebar buttons

    QPushButton* menuHomeButton;
    QPushButton* menuSettingsButton;
    QPushButton* menuMembersButton;
    QPushButton* menuLoginButton;
    //SettingsPage* settingsPage;

    void setupUi();
    void setupConnections();
    void showSidebar(bool show); // Method to show/hide the sidebar
    void updateButtonStatus(QPushButton*, bool);

};
