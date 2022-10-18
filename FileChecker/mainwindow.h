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

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<QLabel*> filepathsLabels;
    QList<QLabel*> checksumsLabels;
    QList<QPushButton*> statusIndicates;
    QString sep = ":";

    FileHandler* filehandler;

    QLabel* createLabelWithSize(const QString& text, double h, double w);

private slots:
    void loadFile();
    void saveFile();

};
#endif // MAINWINDOW_H
