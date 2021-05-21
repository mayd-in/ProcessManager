#ifndef PROCESSMODEL_H
#define PROCESSMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QProcess>

class Process : public QProcess {
public:
    Process(QString directory, QString executable, QStringList arguments, QObject *parent = nullptr)
        : QProcess(parent)
    {
        mDirectory = directory;
        mExecutable = executable;
        mArguments = arguments;
    }

    void start()
    {
        return QProcess::start(QString("%1%2").arg(mDirectory, mExecutable), mArguments);
    }

    uint mPid;
    QString mDirectory;
    QString mExecutable;
    QStringList mArguments;
};

class ProcessModel : public QAbstractTableModel {
    Q_OBJECT

public:
    ProcessModel(QObject* parent = nullptr);

    void onProcessStarted(Process* process);
    void onProcessStopped(Process* process);

    void stopProcess(uint processId);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    QList<Process*> mProcesses;
};

#endif // PROCESSMODEL_H
