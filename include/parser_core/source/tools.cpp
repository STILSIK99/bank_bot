#include "pc_tools.h"

bool TOOLS::checkStart(const QString & line1, const QString & line2){
    auto end = std::min(line1.length(), line2.length());
    if (end == 0) return false;
    for(auto i = 0; i < end; ++i){
        if (line1[i] != line2[i]) return false;
    }
    return true;
}


bool TOOLS::checkEnd(const QString & line1, const QString & line2){
    int size1 = line1.size(),
        size2 = line2.size();
    int size = std::min(size1, size2);
    for (int i = 1; i <= size; ++i){
        if (line1[size1 - i] != line2[size2 - i]) {
            return false;
        }
    }
    return true;
}


PARSER::SEPARATOR_TYPE TOOLS::checkSeparator(const QString & line){
    if (!isSeparator(line)){
        return PARSER::SEPARATOR_TYPE::NO;
    }
    if (line.length() > 17 && line[17] == 'E'){
        return PARSER::SEPARATOR_TYPE::ENCODING;
    }
    if (line.length() > 9 && line[9] == 'y'){
        return PARSER::SEPARATOR_TYPE::TYPE;
    }
    if (line.length() > 8 && line[8] == 'D'){
        return PARSER::SEPARATOR_TYPE::DISPOSITION;
    }
    if (line.length() > 5 && line[5] == 'n'){
        return PARSER::SEPARATOR_TYPE::FILENAME;
    }
    if (line.length() > 8 && line[0] == '-' && line[8] == 'P'){
        return PARSER::SEPARATOR_TYPE::PART;
    }
    if (line.length() > 9 && line[0] == '<' && line[1] == '!'){
        return PARSER::SEPARATOR_TYPE::HTML;
    }
    return PARSER::SEPARATOR_TYPE::NO;
}

bool TOOLS::isSeparator(const QString &line){
    for(auto sep : PARSER::SEPARATOR::ALL){
        if (TOOLS::checkStart(line, sep)){
            return true;
        }
    }
    return false;
}


























