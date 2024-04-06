#pragma once

#include <quazip/quazip.h>
#include <quazip/quazipfile.h>
#include <QByteArray>
#include <QBuffer>

#include <list>
#include <utility>

using std::list, std::pair;

class FileUnzip {

public:
    //list of unzipped files
    list<pair<QString, QByteArray *>> unzip(QByteArray *);

};
