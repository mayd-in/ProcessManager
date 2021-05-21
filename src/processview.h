#ifndef PROCESSVIEW_H
#define PROCESSVIEW_H

#include <QTableView>

class ProcessView : public QTableView {
protected slots:
    void rowsInserted(const QModelIndex& /*parent*/, int start, int /*end*/) override;
};

#endif // PROCESSVIEW_H
