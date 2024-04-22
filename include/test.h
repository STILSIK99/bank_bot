#pragma once
#include <QString>
#include <QFile>

#include "parser_core.h"
#include "data_core.h"
#include "config.h"

namespace TEST{

bool testDecodeBase64(const QString & base64);

bool testParseStatement();

bool testDataBaseConnection();

bool testConfig();

}

