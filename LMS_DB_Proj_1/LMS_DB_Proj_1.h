#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LMS_DB_Proj_1.h"
#include "CommonData.h"

#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include "loginpage.h"
#include "Homepage.h"
#include "MembersPage.h"
#include "MemberCustomPage.h"
#include "BooksPage.h"
#include "Eventspage.h"
#include "AuthorsPublishersPage.h"
#include "StaffPage.h"

class LMS_DB_Proj_1 : public QMainWindow
{
    Q_OBJECT

public:
    LMS_DB_Proj_1(QWidget* parent = nullptr);
    ~LMS_DB_Proj_1();

private:

    QString* userType;

    QWidget* centralWidget;
    QStackedWidget* stackedWidget;
    LoginPage* loginPage;
    HomePage* homePage;
    MembersPage* membersPage;
    BooksPage* booksPage;
    MemberCustomPage* memberCustomPage;
    EventsPage* eventsPage;
    AuthorsPublishersPage* authorsPublishersPage;
    StaffPage* staffPage;

    QWidget* sidebarWidget; // Sidebar container
    QVBoxLayout* sidebarLayout; // Layout for sidebar buttons

    QPushButton* menuHomeButton;
    QPushButton* menuSettingsButton;
    QPushButton* menuMembersButton;
    QPushButton* menuLoginButton;
    QPushButton* menuBooksButton;
    QPushButton* menuEventsButton;
    QPushButton* menuAuthorsPublishersButton;
    QPushButton* menuStaffButton;

    QLabel* smallIdL;

    void setupUi();
    void setupConnections();
    void showSidebar(bool show); // Method to show/hide the sidebar
    void updateButtonStatus(QPushButton*, bool);
    void showStaffPage();

};
