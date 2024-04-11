#pragma once
#include <QString>
#include <QFile>

#include "parser_core.h"
#include "data_storage.h"
#include "config_core.h"

namespace TEST{

bool testDecodeBase64(const QString & base64);

bool testParseStatement();

bool testDataBaseConnection();

bool testConfig();

}

