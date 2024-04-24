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

    userType = new QString();
        
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create sidebar buttons with icons
    sidebarWidget = new QWidget(this);
    sidebarWidget->setStyleSheet("background-color: #c0c0c0;"); // Set background color to gray
    sidebarLayout = new QVBoxLayout(sidebarWidget);

    // Menu Buttons with Icons
    menuHomeButton = new QPushButton(sidebarWidget);
    menuHomeButton->setIcon(QIcon(":/icons/Home_1.png"));
    menuHomeButton->setIconSize(QSize(50, 50));
    menuHomeButton->setProperty("active", false); // Initially inactive
    menuHomeButton->setStyleSheet("background-color: #c0c0c0;"); // Set initial background color

    menuMembersButton = new QPushButton(sidebarWidget);
    menuMembersButton->setIcon(QIcon(":/icons/members_icon.png"));
    menuMembersButton->setIconSize(QSize(50, 50));
    menuMembersButton->setProperty("active", false); // Initially inactive
    menuMembersButton->setStyleSheet("background-color: #c0c0c0;"); // Set initial background color

    
    menuLoginButton = new QPushButton(sidebarWidget);
    menuLoginButton->setIcon(QIcon(":/icons/logout_icon.png"));
    menuLoginButton->setIconSize(QSize(50, 50));
    menuLoginButton->setProperty("active", false); // Initially inactive
    menuLoginButton->setStyleSheet("background-color: #c0c0c0;"); // Set initial background color

    menuBooksButton = new QPushButton(sidebarWidget);
    menuBooksButton->setIcon(QIcon(":/icons/Books_Icon.png"));
    menuBooksButton->setIconSize(QSize(50, 50));
    menuBooksButton->setProperty("active", false); // Initially inactive
    menuBooksButton->setStyleSheet("background-color: #c0c0c0;"); // Set initial background color

    menuEventsButton = new QPushButton(sidebarWidget);
    menuEventsButton->setIcon(QIcon(":/icons/Events.png"));
    menuEventsButton->setIconSize(QSize(50, 50));
    menuEventsButton->setProperty("active", false); // Initially inactive
    menuEventsButton->setStyleSheet("background-color: #c0c0c0;"); // Set initial background color

    sidebarLayout->addWidget(menuHomeButton);
    sidebarLayout->addWidget(menuMembersButton);
    
    sidebarLayout->addWidget(menuLoginButton);
    sidebarLayout->addWidget(menuBooksButton);
    sidebarLayout->addWidget(menuEventsButton);

    // Create stacked widget for main pages
    stackedWidget = new QStackedWidget(centralWidget);
    loginPage = new LoginPage;
    homePage = new HomePage;
    membersPage = new MembersPage;
    memberCustomPage = new MemberCustomPage;
    booksPage = new BooksPage;
    eventsPage = new EventsPage;

    stackedWidget->addWidget(loginPage);
    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(membersPage);
    stackedWidget->addWidget(memberCustomPage);
    stackedWidget->addWidget(booksPage);
    stackedWidget->addWidget(eventsPage);


    // Layout for central widget
    QHBoxLayout* layout = new QHBoxLayout(centralWidget);
    layout->addWidget(sidebarWidget);
    layout->addWidget(stackedWidget);

    // Set layout for central widget
    centralWidget->setLayout(layout);

    // Show login page by default
    stackedWidget->setCurrentWidget(loginPage);

    smallIdL = new QLabel(this);
    smallIdL->move(1200, 750);
    smallIdL->show();

    // Create settings button
    menuSettingsButton = new QPushButton(sidebarWidget);
    menuSettingsButton->setIcon(QIcon(":/icons/settings_icon.png"));
    menuSettingsButton->setIconSize(QSize(50, 50));
    menuSettingsButton->setProperty("active", false); // Initially inactive
    menuSettingsButton->setStyleSheet("background-color: #c0c0c0;"); // Set initial background color
    menuSettingsButton->hide(); // Initially hide the button
    sidebarLayout->addWidget(menuSettingsButton);
    
    

}

void LMS_DB_Proj_1::setupConnections()
{
    connect(menuLoginButton, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentWidget(loginPage);
        });
    connect(menuEventsButton, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentWidget(eventsPage);
        });

    connect(loginPage, &LoginPage::loginSuccessful, [=]() {
        stackedWidget->setCurrentWidget(homePage);
    updateButtonStatus(menuHomeButton, true); // Set home button active
    showSidebar(true);
    smallIdL->setText("ID: " + CommonData::getInstance().getUsername());
    userType->assign(CommonData::getInstance().getType());
    showEventsPage();
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

    connect(menuBooksButton, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentWidget(booksPage);
    updateButtonStatus(menuBooksButton, true); // Set members button active
    updateButtonStatus(menuHomeButton, false);
    updateButtonStatus(menuMembersButton, false);
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

void LMS_DB_Proj_1::showEventsPage() {
    if (userType->compare("M") == 0) {
        menuSettingsButton->show();
    } else {
        menuSettingsButton->hide();
    }
}
