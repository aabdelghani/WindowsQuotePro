#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool populateQuotesTable(QSqlDatabase &db);  // Function to populate the table

public slots:
    void onCellDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
