#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QtSql>
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

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_actionSave_as_triggered();

    void on_actionSave_triggered();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString path;
    QSqlDatabase db;
    SQLEdit *SQLEditor;
};

#endif // MAINWINDOW_H
