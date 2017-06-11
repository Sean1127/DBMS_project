#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label->setText("Welcome to StarCraft Database GUI\n");
    ui->label_2->setText("\tFor SQL rookies, choose 'Junior' tab and\n"
                         "\tclick the buttons to start exploring.\n\n"
                         "\tFor senior user, choose 'Senior' tab to\n"
                         "\twrite SQL commands and execute them\n"
                         "\tdirectly");

    QPixmap pixmap(":/wall2-1280x1024.jpg");
    pixmap = pixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, pixmap);
    this->setPalette(palette);
}

Dialog::~Dialog()
{
    delete ui;
}
