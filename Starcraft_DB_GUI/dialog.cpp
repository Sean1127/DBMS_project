#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label->setText("Welcome to StarCraft Database GUI:\n\n"
                       "\tFor SQL rookies, choose 'Junior' tab and click\n"
                       "\tthe buttons to start exploring.\n\n"
                       "\tFor senior user, choose 'Senior' tab to write\n"
                       "\tSQL commands and execute them directly");
}

Dialog::~Dialog()
{
    delete ui;
}
