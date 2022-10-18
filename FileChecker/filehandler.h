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

public:
    FileHandler(QWidget* pParent);

    ///Возвращает строку с контрольнной суммой файла
    ///filepath - путь к файлу
    QString calcChecksumm(const QString& filepath);

    ///Возвращает пару строка - число, где строка краткое описание результата работы, число - статус проверки.ы
    QPair<QString, int> compareSumms(const QString& filepath, const QString& checksumm);
    QStringList readFile();
    bool writeToFile(const QStringList& data);
    QString chooseFileToRead(const QString& extension = "");
    QString chooseFileToSave();



};

#endif // FILEHANDLER_H
