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
