#ifndef RASPBOT_WEATHERSTORAGE_H
#define RASPBOT_WEATHERSTORAGE_H

#include <iostream>
#include <vector>
#include <chrono>
#include <map>
#include <deque>
#include "date/date.h"
#include <boost/optional.hpp>

#define WEATHER_HISTORY_COUNT 5

struct Entry {
    std::string cityName;
    int temperature;
    int windSpeed;
    std::chrono::system_clock::time_point timestamp;
};

class WeatherStorage {
    std::map<std::string, std::deque<Entry> > m_storage;
public:
    WeatherStorage();
    ~WeatherStorage();
    bool needUpdate(Entry &entry);
    void add(std::string cityID, Entry& e);
    boost::optional<Entry&> get(std::string cityID);
    void check(std::string cityID);
private:
};


#endif //RASPBOT_WEATHERSTORAGE_H
