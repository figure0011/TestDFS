#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setMinimum(5);
    ui->spinBox_2->setMinimum(5);

    QPoint pos;
    QSize size;

    state->RestoreState(pos, size);

    this->move(pos);
    this->resize(size);
}

MainWindow::~MainWindow()
{
    delete ui;
    state->SaveState(this->pos(), this->size());
}

void MainWindow::on_pushButton_clicked()
{
    if(field->isWidgetType()){
        delete field;
    }
    int w = ui->spinBox->value() * 50;
    int h = ui->spinBox_2->value() * 50;
    field = new Field(w, h, this);
    ui->verticalLayout->addWidget(field);
    field->generate();
}

