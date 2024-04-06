#pragma once

#include <QString>

namespace TOOLS{

QString getLastLine(QString str, int step = 2);

QString getWord(const QString &, int position);

bool isDigit(const QString &);

};
