#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filehandler = new FileHandler(this);
    connect(ui->loadButton, &QAction::triggered, this, &MainWindow::loadFile);
    connect(ui->addNewFileButton, &QPushButton::clicked, this, &MainWindow::addFile);
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
      if(loadedData.contains(str))
          continue;

        loadedData.append(str);
        QStringList pathAndsumm = str.split(sep);
        filepathsLabels.append(createLabelWithSize(pathAndsumm[0], 30, 600));
        checksumsLabels.append(createLabelWithSize(pathAndsumm[1], 30, 300));
        statusIndicates.append(createStatusInd(0, filepathsLabels.size() - 1));
        addDataToUI();
    }
}

void MainWindow::saveFile()
{

}

void MainWindow::addFile()
{
    QString filepath = filehandler->chooseFileToRead();
    if (filepath.isEmpty())
        return;
    if(loadedData.contains(filepath))
        return;
    loadedData.append(filepath);
    filepathsLabels.append(createLabelWithSize(filepath, 30, 600));
    checksumsLabels.append(createLabelWithSize("", 30, 300));
    statusIndicates.append(createStatusInd(0, filepathsLabels.size() - 1));
    addDataToUI();
}


const QStringList MainWindow::styleStatus = {"gray;", "red;", "green;"};

QPushButton *MainWindow::createStatusInd(int status, int index)
{
   QPushButton* b = new QPushButton();
   b->setText(QString::number(index));
   setStyleStatus(b, status);
   return  b;
}

void MainWindow::setStyleStatus(QPushButton *but, int status)
{
    but->setStyleSheet("background-color: " + styleStatus[status] +
                     "border-style: outset;"
                     "border-radius: 10px;"
                     "border-color: beige;"
                     "color: " + styleStatus[status]
                       );
}

void MainWindow::addDataToUI()
{
    int index = filepathsLabels.size()-1;

    ui->wsLayout->addWidget(filepathsLabels.last(), index,  0);
    ui->wsLayout->addWidget(checksumsLabels.last(), index, 1);
    ui->wsLayout->addWidget(statusIndicates.last(), index , 2);
}

