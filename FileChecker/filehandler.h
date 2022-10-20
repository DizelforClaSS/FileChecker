#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <QObject>
#include <QPair>
#include <QFile>
#include <QCryptographicHash>
#include <QDir>
#include <QFileDialog>
#include <QWidget>
class FileHandler : public QObject
{
    Q_OBJECT

    QWidget* parent;
    QString sep;

public:
    FileHandler(QWidget* pParent, const QString& sep);

    ///Возвращает строку с контрольнной суммой файла находящегося по пути filepath
    QString calcChecksumm(const QString& filepath);

    ///Чтение файла, возвращает список путей файлов и их контрольные суммы
    QStringList readFile();

    ///Записывает данные data в файл
    bool writeToFile(const QStringList& data);

    ///Открывает диаологовое окно для выбора файла с расширением extension
    QString chooseFileToRead(const QString& extension = "");

    ///Открывает диаологовое окно для выбора места сохранения файла
    QString chooseFileToSave();



};

#endif // FILEHANDLER_H
