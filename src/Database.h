#ifndef RASPBOT_DATABASE_H
#define RASPBOT_DATABASE_H

#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include "date/iso_week.h"
#include "date/date.h"
#include <chrono>

#ifndef DELTA_STAR
#define DELTA_STAR 1
#endif

struct Class {
    std::string name;
    unsigned number;
};

class Database {
private:
    sqlite3 *m_db;
public:
    Database();
    ~Database();
    bool Init();
    void getClassesFor(std::vector<Class>& vec, std::string day);

    unsigned int getStarOfWeek();
};


#endif //RASPBOT_DATABASE_H
