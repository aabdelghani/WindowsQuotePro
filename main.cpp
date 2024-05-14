#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Construct the full path to the database file
    QString databasePath = QDir::current().absoluteFilePath("quotes.db");
    qDebug() << "Database path:" << databasePath;

    // Set up the database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databasePath);
    if (!db.open()) {
        qDebug() << "Error: connection with database failed: " << db.lastError().text();
        return -1;
    }

    MainWindow window;
    window.setWindowTitle("WindowQuotePro");

    // Assuming MainWindow has a method to populate quotesQTable
    if (!window.populateQuotesTable(db)) {
        qDebug() << "Error: Unable to populate quotes table.";
        return -1;
    }

    window.showFullScreen();

    return app.exec();
}
