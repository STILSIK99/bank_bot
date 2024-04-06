#include "imap_tools.h"

QString TOOLS::getLastLine(QString str, int step){
    for(int i = str.length() - 1 - step; i > 1; --i){
        if (str[i] == '\n' && str[i - 1] == '\r'){
            return str.right(str.length() - i - 1);
        }
    }
    return str;
};

QString TOOLS::getWord(const QString &str, int position){
    if (position < 1) return "";
    int left = 0, right = 0;
    for(; right < str.length(); ++right){
        if (str[right] == ' '){
            if (!(--position)){
                break;
            }
            else{
                left = right + 1;
            }
        }
    }
    if (left >= right || position > 1) return "";
    return str.mid(left, right - left);
}

bool TOOLS::isDigit(const QString &text){
    for(auto s : text){
        if (s < '0' || s > '9')
            return false;
    }
    return true;
}
