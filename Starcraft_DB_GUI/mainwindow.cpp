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
    ui->verticalLayout_2->addWidget(SQLEditor);

    initComboButton();

    ui->comboBox_2->setMinimumWidth(ui->comboBox_2->minimumSizeHint().width());
    ui->comboBox->setMinimumWidth(ui->comboBox_2->width());
    ui->label_2->setMinimumWidth(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initComboButton()
{
    ui->comboBox_2->addItem("SELECT");
    ui->comboBox_2->addItem("INSERT");
    ui->comboBox_2->addItem("DELETE");
    ui->comboBox_2->addItem("UPDATE");
    ui->comboBox_2->addItem("IN");
    ui->comboBox_2->addItem("NOT IN");
    ui->comboBox_2->addItem("EXIST");
    ui->comboBox_2->addItem("NOT EXIST");
    ui->comboBox_2->addItem("COUNT");
    ui->comboBox_2->addItem("SUM");
    ui->comboBox_2->addItem("MAX");
    ui->comboBox_2->addItem("MIN");
    ui->comboBox_2->addItem("AVG");
    ui->comboBox_2->addItem("HAVING");
}

void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_actionOpen_triggered()
{
    if (database.isOpen()) {
        database.close();
        database.removeDatabase("qt_sql_default_connection");
    }

    path = QFileDialog::getOpenFileName(this, tr("Open"), "/home/sean", tr("Database (*.db)"));

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path);
    if (!database.open()) {
        QMessageBox::warning(this, "Warning", "Error: cannot open \"" + path + "\"");
        return;
    }

    ui->comboBox->addItems(database.tables());
    ui->comboBox->setMinimumWidth(7);
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

void MainWindow::on_pushButton_2_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(SQLEditor->toPlainText());
    if (model->lastError().isValid()) {
        ui->lineEdit->setText(model->lastError().text());
    }
    ui->tableView_2->setModel(model);
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    tableModel = new QSqlTableModel(this, database);
    tableModel->setTable(arg1);
    tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    tableModel->select();

    ui->tableView_1->setModel(tableModel);
}

void MainWindow::on_pushButton_clicked()
{
    QString str;
    switch (ui->comboBox_2->currentIndex()) {
    case 0:
        str = "SELECT Name,HP "
              "FROM UNIT "
              "WHERE Race='Zerg'";
        break;
    case 1:
        str = "INSERT INTO BUILDING(ID,Name,Race,Cost_minerals,Cost_gas,Build_time,"
              "HP,Def,Unlock_by,Build_by) "
              "VALUES(18,'Spawning Pool','Zerg',200,0,50,750,1,17,19)";
        break;
    case 2:
        str = "DELETE FROM BUILDING "
              "WHERE ID=18";
        break;
    case 3:
        str = "UPDATE ";
        break;
    case 4:
        str = "";
        break;
    case 5:
        str = "";
        break;
    case 6:
        str = "";
        break;
    case 7:
        str = "";
        break;
    case 8:
        str = "";
        break;
    case 9:
        str = "";
        break;
    case 10:
        str = "";
        break;
    case 11:
        str = "";
        break;
    case 12:
        str = "";
        break;
    case 13:
        str = "";
        break;
    }

    qDebug()<<str;

    QSqlQuery query(database);
    query.exec(str);

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(str);
    ui->tableView_1->setModel(model);
}
