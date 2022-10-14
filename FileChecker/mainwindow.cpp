#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

//TO DO Функция добавления файла на рабочее пространство (Путь к файлу, контрольная сумма, статус) -- + добавление кнопки удаления
//TO DO Удаление одного объекта (файла)
//TO DO Очистка рабочего пространства
MainWindow::~MainWindow()
{
    delete ui;
}

