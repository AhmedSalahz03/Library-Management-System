// LMS_DB_Proj_1.cpp

#include "LMS_DB_Proj_1.h"
#include<qobject.h>
LMS_DB_Proj_1::LMS_DB_Proj_1(QWidget* parent)
    : QMainWindow(parent)
{
    setupUi();
    setupConnections();
    showSidebar(false); // Initially hide the sidebar
}

LMS_DB_Proj_1::~LMS_DB_Proj_1()
{
}

void LMS_DB_Proj_1::setupUi()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create sidebar buttons with icons
    sidebarWidget = new QWidget(this);
    sidebarWidget->setStyleSheet("background-color: #c0c0c0;"); // Set background color to gray
    sidebarLayout = new QVBoxLayout(sidebarWidget);

    // Menu Buttons with Icons
    menuHomeButton = new QPushButton(sidebarWidget);
    menuHomeButton->setIcon(QIcon(":/icons/Home_Green-removebg-preview.png"));
    menuHomeButton->setIconSize(QSize(50, 50));
    menuHomeButton->setProperty("active", false); // Initially inactive
    menuHomeButton->setStyleSheet("background-color: #c0c0c0;"); // Set initial background color

    menuMembersButton = new QPushButton(sidebarWidget);
    menuMembersButton->setIcon(QIcon(":/icons/members_icon.png"));
    menuMembersButton->setIconSize(QSize(50, 50));
    menuMembersButton->setProperty("active", false); // Initially inactive
    menuMembersButton->setStyleSheet("background-color: #c0c0c0;"); // Set initial background color

    menuSettingsButton = new QPushButton(sidebarWidget);
    menuSettingsButton->setIcon(QIcon(":/icons/settings_icon.png"));
    menuSettingsButton->setIconSize(QSize(50, 50));
    menuSettingsButton->setProperty("active", false); // Initially inactive
    menuSettingsButton->setStyleSheet("background-color: #c0c0c0;"); // Set initial background color

    menuLoginButton = new QPushButton(sidebarWidget);
    menuLoginButton->setIcon(QIcon(":/icons/logout_icon.png"));
    menuLoginButton->setIconSize(QSize(50, 50));
    menuLoginButton->setProperty("active", false); // Initially inactive
    menuLoginButton->setStyleSheet("background-color: #c0c0c0;"); // Set initial background color

    sidebarLayout->addWidget(menuHomeButton);
    sidebarLayout->addWidget(menuMembersButton);
    sidebarLayout->addWidget(menuSettingsButton);
    sidebarLayout->addWidget(menuLoginButton);

    // Create stacked widget for main pages
    stackedWidget = new QStackedWidget(centralWidget);
    loginPage = new LoginPage;
    homePage = new HomePage;
    membersPage = new MembersPage;
    memberCustomPage = new MemberCustomPage;

    stackedWidget->addWidget(loginPage);
    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(membersPage);
    stackedWidget->addWidget(memberCustomPage);

    // Layout for central widget
    QHBoxLayout* layout = new QHBoxLayout(centralWidget);
    layout->addWidget(sidebarWidget);
    layout->addWidget(stackedWidget);

    // Set layout for central widget
    centralWidget->setLayout(layout);

    // Show login page by default
    stackedWidget->setCurrentWidget(loginPage);

    

}

void LMS_DB_Proj_1::setupConnections()
{
    connect(menuLoginButton, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentWidget(loginPage);
        });

    connect(loginPage, &LoginPage::loginSuccessful, [=]() {
        stackedWidget->setCurrentWidget(homePage);
    updateButtonStatus(menuHomeButton, true); // Set home button active
    showSidebar(true);
        });

    connect(menuLoginButton, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentWidget(loginPage);
    updateButtonStatus(menuHomeButton, false); // Set home button inactive
    showSidebar(false); // Hide sidebar when on login page
        });

    connect(menuMembersButton, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentWidget(membersPage);
    updateButtonStatus(menuMembersButton, true); // Set members button active
    updateButtonStatus(menuHomeButton, false);
    showSidebar(true);
        });

    connect(menuHomeButton, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentWidget(homePage);
    updateButtonStatus(menuMembersButton, false); // Set members button active
    updateButtonStatus(menuHomeButton, true);
    showSidebar(true);
        });
}

void LMS_DB_Proj_1::showSidebar(bool show)
{
    sidebarWidget->setVisible(show);
}

void LMS_DB_Proj_1::updateButtonStatus(QPushButton* button, bool active)
{
    button->setProperty("active", active); // Update button status
    button->setStyleSheet(active ? "background-color: white;" : "background-color: #c0c0c6;"); // Change background color based on status
}
