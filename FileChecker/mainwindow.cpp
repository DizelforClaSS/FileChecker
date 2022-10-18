#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filehandler = new FileHandler(this);
    connect(ui->loadButton, &QAction::triggered, this, &MainWindow::loadFile);
    this->setFixedSize(1070, 610);
}

//TO DO Функция добавления файла на рабочее пространство (Путь к файлу, контрольная сумма, статус) -- + добавление кнопки удаления
//TO DO Удаление одного объекта (файла)
//TO DO Очистка рабочего пространства
MainWindow::~MainWindow()
{
    delete ui;
    delete filehandler;
}

QLabel *MainWindow::createLabelWithSize(const QString &text, double h, double w)
{
   QLabel* label = new QLabel(text);
   label->setMinimumSize(w, h);
   return label;
}



void MainWindow::loadFile()
{
    QStringList data = filehandler->readFile();
    for(auto str : data)
    {
        QStringList pathAndsumm = str.split(sep);
        filepathsLabels.append(createLabelWithSize(pathAndsumm[0], 30, 600));
        checksumsLabels.append(createLabelWithSize(pathAndsumm[1], 30, 300));
        statusIndicates.append(new QPushButton());

        statusIndicates.last()->setStyleSheet("background-color: gray;"
                                                "border-style: outset;"
                                                "border-radius: 10px;"
                                                "border-color: beige;"
                    );

        ui->wsLayout->addWidget(filepathsLabels.last(), filepathsLabels.size()-1, 0);
        ui->wsLayout->addWidget(checksumsLabels.last(), filepathsLabels.size()-1, 1);
        ui->wsLayout->addWidget(statusIndicates.last(), filepathsLabels.size()-1, 2);

    }
}

void MainWindow::saveFile()
{

}

