// loginpage.h
#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include "CommonData.h"

class LoginPage : public QWidget
{
    Q_OBJECT
public:
    explicit LoginPage(QWidget* parent = nullptr);

public slots:
    QString* getLibrarianId();

signals:
    void loginSuccessful();

private:
    QLineEdit* userIdTF;
    QLineEdit* passwordTF;
    QPushButton* loginBtn;
    QString* librarianId;
    

private slots:
    void attemptLogin();
};

#endif // LOGINPAGE_H
