#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLineEdit;
class QStandardItemModel;
class QTableView;

class ProcessModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void startProcess();

    QLineEdit* mDirectoryLineEdit;
    QLineEdit* mExecutableLineEdit;
    QLineEdit* mArgumentsLineEdit;

    QTableView* mTableView;
    ProcessModel* mProcessModel;
};
#endif // MAINWINDOW_H
