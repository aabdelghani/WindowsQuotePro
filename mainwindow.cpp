#include "mainwindow.h"
#include "editquote.h"
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
    connect(ui->quotesQTable, &QTableWidget::cellDoubleClicked, this, &MainWindow::onCellDoubleClicked);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onCellDoubleClicked(int row, int column) {
    Q_UNUSED(column)  // We don't need the column number for this operation

    // Collect data from the row
    QList<QString> rowData;
    for (int i = 0; i < ui->quotesQTable->columnCount(); ++i) {
        rowData.append(ui->quotesQTable->item(row, i)->text());
    }

    // Open the new window and pass the data
    editQuote *newWindow = new editQuote(rowData);
    newWindow->show();
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

    // Set selection behavior and mode
    quotesQTable->setSelectionMode(QAbstractItemView::SingleSelection);
    quotesQTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Make the table unclickable
    quotesQTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    quotesQTable->setFocusPolicy(Qt::NoFocus);

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
