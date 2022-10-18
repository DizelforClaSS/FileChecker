#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

#include <filehandler.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
     Q_OBJECT

    class PushButtonWithIndex : public QPushButton
    {
      int index;
        public:
          PushButtonWithIndex(int i) : index(i){}
          void setIndex(int i){index = i;}
          int getIndex(){return index;}
    };

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<QLabel*> filepathsLabels;
    QList<QLabel*> checksumsLabels;
    QList<PushButtonWithIndex*> statusIndicates;
    QList<PushButtonWithIndex*> checkButtons;
    QList<PushButtonWithIndex*> delButtons;
    QList<PushButtonWithIndex*> calcButtons;

    QString sep = "|";

    static const QStringList styleStatus;

    FileHandler* filehandler;
    QStringList loadedData;

    QLabel* createLabelWithSize(const QString& text, double h, double w);
    PushButtonWithIndex* createStatusInd(int status, int index);
    void setStyleStatus (PushButtonWithIndex* but, int status);
    void addDataToUI();

    template<typename T>
    void clearWidgetsList(QList<T*>& list);
    void addStrDataToUI(const QString& str);


private slots:
    void loadFile();
    void saveFile();
    void addFile();
    void deleteOne();
    void deleteAll();
    void calcCheckSumOne(int index = -1);
    void calcAll();
    void checkSumOne(int index = -1);
    void checkAll();

};
#endif // MAINWINDOW_H
