#include "Weather.h"

Weather::Weather() {

}

void Weather::getRequest(std::string& str, std::string cityID) {
    m_curl = curl_easy_init();
    if (m_curl) {
        m_buffer.clear();
        str.clear();
        auto url = boost::format("api.openweathermap.org/data/2.5/weather?" \
                        "id=%1%&units=metric&" \
                        "APPID=%2%\0") % cityID % WEATHER_TOKEN;
        std::cout << url << std::endl;
        curl_easy_setopt(m_curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, writer);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_buffer);
        curl_easy_perform(m_curl);

        std::cout << m_buffer << std::endl;
        using nlohmann::json;
        json parsedJson = json::parse(m_buffer);
        auto weatherString = boost::format("_%1%_ *%2% °C* Wind: %3% m/s") %
                             parsedJson["name"].get<std::string>() %
                             parsedJson["main"]["temp"] %
                             parsedJson["wind"]["speed"];
        str = weatherString.str();
    }
    curl_easy_cleanup(m_curl);
}

std::string Weather::getWeatherForN4k() {
    std::string s;
    getRequest(s, N4K_ID);
    return s;
}

std::string Weather::getWeatherFor4eb() {
    std::string s;
    getRequest(s, CHEB_ID);
    return s;
}