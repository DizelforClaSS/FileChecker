#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filehandler = new FileHandler(this);
    connect(ui->loadButton, &QAction::triggered, this, &MainWindow::loadFile);
    connect(ui->addNewFileButton, &PushButtonWithIndex::clicked, this, &MainWindow::addFile);
    connect(ui->saveButton, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->clearAllButton, &QPushButton::clicked, this, &MainWindow::deleteAll);
    this->setFixedSize(1070, 610);
}

//TO DO Исправить баг с наложением

template<typename  T>
void MainWindow::clearWidgetsList(QList<T*>& list)
{
    for(auto l : list)
        delete l;
    list.clear();
}

MainWindow::~MainWindow()
{
    deleteAll();
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

        addStrDataToUI(str);
    }
}

void MainWindow::saveFile()
{
    filehandler->writeToFile(loadedData);
}

void MainWindow::addFile()
{
    QString filepath = filehandler->chooseFileToRead();
    if (filepath.isEmpty())
        return;
    if(loadedData.contains(filepath + sep))
        return;
    addStrDataToUI(filepath+sep);

}

void MainWindow::deleteOne()
{
    PushButtonWithIndex* but = dynamic_cast<PushButtonWithIndex*>(sender());
    int index = but->getIndex();
    delete filepathsLabels[index];
    filepathsLabels.remove(index);

    delete checksumsLabels[index];
    checksumsLabels.remove(index);

    delete statusIndicates[index];
    statusIndicates.remove(index);

    delete checkButtons[index];
    checkButtons.remove(index);

    delete delButtons[index];
    delButtons.remove(index);

    loadedData.remove(index);
    for(int i = index; i < delButtons.size(); i++)
    {
        delButtons[i]->setIndex(i);
    }

    for(int i = index; i < checkButtons.size(); i++)
    {
        checkButtons[i]->setIndex(i);
    }
}

void MainWindow::deleteAll()
{
    clearWidgetsList(filepathsLabels);
    clearWidgetsList(checksumsLabels);
    clearWidgetsList(statusIndicates);
    clearWidgetsList(checkButtons);
    clearWidgetsList(delButtons);
    loadedData.clear();
}


const QStringList MainWindow::styleStatus = {"gray;", "red;", "green;"};

MainWindow::PushButtonWithIndex* MainWindow::createStatusInd(int status, int index)
{
   PushButtonWithIndex* b = new PushButtonWithIndex(index);
   setStyleStatus(b, status);
   return  b;
}

void MainWindow::setStyleStatus(PushButtonWithIndex *but, int status)
{
    but->setStyleSheet("background-color: " + styleStatus[status] +
                     "border-style: outset;"
                     "border-radius: 10px;"
                     "border-color: beige;"
                       );
}

void MainWindow::addDataToUI()
{
    int index = filepathsLabels.size()-1;

    ui->wsLayout->addWidget(filepathsLabels.last(), index,  0);
    ui->wsLayout->addWidget(checksumsLabels.last(), index, 1);
    ui->wsLayout->addWidget(statusIndicates.last(), index , 2);
    ui->wsLayout->addWidget(checkButtons.last(), index, 3);
    ui->wsLayout->addWidget(delButtons.last(), index, 4);
}

void MainWindow::addStrDataToUI(const QString &str)
{
    loadedData.append(str);
    QStringList pathAndsumm = str.split(sep);
    filepathsLabels.append(createLabelWithSize(pathAndsumm[0], 30, 600));
    checksumsLabels.append(createLabelWithSize(pathAndsumm[1], 30, 300));
    statusIndicates.append(createStatusInd(0, filepathsLabels.size() - 1));
    checkButtons.append(new PushButtonWithIndex(filepathsLabels.size() - 1));
    delButtons.append(new PushButtonWithIndex(filepathsLabels.size() - 1));
    connect(delButtons.last(), &QPushButton::clicked, this, &MainWindow::deleteOne);
    addDataToUI();
}

