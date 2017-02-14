#include "WeatherStorage.h"

WeatherStorage::WeatherStorage() {}

WeatherStorage::~WeatherStorage() {}

bool WeatherStorage::needUpdate(Entry &entry) {
    auto now = std::chrono::system_clock::now();
    auto timeDelta =  std::chrono::duration_cast<std::chrono::seconds>(now - entry.timestamp);
    return timeDelta.count() > 60;
}

void WeatherStorage::add(std::string cityID, Entry &e) {
    auto it = m_storage.find(cityID);
    if ( it != m_storage.end()) {
        auto& cityDeque = it->second;
        cityDeque.push_back(e);
    }
}

boost::optional<Entry&> WeatherStorage::get(std::string cityID) {
    auto it = m_storage.find(cityID);
    if (it != m_storage.end()) {
        auto& deque = it->second;
        return boost::optional<Entry&>(deque.back());
    } else {
        std::deque<Entry> d;
        m_storage.insert(std::pair<std::string, std::deque<Entry> >(cityID, d));
        return boost::optional<Entry&>();
    }
}

void WeatherStorage::check(std::string cityID) {
    auto it = m_storage.find(cityID);
    if (it != m_storage.end()) {
        auto& deque = it->second;
        if (deque.size() > 5) deque.pop_front();
    }
}


