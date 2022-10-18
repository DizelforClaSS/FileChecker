#include "filehandler.h"
#define DIR_WITH_BEG_FILE "./filecheckers"  // Директория с файлами в которых прописаны пути и контрольные суммы
FileHandler::FileHandler(QWidget *pParent) : parent(pParent)
{

}

QString FileHandler::solveChecksumm(const QString &filepath)
{
        QFile f(filepath);

        if (f.open(QFile::ReadOnly))
        {
            QCryptographicHash hash(QCryptographicHash::Md5);
            return hash.result().toHex();
        }
        return "";

}

QPair<QString, int> FileHandler::compareSumms(const QString &filepath, const QString &checksumm)
{

}

QStringList FileHandler::readFile()
{
    QStringList data;

    QString filepath = chooseFileToRead();
    QFile file(filepath);

    if (!file.open(QIODevice::ReadOnly)) // Проверяем, возможно ли открыть файл для чтения
            return data; // если это сделать невозможно, то завершаем функцию

    while(!file.atEnd())
        data.append(file.readLine()); //считываем все данные с файла в объект data

    return data;
}

bool FileHandler::writeToFile(const QStringList &data)
{

}


QString FileHandler::chooseFileToRead()
{
    QDir dir;                      // sAppPathConfig - путь к начальной папке
    dir.mkdir(DIR_WITH_BEG_FILE); 	//Создаем папку если ее нет.
    dir.cd(DIR_WITH_BEG_FILE);     //Переходим в папку с конфиг файлами

    //Открываем окно выбора для загрузки файла
    QString filename = QFileDialog::getOpenFileName(parent, tr("Открыть файл"), dir.path(), tr("TXT files (*.txt)"));

    return filename;
}

QString FileHandler::chooseFileToSave()
{

}
