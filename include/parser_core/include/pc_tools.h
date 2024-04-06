#pragma once
#include "pc_variables.h"

namespace TOOLS{

bool checkStart(const QString & line1, const QString & line2);

bool checkEnd(const QString & line1, const QString & line2);

PARSER::SEPARATOR_TYPE checkSeparator(const QString & line);

bool isSeparator(const QString & );

bool isDigit(const QString &text);

QString getWord(const QString &str, int position);

QString getLastLine(QString str, int step);

};
