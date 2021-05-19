#include "mainwindow.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto directoryLineEdit = new QLineEdit;
    auto executableLineEdit = new QLineEdit;
    auto argumentsLineEdit = new QLineEdit;

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Directory:"), directoryLineEdit);
    formLayout->addRow(tr("Executable:"), executableLineEdit);
    formLayout->addRow(tr("Arguments:"), argumentsLineEdit);

    auto startPushButton = new QPushButton(tr("Start Process"));

    auto model = new QStandardItemModel(1, 5);
    model->setHeaderData(0, Qt::Horizontal, tr("PID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Exec Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Arguments"));
    model->setHeaderData(3, Qt::Horizontal, tr("Running Duration"));
    model->setHeaderData(4, Qt::Horizontal, "");

    for (int row = 0; row < model->rowCount(); ++row) {
        for (int column = 0; column < model->columnCount(); ++column) {
            QStandardItem *item = new QStandardItem(QString("row %0, column %1").arg(row).arg(column));
            model->setItem(row, column, item);
        }
    }

    auto tableView = new QTableView;
    tableView->setModel(model);
    tableView->verticalHeader()->hide();
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->resizeColumnsToContents();
    tableView->setIndexWidget(model->index(0, 4), new QPushButton(tr("Kill")));

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(startPushButton);
    mainLayout->addWidget(tableView);

    auto centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}

