// loginpage.cpp
#include "loginpage.h"

LoginPage::LoginPage(QWidget* parent) : QWidget(parent)
{
    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("Login", this);
    layout = new QVBoxLayout(this);

    layout->addWidget(usernameEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(loginButton);

    setLayout(layout);

    connect(loginButton, &QPushButton::clicked, this, &LoginPage::attemptLogin);
}

void LoginPage::attemptLogin()
{
    // Add your authentication logic here
    // For now, emit loginSuccessful signal directly
    emit loginSuccessful();
}

