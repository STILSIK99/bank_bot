#pragma once

#include <QString>
#include <set>
#include <vector>

namespace FILE_MODULE{

    enum FileType{
        HEADER,
        BODY,
        ADDITION
    };


};

namespace PARSER{

    namespace SEPARATOR{
        const QString ENCODING = "Content-Transfer-Encoding: base64";
        const QString TYPE = "Content-Type: text/html;charset=UTF-8";
        const QString DISPOSITION = "Content-Disposition: attachment;";
        const QString FILENAME = "	filename*=UTF-8''";
        const QString PART = "------=_Part";
        const QString HTML = "<!DOCTYPE";


        const std::set<QString> ALL = {
            ENCODING, TYPE, DISPOSITION,
            FILENAME, PART, HTML
        };
    }

    enum SEPARATOR_TYPE{
        NO,
        ENCODING,
        TYPE,
        DISPOSITION,
        FILENAME,
        PART,
        HTML
    };

    namespace STRINGS{
        const QString BASE64 = "base64";
        const std::vector<QString> URL2FILE = {
            "<a href=3D\"https",
            "<a title=\"Скачать выписку\" target=\"_blank\" href=\"https:"
        };
    }
};
