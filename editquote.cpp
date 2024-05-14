#include "editquote.h"

editQuote::editQuote(const QStringList &rowData, QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    for (const QString &data : rowData) {
        QLabel *label = new QLabel(data, this);
        layout->addWidget(label);
    }
}
