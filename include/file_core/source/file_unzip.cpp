#include "file_unzip.h"

list<pair<QString, QByteArray *>> FileUnzip::unzip(QByteArray *zipData){
    QBuffer *buffer = new QBuffer(zipData);
    QuaZip zip(buffer);
    zip.open(QuaZip::mdUnzip);
    QuaZipFile zipFile(&zip);
    std::list<std::pair<QString, QByteArray *>> result;
    for(bool next = zip.goToFirstFile(); next; next = zip.goToNextFile()){
        if (!zipFile.open(QIODevice::ReadOnly)) continue;
        result.emplace_back(
            std::make_pair(
                zipFile.getActualFileName(),
                new QByteArray(zipFile.readAll())));
        zipFile.close();
    }
    zip.close();
    delete zipData;
    return result;
}
