#ifndef EDITQUOTE_H
#define EDITQUOTE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QStringList>

class editQuote : public QWidget {
    Q_OBJECT
public:
    explicit editQuote(const QStringList &rowData, QWidget *parent = nullptr);
};

#endif  // EDITQUOTE_H
