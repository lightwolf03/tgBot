#ifndef RASPBOT_HELPERS_H
#define RASPBOT_HELPERS_H

#include <chrono>
#include <string>
#include "iso_week.h"
#include "date.h"
#include "json.h"
#include <curl/curl.h>

#ifndef DELTA_STAR
#define DELTA_STAR 1
#endif

namespace helpers {
    static std::string buffer;

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

    std::string getWeatherForN4k() {
        CURL *curl;
        curl = curl_easy_init();
        std::stringstream ss;
        if (curl) {
            buffer.clear();
            curl_easy_setopt(curl, CURLOPT_URL, "api.openweathermap.org/data/2.5/weather?" \
                                                "id=518976&units=metric&" \
                                                "APPID=eee318bf4a5a5b19aecfd9d1c4d7c3a9");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
            curl_easy_perform(curl);

            using nlohmann::json;
            json parsedJson = json::parse(buffer);
            ss << "_" << parsedJson["name"].get<std::string>() << "_ *" << parsedJson["main"]["temp"] << " °C*";
            // TODO: Use boost::format for generate string
        }
        curl_easy_cleanup(curl);
        return ss.str();
    }
}

#endif //RASPBOT_HELPERS_H
