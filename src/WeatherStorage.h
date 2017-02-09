#ifndef RASPBOT_WEATHERSTORAGE_H
#define RASPBOT_WEATHERSTORAGE_H

#include <iostream>
#include <map>
#include <chrono>

struct Entry {
    std::string cityName;
    int temperature;
    int wind;
//    std::chrono::time_point timestamp;
};

class WeatherStorage {
    std::map<std::string, Entry> storage;
public:
    WeatherStorage();
    ~WeatherStorage();
};


#endif //RASPBOT_WEATHERSTORAGE_H
