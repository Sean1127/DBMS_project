#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QtSql>
#include <QSqlTableModel>
#include "dialog.h"
#include "sqledit.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initComboButton();

private slots:

    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_2_activated(int index);

private:
    Ui::MainWindow *ui;
    QString path;
    QSqlDatabase database;
    QSqlTableModel *tableModel;
    SQLEdit *SQLEditor;
};

#endif // MAINWINDOW_H
