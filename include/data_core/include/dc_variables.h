#pragma once
#include <QString>
#include <list>
#include <vector>
#include <map>
namespace DATABASE{



    namespace REQUESTS{
        const std::list<QString> TABLES = {
            "CREATE TABLE IF NOT EXISTS DATA_PROPERTIES("
            "   Id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
            "	Property VARCHAR(20) NOT NULL UNIQUE"
            ");",

            "CREATE TABLE IF NOT EXISTS ACCOUNTS("
            "    Id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
            "    Account DECIMAL(20, 0) NOT NULL UNIQUE"
            ");",

            "CREATE TABLE IF NOT EXISTS DATA("
            "	Account_id INT REFERENCES ACCOUNTS(Id),"
            "	Hash_1_1 DECIMAL(20,0), 	Hash_1_2 DECIMAL(20,0),"
            "   Hash_2_1 DECIMAL(20,0), 	Hash_2_2 DECIMAL(20,0),"
            "   PRIMARY KEY (Hash_1_1, Hash_1_2, Hash_2_1, Hash_2_2),"
            "	Field_1 VARCHAR(50), 	Field_2 DECIMAL(2,0),"
            "	Field_3 VARCHAR(10), 	Field_4 DATE NOT NULL,"
            "	Field_5 DATE,           Field_6 DATE,"
            "	Field_7 DATE,           Field_8 VARCHAR(200),"
            "	Field_9 TIME,           Field_10 DATE,"
            "	Field_11 VARCHAR(50), 	Field_12 DECIMAL(2, 0),"
            "	Field_13 VARCHAR(1), 	Field_14 VARCHAR(100),"
            "	Field_15 VARCHAR(30) NOT NULL,      Field_16 VARCHAR(50),"
            "	Field_17 DECIMAL(11,0),             Field_18 DECIMAL(2,0),"
            "	Field_19 VARCHAR(200), 	Field_20 VARCHAR(300),"
            "	Field_21 DECIMAL(9,0), 	Field_22 VARCHAR(50),"
            "	Field_23 VARCHAR(50), 	Field_24 DECIMAL(12,0) NOT NULL,"
            "	Field_25 DECIMAL(9,0), 	Field_26 DECIMAL(20,0),"
            "	Field_27 DECIMAL(20,0),             Field_28 DECIMAL(20,0) NOT NULL,"
            "	Field_29 DATE,          Field_30 DECIMAL(20, 0),"
            "	Field_31 VARCHAR(50), 	Field_32 DECIMAL(2,0),"
            "	Field_33 DECIMAL(10,0),             Field_34 VARCHAR(1),"
            "	Field_35 VARCHAR(300), 	Field_36 DECIMAL(9,0),"
            "	Field_37 VARCHAR(50), 	Field_38 VARCHAR(50),"
            "	Field_39 DECIMAL(12,0) NOT NULL, 	Field_40 DECIMAL(9,0),"
            "	Field_41 DECIMAL(20,0),             Field_42 DECIMAL(20,0),"
            "	Field_43 DECIMAL(20,0) NOT NULL, 	Field_44 VARCHAR(25),"
            "	Field_45 DECIMAL(5,0), 	Field_46 DATE,"
            "	Field_47 DECIMAL(2,0), 	Field_48 DECIMAL(16,2) NOT NULL,"
            "	Field_49 VARCHAR(100), 	Field_50 VARCHAR(100),"
            "	Field_51 VARCHAR(100) );"
        };

        const std::list<QString> INSERTIONS = {
            "INSERT INTO DATA_PROPERTIES VALUES "
            "(\"ВидАккредитива\", 1),   (\"ВидОплаты\", 2),"
            "(\"ВидПлатежа\", 3),       (\"Дата\", 4),"
            "(\"ДатаОтсылкиДок\", 5),   (\"ДатаПоступило\", 6),"
            "(\"ДатаСписано\", 7),      (\"ДополнУсловия\", 8),"
            "(\"КвитанцияВремя\", 9),   (\"КвитанцияДата\", 10),"
            "(\"КвитанцияСодержание\", 11), (\"Код\", 12),"
            "(\"КодНазПлатежа\", 13),   (\"НазначениеПлатежа\", 14),"
            "(\"Номер\", 15),           (\"НомерСчетаПоставщика\", 16),"
            "(\"ОКАТО\", 17),           (\"Очередность\", 18),"
            "(\"ПлатежПоПредст\", 19),  (\"Плательщик\", 20),"
            "(\"ПлательщикБИК\", 21),   (\"ПлательщикБанк1\", 22),"
            "(\"ПлательщикБанк2\", 23), (\"ПлательщикИНН\", 24),"
            "(\"ПлательщикКПП\", 25),   (\"ПлательщикКорсчет\", 26),"
            "(\"ПлательщикРасчСчет\", 27),  (\"ПлательщикСчет\", 28),"
            "(\"ПоказательДаты\", 29),  (\"ПоказательКБК\", 30),"
            "(\"ПоказательНомера\", 31),    (\"ПоказательОснования\", 32),"
            "(\"ПоказательПериода\", 33),   (\"ПоказательТипа\", 34),"
            "(\"Получатель\", 35),      (\"ПолучательБИК\", 36),"
            "(\"ПолучательБанк1\", 37), (\"ПолучательБанк2\", 38),"
            "(\"ПолучательИНН\", 39),   (\"ПолучательКПП\", 40),"
            "(\"ПолучательКорсчет\", 41),   (\"ПолучательРасчСчет\", 42),"
            "(\"ПолучательСчет\", 43),  (\"СекцияДокумент\", 44),"
            "(\"СрокАкцепта\", 45),     (\"СрокПлатежа\", 46),"
            "(\"СтатусСоставителя\", 47),   (\"Сумма\", 48),"
            "(\"УсловиеОплаты1\", 49),  (\"УсловиеОплаты2\", 50),"
            "(\"УсловиеОплаты3\", 51);"
        };

        const QString INSERT_DATA_PROPERTY = "INSERT INTO DATA_PROPERTIES";
        const QString INSERT_RECORD = "INSERT INTO DATA VALUES %1";
        const QString INSERT_ACCOUNT_NUMBER = "INSERT INTO ACCOUNTS (Account) "
                                              "VALUES (%1) RETURNING Id;";
        const QString DELETE_RECORD = "DELETE FROM DATA "
                               "WHERE Hash_1_1 = %1 and Hash_1_2 = %2 "
                               "and Hash_2_1 = %3 and Hash_2_2 = %4 "
                               "and Account_id = %5 LIMIT 1;";
        const QString SELECT_ACCOUNTS = "SELECT Account, Id FROM ACCOUNTS;";
        const QString CREATE_DATABASE = "CREATE DATABASE IF NOT EXISTS %1";
    };

    const QString DRIVER = "QMARIADB";
    const QString DATABASE_NAME = "bank_bot";

    const std::vector<QString> FIELDS = {
        "ВидАккредитива",   "ВидОплаты",            "ВидПлатежа",           //0-2
        "Дата",             "ДатаОтсылкиДок",       "ДатаПоступило",        //3-5
        "ДатаСписано",      "ДополнУсловия",        "КвитанцияВремя",       //6-8
        "КвитанцияДата",    "КвитанцияСодержание",  "Код",                  //9-11
        "КодНазПлатежа",    "НазначениеПлатежа",    "Номер",                //12-14
        "НомерСчетаПоставщика", "ОКАТО",            "Очередность",          //15-17
        "ПлатежПоПредст",   "Плательщик",           "ПлательщикБИК",        //18-20
        "ПлательщикБанк1",  "ПлательщикБанк2",      "ПлательщикИНН",        //21-23
        "ПлательщикКПП",    "ПлательщикКорсчет",    "ПлательщикРасчСчет",   //24-26
        "ПлательщикСчет",   "ПоказательДаты",       "ПоказательКБК",        //27-29
        "ПоказательНомера", "ПоказательОснования",  "ПоказательПериода",    //30-32
        "ПоказательТипа",   "Получатель",           "ПолучательБИК",        //33-35
        "ПолучательБанк1",  "ПолучательБанк2",      "ПолучательИНН",        //36-38
        "ПолучательКПП",    "ПолучательКорсчет",    "ПолучательРасчСчет",   //39-41
        "ПолучательСчет",   "СекцияДокумент",       "СрокАкцепта",          //42-44
        "СрокПлатежа",      "СтатусСоставителя",    "Сумма",                //45-47
        "УсловиеОплаты1",   "УсловиеОплаты2",       "УсловиеОплаты3"        //48-50
    };
    const std::vector<bool> IS_DIGIT_FIELD = {
        0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 1, 1, 0, 0,
        1, 0, 0, 1, 1, 1, 1, 1, 0, 1,
        0, 1, 1, 0, 0, 1, 0, 0, 1, 1,
        1, 1, 1, 0, 1, 0, 1, 1, 0, 0,
        0
    };
    const std::vector<bool> IS_DATE_FIELD = {
        0, 0, 0, 1, 1, 1, 1, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        0
    };
    const std::map<int, short> LENGTH_CONSTRAINT = {
        {1, 50}, {3, 10}, {8, 200}, {11, 50}, {13, 1},
        {14, 200}, {15, 30}, {16, 50}, {19, 200},
        {20, 300}, {22, 50}, {23, 50}, {31, 50},
        {34, 1}, {35, 300}, {37, 50}, {38, 50},
        {44, 25}, {49, 100}, {50, 100}, {51, 100}
    };

};
