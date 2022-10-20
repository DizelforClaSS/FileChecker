#include "filehandler.h"
#define DIR_WITH_BEG_FILE "./filecheckers"  // Директория с файлами в которых прописаны пути и контрольные суммы
FileHandler::FileHandler(QWidget *pParent, const QString &sep) : parent(pParent), sep(sep){}

QString FileHandler::calcChecksumm(const QString &filepath)
{
    QFile f(filepath);

    if (!f.exists())
        throw QString("Файл отсутствует!");

    if (!f.open(QFile::ReadOnly))
        throw QString("Файл невозможно открыть!");

    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(&f);
    QString sum = hash.result().toHex();
    return sum ;
}



QStringList FileHandler::readFile()
{
    QStringList data;

    QString filepath = chooseFileToRead("TXT files (*.txt)");
    QFile file(filepath);

    if (!file.open(QIODevice::ReadOnly)) // Проверяем, возможно ли открыть файл для чтения
            return data; // если это сделать невозможно, то завершаем функцию

    while(!file.atEnd())
    {
        QString str = file.readLine().trimmed();
        if(str.indexOf(sep) < 0)
            continue;


        QStringList pair = str.split(sep);  //Разделяем по разделителю для проверки строки
        if(pair.length() != 2)
            continue;

        pair[0] = pair[0].trimmed();        //Убираем все пустые символы
        if(pair[0].isEmpty())               //Если часть с полным путем файла пустой пропускаем
            continue;

        if(pair[0].indexOf('.') < 0 && pair[0].lastIndexOf('.') == str.length() - 1) //На проверку пропускаем только файлы ("filename.extension")
            continue;

        pair[1] = pair[1].trimmed();        //Убираем все пустые символы
        str = pair[0]+sep+pair[1];

        if(!str.isEmpty())
            data.append(str); //считываем все данные с файла в объект data
        }
    file.close();
    return data;
}

bool FileHandler::writeToFile(const QStringList &data)
{
    QString filepath = chooseFileToSave();
    QFile file(filepath);
    if(!file.open(QIODevice::WriteOnly))
        return 0;

    for(auto d : data)
        file.write(QByteArray::fromStdString(d.toStdString() + "\n")); //Построчно записываем абсолютные пути файлов и их контрольные суммы

    file.close();
}


QString FileHandler::chooseFileToRead(const QString& extension)
{
    QDir dir;
    dir.mkdir(DIR_WITH_BEG_FILE); 	//Создаем папку если ее нет.
    dir.cd(DIR_WITH_BEG_FILE);     //Переходим в папку с конфиг файлами

    //Открываем окно выбора для загрузки файла
    QString filename = QFileDialog::getOpenFileName(parent, tr("Открыть файл"), dir.path(), extension);

    return filename;
}

QString FileHandler::chooseFileToSave()
{
    QDir dir;                      // sAppPathConfig - путь к начальной папке
    dir.mkdir(DIR_WITH_BEG_FILE); 	//Создаем папку если ее нет.
    dir.cd(DIR_WITH_BEG_FILE);     //Переходим в папку с конфиг файлами

    //Открываем окно выбора для загрузки файла
    QString filename = QFileDialog::getSaveFileName(parent, tr("Открыть файл"), dir.path(), tr("TXT files (*.txt)"));

    return filename;
}
