#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filehandler = new FileHandler(this, sep);
    this->setFixedSize(1200, 800);

    connect(ui->loadButton, &QAction::triggered, this, &MainWindow::loadFile);
    connect(ui->addNewFileButton, &PushButtonWithIndex::clicked, this, &MainWindow::addFileToCheck);
    connect(ui->saveButton, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->clearAllButton, &QPushButton::clicked, this, &MainWindow::deleteAll);
    connect(ui->calcAllFilesButton, &QPushButton::clicked, this, &MainWindow::calcAll);
    connect(ui->checkAllFilesButton, &QPushButton::clicked, this, &MainWindow::checkAll);
}

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
      createDataRow(str);
    }
}

void MainWindow::saveFile()
{
    filehandler->writeToFile(loadedData);
}

void MainWindow::addFileToCheck()
{

    QString filepath = filehandler->chooseFileToRead();

    if(checkDoublePath(filepath))
    {
        messageBox("Такой файл уже есть в системе!");
        return;
    }

    if (filepath.isEmpty())
        return;


    createDataRow(filepath+sep);
}

void MainWindow::deleteOne()
{
    PushButtonWithIndex* but = dynamic_cast<PushButtonWithIndex*>(sender());
    int index = but->getIndex();

    deleteWidgetsOnRow(index);
    loadedData.remove(index);



    for(int i = index; i < checkButtons.size(); i++)
    {
        delButtons[i]->setIndex(i);
        statusIndicates[i]->setIndex(i);
        checkButtons[i]->setIndex(i);
        calcButtons[i]->setIndex(i);
        changeFileButtons[i]->setIndex(i);
        ui->wsLayout->addWidget(filepathsLabels[i], i,  0);
        ui->wsLayout->addWidget(checksumsLabels[i], i, 1);
        ui->wsLayout->addWidget(statusIndicates[i], i , 2);
        ui->wsLayout->addWidget(checkButtons[i], i, 3);
        ui->wsLayout->addWidget(delButtons[i], i, 4);
        ui->wsLayout->addWidget(calcButtons[i], i, 5);
        ui->wsLayout->addWidget(changeFileButtons[i], i, 6);
    }
}

void MainWindow::deleteAll()
{
    clearWidgetsList(filepathsLabels);
    clearWidgetsList(checksumsLabels);
    clearWidgetsList(statusIndicates);
    clearWidgetsList(checkButtons);
    clearWidgetsList(delButtons);
    clearWidgetsList(calcButtons);
    clearWidgetsList(changeFileButtons);
    loadedData.clear();
}

void MainWindow::calcCheckSumOne(int index)
{
    QString filepath;
    QString checksum;
    QObject* s = sender();
    try {

        if(s != ui->calcAllFilesButton)
            index = dynamic_cast<PushButtonWithIndex*>(sender())->getIndex();

        filepath = filepathsLabels[index]->text();
        checksum = filehandler->calcChecksumm(filepath);
        setStyleStatus(statusIndicates[index], 2);
        statusIndicates[index]->setToolTip("Is correct");
        checksumsLabels[index]->setText(checksum);
        loadedData[index] = filepath + sep + checksum;

    }  catch (QString ex) {
        setStyleStatus(statusIndicates[index], 1);
        statusIndicates[index]->setToolTip(ex);
    }
}

void MainWindow::calcAll()
{
    for (int i = 0; i < filepathsLabels.size(); i++)
        calcCheckSumOne(i);

}

void MainWindow::checkSumOne(int index)
{
    QString filepath;
    QString checksum;
    QObject* s = sender();

    try {

        if(s != ui->checkAllFilesButton)
            index = dynamic_cast<PushButtonWithIndex*>(sender())->getIndex();

        filepath = filepathsLabels[index]->text();
        checksum = filehandler->calcChecksumm(filepath);
        setStyleStatus(statusIndicates[index], 2);
        if(checksumsLabels[index]->text() != checksum)
            throw QString("Суммы разные");

        statusIndicates[index]->setToolTip("Сумма верная");


    }  catch (QString ex) {
        setStyleStatus(statusIndicates[index], 1);
        statusIndicates[index]->setToolTip(ex);
    }
}

void MainWindow::checkAll()
{
    for (int i = 0; i < filepathsLabels.size(); i++)
        checkSumOne(i);
}

void MainWindow::changeFile()
{
    QString filepath = filehandler->chooseFileToRead();
    if(checkDoublePath(filepath))
    {
        messageBox("Такой файл уже есть в системе!");
        return;
    }

    if(filepath.isEmpty())
        return;

    int index = dynamic_cast<PushButtonWithIndex*>(sender())->getIndex();
    filepathsLabels[index]->setText(filepath);
    checksumsLabels[index]->setText("");
    setStyleStatus(statusIndicates[index], 0);
    loadedData[index] = filepath + sep;
}


const QStringList MainWindow::styleStatus = {"gray;", "red;", "green;"};

MainWindow::PushButtonWithIndex* MainWindow::createStatusInd(int index, int status)
{
   PushButtonWithIndex* b = new PushButtonWithIndex(index);
   setStyleStatus(b, status);
   return  b;
}

void MainWindow::setStyleStatus(PushButtonWithIndex *but, int status)
{
    but->setStyleSheet("QPushButton {background-color: " + styleStatus[status] +
                     "border-style: outset;"
                     "border-radius: 10px;"
                     "border-color: beige;}"

                     "QToolTip {"
                     "background-color: #000000;}"
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
    ui->wsLayout->addWidget(calcButtons.last(), index, 5);
    ui->wsLayout->addWidget(changeFileButtons.last(), index, 6);

    checkButtons.last()->setIconSize(QSize(25, 25));
    checkButtons.last()->setStyleSheet("qproperty-icon: url(:/Resources/checksum.png)");
    checkButtons.last()->setToolTip("Проверить");
    checkButtons.last()->setToolTipDuration(500);

    delButtons.last()->setIconSize(QSize(25, 25));
    delButtons.last()->setStyleSheet("qproperty-icon: url(:/Resources/trash.png)");
    delButtons.last()->setToolTip("Удалить");
    delButtons.last()->setToolTipDuration(500);

    calcButtons.last()->setIconSize(QSize(25, 25));
    calcButtons.last()->setStyleSheet("qproperty-icon: url(:/Resources/sum_icon.png)");
    calcButtons.last()->setToolTip("Вычислить");
    calcButtons.last()->setToolTipDuration(500);

    changeFileButtons.last()->setIconSize(QSize(25, 25));
    changeFileButtons.last()->setStyleSheet("qproperty-icon: url(:/Resources/file_replace.png)");
    changeFileButtons.last()->setToolTip("Заменить");
    changeFileButtons.last()->setToolTipDuration(500);

}

void MainWindow::createDataRow(const QString &str)
{
    loadedData.append(str);
    QStringList pathAndsumm = str.split(sep);
    filepathsLabels.append(createLabelWithSize(pathAndsumm[0], 30, 600));
    checksumsLabels.append(createLabelWithSize(pathAndsumm[1], 30, 300));

    statusIndicates.append(createStatusInd(filepathsLabels.size() - 1));

    calcButtons.append(new PushButtonWithIndex(filepathsLabels.size() - 1));
    connect(calcButtons.last(), &QPushButton::clicked, this, &MainWindow::calcCheckSumOne);

    delButtons.append(new PushButtonWithIndex(filepathsLabels.size() - 1));
    connect(delButtons.last(), &QPushButton::clicked, this, &MainWindow::deleteOne);

    checkButtons.append(new PushButtonWithIndex(filepathsLabels.size() - 1));
    connect(checkButtons.last(), &QPushButton::clicked, this, &MainWindow::checkSumOne);

    changeFileButtons.append(new PushButtonWithIndex(filepathsLabels.size() - 1));
    connect(changeFileButtons.last(), &QPushButton::clicked, this, &MainWindow::changeFile);

    statusIndicates.last()->setToolTip("Файл ещё не проверялся");
    addDataToUI();
}

bool MainWindow::checkDoublePath(const QString &filepath)
{
    for(auto f : filepathsLabels)
    {
        if(f->text() == filepath)
            return true;
    }

    return false;
}

void MainWindow::messageBox(const QString &message)
{
    QMessageBox::warning(this,"Внимание", message);

}

void MainWindow::deleteWidgetsOnRow(int index)
{
    delete filepathsLabels[index];
    delete checksumsLabels[index];
    delete statusIndicates[index];
    delete checkButtons[index];
    delete delButtons[index];
    delete calcButtons[index];
    delete changeFileButtons[index];

    filepathsLabels.remove(index);
    checksumsLabels.remove(index);
    statusIndicates.remove(index);
    checkButtons.remove(index);
    delButtons.remove(index);
    calcButtons.remove(index);
    changeFileButtons.remove(index);
}
