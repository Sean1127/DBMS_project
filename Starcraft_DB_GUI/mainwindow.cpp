#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Dialog w;
    w.show();
    w.exec();

    ui->setupUi(this);
    SQLEditor = new SQLEdit();
    ui->verticalLayout->addWidget(SQLEditor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_actionOpen_triggered()
{
    path = QFileDialog::getOpenFileName(this, tr("Open"), "/home/sean", tr("Database (*.db)"));
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if (!db.open()) {
        QMessageBox::warning(this, "Warning", "Error: cannot open \"" + path + "\"");
    }
}

void MainWindow::on_actionExit_triggered()
{
    QMainWindow::close();
}

void MainWindow::on_actionSave_as_triggered()
{
    path = QFileDialog::getSaveFileName(this, tr("Save"), "/home/sean", tr("Database (*.db)"));
}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery q(db);
    if (!q.exec(SQLEditor->toPlainText())) {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText(q.lastError().text());
    }

    //while (query.next()) {
    //    str.append(query.value(1).toString() + " ");
    //}
    //ui->label->setText(str);
}
