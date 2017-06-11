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
    SQLEditor->setFont(QFont("Courier 10 pitch",11));
    ui->verticalLayout_2->addWidget(SQLEditor);

    initComboButton();

    ui->comboBox_2->setMinimumWidth(ui->comboBox_2->minimumSizeHint().width());
    ui->pushButton_2->setMaximumWidth(80);
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

void MainWindow::on_actionOpen_triggered()
{
    path = QFileDialog::getOpenFileName(this, tr("Open"), "/home/sean", tr("Database (*.db)"));

    if (database.isOpen()) {
        database.close();
        database = QSqlDatabase();
        database.removeDatabase(QSqlDatabase::database().connectionName());
    }

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path);
    if (!database.open()) {
        QMessageBox::warning(this, "Warning", "Error: cannot open \"" + path + "\"");
        return;
    }

    ui->comboBox->clear();
    ui->comboBox->addItems(database.tables());
    ui->comboBox->setMinimumWidth(ui->comboBox->minimumSizeHint().width());
}

void MainWindow::on_actionExit_triggered()
{
    database.close();
    QMainWindow::close();
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

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery query(database);
    query.exec(ui->lineEdit_2->text());

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(ui->lineEdit_2->text());
    ui->tableView_1->setModel(model);
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    tableModel = new QSqlTableModel(this, database);
    tableModel->setTable(arg1);
    tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    tableModel->select();

    ui->tableView_1->setModel(tableModel);
}

void MainWindow::on_comboBox_2_activated(int index)
{
    QString str;
    switch (index) {
    case 0:
        str = "SELECT Name,HP "
              "FROM UNIT "
              "WHERE Race='Zerg'";
        break;
    case 1:
        str = "INSERT INTO BUILDING(ID,Name,Race,Cost_minerals,Cost_gas,Build_time,HP,Def,Unlock_by,Build_by) "
              "VALUES(18,'Spawning Pool','Zerg',200,0,50,750,1,17,19)";
        break;
    case 2:
        str = "DELETE FROM BUILDING "
              "WHERE ID=18";
        break;
    case 3:
        str = "UPDATE UNIT "
              "SET Energy=250 "
              "WHERE ID=4";
        break;
    case 4:
        str = "SELECT * "
              "FROM SPELL "
              "WHERE Cast_by "
              "IN(SELECT ID "
              "FROM UNIT "
              "WHERE Cost_gas=0)";
        break;
    case 5:
        str = "SELECT * "
              "FROM SPELL "
              "WHERE Cast_by "
              "NOT IN(SELECT ID "
              "FROM UNIT "
              "WHERE Cost_gas=0)";
        break;
    case 6:
        str = "SELECT Name,HP,Shield "
              "FROM BUILDING B "
              "WHERE EXISTS"
              "(SELECT * "
              "FROM UPGRADE "
              "WHERE Building_ID=B.ID)";
        break;
    case 7:
        str = "SELECT * "
              "FROM COMMAND C "
              "WHERE NOT EXISTS"
              "(SELECT * "
              "FROM UNIT "
              "WHERE ID=C.Act_by)";
        break;
    case 8:
        str = "SELECT COUNT(*) "
              "FROM UNIT "
              "WHERE Shield IS NULL";
        break;
    case 9:
        str = "SELECT SUM(Cost_minerals),SUM(Cost_gas) "
              "FROM UPGRADE "
              "WHERE Name LIKE '%Air Weapon%'";
        break;
    case 10:
        str = "SELECT U.Name,S.* "
              "FROM SPELL S,UNIT U "
              "WHERE Cast_by=U.ID AND Radius IN"
              "(SELECT MAX(Radius)"
              "FROM SPELL)";
        break;
    case 11:
        str = "SELECT Name "
              "FROM BUILDING "
              "WHERE Build_time IN"
              "(SELECT MIN(Build_time) "
              "FROM BUILDING)";
        break;
    case 12:
        str = "SELECT AVG(U.Cost_minerals) "
              "FROM UNIT U,BUILDING B "
              "WHERE U.Produce_by=B.ID AND B.Name='Gateway'";
        break;
    case 13:
        str = "SELECT Size,COUNT(*) "
              "FROM Unit "
              "WHERE Atk_type_g>10 "
              "GROUP BY Size "
              "HAVING Type='Ground'";
        break;
    }

    ui->lineEdit_2->setText(str);
}
