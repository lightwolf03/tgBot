#ifndef RASPBOT_DATABASE_H
#define RASPBOT_DATABASE_H

#include <sqlite3.h>
#include <iostream>
#include "iso_week.h"

struct Class {
    unsigned week;
    std::string definition;
    unsigned number;
    std::string day;
};

class Database {
private:
    sqlite3 *m_db;
public:
    Database();
    ~Database();
    bool Init();
};


#endif //RASPBOT_DATABASE_H
