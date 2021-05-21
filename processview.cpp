#include "processview.h"
#include "processmodel.h"

#include <QLabel>
#include <QPushButton>
#include <QTime>
#include <QTimer>

void ProcessView::rowsInserted(const QModelIndex&, int start, int)
{
    // Duration label
    auto durationLabel = new QLabel;
    setIndexWidget(model()->index(start, 3), durationLabel);

    QTime startTime = QTime::currentTime();
    auto timer = new QTimer(durationLabel);
    connect(timer, &QTimer::timeout, durationLabel, [durationLabel, startTime] {
        durationLabel->setText(
                    QTime::fromMSecsSinceStartOfDay(startTime.msecsTo(QTime::currentTime())).toString());
    });
    timer->start(200);

    // Kill button
    auto killButton = new QPushButton(tr("Kill"));
    uint processId = model()->index(start, 0).data().toUInt();
    connect(killButton, &QPushButton::clicked, model(), [this, processId]() {
        auto processModel = qobject_cast<ProcessModel*>(model());
        processModel->stopProcess(processId);
    });
    setIndexWidget(model()->index(start, 4), killButton);
}
