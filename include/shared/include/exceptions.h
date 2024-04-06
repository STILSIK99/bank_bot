#pragma once

#include <exception>

#include <QString>
#include <string>

namespace EXCEPTIONS{

const std::string CONFIG_FORMAT = "Format corrupt.\n\0";    //"Формат файла конфигурации некорректен.";
const std::string CONFIG_ACCESS = "Access denied.\n\0";   //"Файл конфигурации недоступен.";

const std::string STATE_FORMAT = "Format corrupt.\n\0";   //"Файл не соответствует формату.";
const std::string STATE_PARAMETER = "Parametr corrupt.\n\0";   //"Параметр задан не корректно.";
const std::string VARIABLES_NOT_FOUND = "Variables not found. Check source code. \"include/other/variables.h.\"";

const std::string DATABASE_DONOT_AVAILABLE = "Database isn't available.";

const std::string MESSAGE_DONOT_SEND = "Message don't send.";

class CodeException : public std::exception{
    std::string message;
    std::string prefix = "Code: ";

public:
    const char* what() const noexcept override{
        return message.c_str();
    }

    CodeException(std::string _m){
        message = prefix + _m;
    }
};


class ConfigException : public std::exception{
    std::string message;
    std::string prefix = "Config: ";

public:
    const char* what() const noexcept override{
        return message.c_str();
    }

    ConfigException(std::string _m){
        message = prefix + _m;
    }
};


class StatementException : public std::exception{
    std::string message;
    std::string prefix = "Statement: ";

public:
    const char* what() const noexcept override{
        return message.c_str();
    }

    StatementException(std::string _m){
        message = prefix + _m;
    }
};

class CoreException : public std::exception{
    std::string message;
    std::string prefix = "Core: ";

public:
    const char* what() const noexcept override{
        return message.c_str();
    }

    CoreException(std::string _m){
        message = prefix + _m;
    }
};

class SocketException : public std::exception{
    std::string message;
    std::string prefix = "Socket: ";

public:
    const char* what() const noexcept override{
        return message.c_str();
    }

    SocketException(std::string _m){
        message = prefix + _m;
    }
};

}


