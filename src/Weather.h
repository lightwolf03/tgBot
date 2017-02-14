#ifndef RASPBOT_WEATHER_H
#define RASPBOT_WEATHER_H

#include <curl/curl.h>
#include <boost/format.hpp>
#include <string>
#include "json/json.h"
#include "WeatherStorage.h"

#define WEATHER_TOKEN "eee318bf4a5a5b19aecfd9d1c4d7c3a9"
#define N4K_ID "518976"
#define CHEB_ID "569696"

static int writer(char *data, size_t size, size_t nmemb, std::string *buffer) {
    int result = 0;
    if (buffer != NULL) {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

class Weather {
    WeatherStorage m_storage;
    std::string m_buffer;
    CURL *m_curl;
public:
    Weather();
    std::string getWeatherForN4k();
    std::string getWeatherFor4eb();
private:
    void getRequest(Entry& e, std::string cityID);
    void getEntry(Entry& e, std::string cityID);
    std::string outputEntry(Entry& e);
};

#endif //RASPBOT_WEATHER_H
