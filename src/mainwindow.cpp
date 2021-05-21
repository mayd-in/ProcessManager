#include "mainwindow.h"
#include "processmodel.h"
#include "processview.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QTableView>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mDirectoryLineEdit = new QLineEdit;
    mExecutableLineEdit = new QLineEdit;
    mArgumentsLineEdit = new QLineEdit;

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Directory:"), mDirectoryLineEdit);
    formLayout->addRow(tr("Executable:"), mExecutableLineEdit);
    formLayout->addRow(tr("Arguments:"), mArgumentsLineEdit);

    auto startPushButton = new QPushButton(tr("Start Process"));
    connect(startPushButton, &QPushButton::clicked, this, &MainWindow::startProcess);

    mProcessModel = new ProcessModel(this);

    mTableView = new ProcessView;
    mTableView->setModel(mProcessModel);
    mTableView->setSelectionBehavior(QTableView::SelectRows);
    mTableView->setSelectionMode(QTableView::SingleSelection);
    mTableView->verticalHeader()->hide();
    mTableView->horizontalHeader()->setStretchLastSection(true);
    mTableView->resizeColumnsToContents();

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(startPushButton);
    mainLayout->addWidget(mTableView);

    auto centralWidget = new QWidget;
    centralWidget->setMinimumWidth(600);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::startProcess()
{
    QString directory = mDirectoryLineEdit->text().trimmed();
    if (!directory.isEmpty())
        directory += "/";
    QString executable = mExecutableLineEdit->text().trimmed();
    QStringList arguments = mArgumentsLineEdit->text().split(" ", Qt::SkipEmptyParts);

    if (executable.isEmpty()) {
        QMessageBox::warning(this, QApplication::applicationDisplayName(),
                             tr("Executable field is empty"));
        return;
    }

    auto process = new Process(directory, executable, arguments, this);
    connect(process, &QProcess::started, mProcessModel, [this, process](){ mProcessModel->onProcessStarted(process); });
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), mProcessModel,
            [this, process](int /*exitCode*/, QProcess::ExitStatus /*exitStatus*/){
        mProcessModel->onProcessStopped(process);
    });
    process->start();
}
