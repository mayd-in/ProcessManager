#include "processmodel.h"

#include <QAbstractTableModel>

ProcessModel::ProcessModel(QObject* parent) : QAbstractTableModel(parent)
{

}

void ProcessModel::onProcessStarted(Process* process)
{
    process->mPid = process->processId();

    beginInsertRows(QModelIndex(), mProcesses.size(), mProcesses.size());
    mProcesses.append(process);
    endInsertRows();
}

void ProcessModel::onProcessStopped(Process* process)
{
    auto index = mProcesses.indexOf(process);
    if (index < 0)
        return;

    beginRemoveRows(QModelIndex(), index, index);
    mProcesses.removeAt(index);
    endRemoveRows();
}

void ProcessModel::stopProcess(uint processId)
{
    int index = -1;
    for (int i = 0; i < mProcesses.size(); ++i) {
        if (mProcesses.at(i)->mPid == processId) {
            index = i;
            break;
        }
    }

    if (index == -1)
        return;

    mProcesses.at(index)->kill();
}

int ProcessModel::rowCount(const QModelIndex& /*parent*/) const
{
    return mProcesses.size();
}

int ProcessModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 5;
}

QVariant ProcessModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    auto process = mProcesses.at(index.row());
    switch (index.column()) {
        case 0: return process->processId();
        case 1: return process->mExecutable;
        case 2: return process->mArguments.join(" ");
    }
    return QVariant();
}

QVariant ProcessModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        switch (section) {
            case 0: return tr("PID");
            case 1: return tr("Exec Name");
            case 2: return tr("Arguments");
            case 3: return tr("Running Duration");
        }
        return "";
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}
