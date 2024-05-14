#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::populateQuotesTable(QSqlDatabase &db) {
    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM quotes")) {
        qDebug() << "Error: query failed: " << query.lastError().text();
        return false;
    }

    QTableWidget* quotesQTable = ui->quotesQTable;
    quotesQTable->setColumnCount(10);
    QStringList headers = {"Quote ID", "Customer Name", "Quote Name", "Quote Date",
                           "Total Price", "Door Material", "Door Size", "Status",
                           "Sales Representative", "Expiration Date"};
    quotesQTable->setHorizontalHeaderLabels(headers);
    quotesQTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    int row = 0;
    while (query.next()) {
        quotesQTable->insertRow(quotesQTable->rowCount());
        for (int col = 0; col < 10; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(query.value(col).toString());
            quotesQTable->setItem(row, col, item);
        }
        ++row;
    }
    return true;
}
