#ifndef RASPBOT_HELPERS_H
#define RASPBOT_HELPERS_H

#include <chrono>
#include <string>
#include "iso_week.h"
#include "date.h"
#include "json.h"
#include <curl/curl.h>
#include <boost/format.hpp>

#ifndef DELTA_STAR
#define DELTA_STAR 1
#endif

#define WEATHER_TOKEN "eee318bf4a5a5b19aecfd9d1c4d7c3a9"
#define N4K_ID "518976"
#define CHEB_ID "569696"

namespace helpers {
    static std::string buffer;
    static CURL *curl;

    static int writer(char *data, size_t size, size_t nmemb, std::string *buffer) {
        int result = 0;
        if (buffer != NULL) {
            buffer->append(data, size * nmemb);
            result = size * nmemb;
        }
        return result;
    }

    unsigned getStarOfWeak() {
        auto now = std::chrono::system_clock::now();
        auto dp = date::floor<iso_week::days>(now);
        iso_week::year_weeknum_weekday iso_date = dp;
        iso_week::weeknum weeknum = iso_date.weeknum();
        return unsigned(weeknum) % 2 + DELTA_STAR;
    }

    void getRequest(std::string& s, std::string cityID) {
        curl = curl_easy_init();
        if (curl) {
            buffer.clear();
            s.clear();
            auto url = boost::format("api.openweathermap.org/data/2.5/weather?" \
                        "id=%1%&units=metric&" \
                        "APPID=%2%\0") % cityID % WEATHER_TOKEN;
            std::cout << url << std::endl;
            curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
            curl_easy_perform(curl);

            std::cout << buffer << std::endl;
            using nlohmann::json;
            json parsedJson = json::parse(buffer);
            auto weatherString = boost::format("_%1%_ *%2% °C* Wind: %3% m/s") %
                    parsedJson["name"].get<std::string>() %
                    parsedJson["main"]["temp"] %
                    parsedJson["wind"]["speed"];
            s = weatherString.str();
        }
        curl_easy_cleanup(curl);
    }

    std::string getWeatherForN4k() {
        std::string s;
        getRequest(s, N4K_ID);
        return s;
    }

    std::string getWeatherFor4eb() {
        std::string s;
        getRequest(s, CHEB_ID);
        return s;
    }
}

#endif //RASPBOT_HELPERS_H
