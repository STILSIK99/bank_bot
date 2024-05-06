#pragma once

#include <QString>
#include <vector>
#include <QSsl>


namespace POST_SERVER{

const std::vector<QSsl::SslProtocol>
    PROTOCOLS = {
        QSsl::TlsV1SslV3, QSsl::TlsV1_2OrLater, QSsl::TlsV1_2,
        QSsl::TlsV1_1OrLater, QSsl::TlsV1_1, QSsl::TlsV1_0OrLater,
        QSsl::TlsV1_0
};

const int IMAP_PORT = 993;
const bool WITHOUT_REQUEST = 1;

namespace COMMANDS{
const QString CAPABILITY = "CAPABILITY";
const QString LOGIN = "LOGIN %1 %2";
const QString SELECT = "SELECT INBOX";
const QString FETCH = "FETCH %1";
const QString LOGOUT = "LOGOUT";
const QString FETCH_BODY = "FETCH %1 (BODY[TEXT])";
const QString FETCH_HEADER = "FETCH %1 (BODY[HEADER])";
const QString FLAGED_MESSAGE = "STORE %1 +FLAGS \\Deleted";
const QString DELETE_MESSAGES = "EXPUNGE";
}

namespace COMMAND_NAMES{
const QString CAPABILITY = "CAPABILITY";
const QString LOGIN = "LOGIN";
const QString SELECT = "SELECT";
const QString FETCH = "FETCH";
const QString LOGOUT = "LOGOUT";
}

namespace STRINGS{
const QString ACCESS = "[READ-WRITE]";
const QString FETCH_BODY = "(BODY[TEXT]";
const QString FETCH_HEADER = "(BODY[HEADER]";
const QString COMPLETED = "completed";
}


}
