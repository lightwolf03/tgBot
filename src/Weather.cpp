#include "Weather.h"

Weather::Weather() {

}

void Weather::getRequest(Entry& e, std::string cityID) {
    m_curl = curl_easy_init();
    if (m_curl) {
        m_buffer.clear();
        auto url = boost::format("api.openweathermap.org/data/2.5/weather?" \
                        "id=%1%&units=metric&" \
                        "APPID=%2%\0") % cityID % WEATHER_TOKEN;
        std::cout << url << std::endl;
        curl_easy_setopt(m_curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, writer);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_buffer);
        curl_easy_perform(m_curl);

        using nlohmann::json;
        json parsedJson = json::parse(m_buffer);

        e.cityName = parsedJson["name"].get<std::string>();
        e.temperature = parsedJson["main"]["temp"];
        e.windSpeed = parsedJson["wind"]["speed"];
        e.timestamp = std::chrono::system_clock::now();
    }
    curl_easy_cleanup(m_curl);
}

std::string Weather::getWeatherForN4k() {
    Entry e;
    getEntry(e, N4K_ID);
    return outputEntry(e);
}

std::string Weather::getWeatherFor4eb() {
    Entry e;
    getEntry(e, CHEB_ID);
    return outputEntry(e);
}

std::string Weather::outputEntry(Entry &e) {
    auto weatherString = boost::format("_%1%_ *%2% °C* Wind: %3% m/s") %
                     e.cityName %
                     e.temperature %
                     e.windSpeed;
    return weatherString.str();
}

void Weather::getEntry(Entry &e, std::string cityID) {
    if (auto entry = m_storage.get(cityID)) {
        e = entry.get();
        if (m_storage.needUpdate(e)) {
            getRequest(e, cityID);
            m_storage.add(cityID, e);
        }
    } else {
        getRequest(e, cityID);
        m_storage.add(cityID, e);
    }
    m_storage.check(cityID);
}
