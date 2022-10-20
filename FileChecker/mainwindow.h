#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

#include <filehandler.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
     Q_OBJECT

    /// Собственный класс кнопки, который хранит в себе индекс, означающий где он находится на ui
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
    ///Список надписей с путями к файлам
    QList<QLabel*> filepathsLabels;
    ///Список надписей с контрольными суммами к файлам
    QList<QLabel*> checksumsLabels;
    ///Список индикаторов
    QList<PushButtonWithIndex*> statusIndicates;
    ///Список кнопок проверки
    QList<PushButtonWithIndex*> checkButtons;
    ///Список кнопок удаления
    QList<PushButtonWithIndex*> delButtons;
    ///Список кнопок высчитывания контр. сумм
    QList<PushButtonWithIndex*> calcButtons;
    ///Список кнопок замены файла
    QList<PushButtonWithIndex*> changeFileButtons;

    ///Знак разделения пути файла и контрольной суммы в файле
    QString sep = "|";

    ///Список цветов под статус проверки
    static const QStringList styleStatus;

    ///Объект управляющий файлами (чтение, запись, подсчет сумм)
    FileHandler* filehandler;

    ///Список путей файлов с их контрольными суммами
    QStringList loadedData;

    ///Создает надпись с text, высотой h и длиной w
    QLabel* createLabelWithSize(const QString& text, double h, double w);

    ///Создает индикатор статуса проверки файла находящегося по индексу index
    PushButtonWithIndex* createStatusInd(int index, int status = 0);

    ///Изменяет цвет индикатора but, по статусу status
    void setStyleStatus (PushButtonWithIndex* but, int status);

    ///Добавляет последние данные из списков на ui
    void addDataToUI();

    ///Чистит весь ui от кнопок и надписей
    template<typename T>
    void clearWidgetsList(QList<T*>& list);

    ///Создает надписи и кнопки по str, добавляя их в списки
    void createDataRow(const QString& str);

    ///Удаляет виджеты с ui по индексу index
    void deleteWidgetsOnRow(int index);

    ///Проверяет дубликаты путей
    bool checkDoublePath(const QString& filepath);

    ///Выводит ошибки в messageBox
    void messageBox(const QString& message);

private slots:
    void loadFile();
    void saveFile();
    void addFileToCheck();
    void deleteOne();
    void deleteAll();
    void calcCheckSumOne(int index = -1);
    void calcAll();
    void checkSumOne(int index = -1);
    void checkAll();
    void changeFile();

};
#endif // MAINWINDOW_H
