#ifndef RASPBOT_HELPERS_H
#define RASPBOT_HELPERS_H

#include <string>
#include "Database.h"

namespace helpers {
    std::string getClassesFor(Database& db, std::string day) {
        std::vector<Class> classes;
        db.getClassesFor(classes, day);
        std::stringstream ss;
        ss << boost::format("_Shedule on_ *%1%*") % day << std::endl;
        for (Class& c: classes) {
            ss << boost::format("*%1%* _%2%_") % c.number % c.name << std::endl;
        }
        return ss.str();
    }
}

#endif //RASPBOT_HELPERS_H
