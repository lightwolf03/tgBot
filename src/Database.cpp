#include "Database.h"

Database::Database() {
}

bool Database::Init() {
    int err = sqlite3_open("shedule.db", &m_db);
    if (err) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(m_db) << std::endl;
        return false;
    } else {
        std::cout << "Database opened successfully" << std::endl;
        return true;
    }
}

Database::~Database() {
    sqlite3_close(m_db);
}

unsigned Database::getStarOfWeek() {
    auto now = std::chrono::system_clock::now();
    auto dp = date::floor<iso_week::days>(now);
    iso_week::year_weeknum_weekday iso_date = dp;
    iso_week::weeknum weeknum = iso_date.weeknum();
    unsigned tmp = unsigned(weeknum) % 2 + DELTA_STAR;
    if (tmp == 0 || tmp == 2) return 2;
    else return 1;
}

void Database::getClassesFor(std::vector<Class> &vec, std::string day) {
    sqlite3_stmt* res;
    const char* tail;

    vec.clear();
    auto sqlCommand = boost::format(
            "SELECT name, number FROM classes WHERE day='%1%' AND (star=0 OR star=%2%) ORDER BY number") %
            day %
            getStarOfWeek();
    int error = sqlite3_prepare_v2(m_db, sqlCommand.str().c_str(), 1000, &res, &tail);
    if (error) throw std::runtime_error("Invalid SQL command");
    while (sqlite3_step(res) == SQLITE_ROW) {
        Class c;
        c.name = boost::lexical_cast<std::string>(sqlite3_column_text(res, 0));
        c.number = boost::lexical_cast<unsigned >(sqlite3_column_text(res, 1));
        vec.push_back(c);
    }
}
