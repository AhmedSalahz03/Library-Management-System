#include "LMS_DB_Proj_1.h"
#include <QtWidgets/QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QtDebug>
#include <iostream>


#include <QtDebug>

void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    Q_UNUSED(type);
    QByteArray localMsg = msg.toLocal8Bit();
    const char* file = context.file ? context.file : "";
    const char* function = context.function ? context.function : "";
    qDebug() << file << ":" << context.line << ":" << function << " - " << localMsg.constData();
}


int main(int argc, char *argv[])
{
    qInstallMessageHandler(customMessageHandler);
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("LMS QT DB3"); // Use the name of your ODBC data source
    db.setUserName("YourUsername"); // If required
    db.setPassword("YourPassword"); // If required

    if (!db.open()) {
        qDebug() << "Error: " << db.lastError().text();
    }
    else {
        qDebug() << "Connected to the database!";
    }

    QApplication a(argc, argv);
    LMS_DB_Proj_1 w;
    w.setWindowTitle("Library Management System");
    w.resize(1200, 700);
    w.show();

    

    return a.exec();
}
