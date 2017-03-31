#include <iostream>
#include <tgbot/tgbot.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

static TgBot::InputFile::Ptr fromLink(std::string url) {
    std::string path = "/tmp/";

    if (url.length() < 5)
        return NULL;

    if (url.substr(url.length()-5, 5) != ".webm")
        return NULL;

    std::vector<std::string> paths;
    boost::split(paths, url, boost::is_any_of("/"));
    std::string fileName = paths.back();

    CURL* curl = curl_easy_init();
    if (!curl)
        return NULL;

    FILE* file = std::fopen((path + fileName).data(), "wb");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    auto res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    fclose(file);

    std::vector<std::string> partsOfFileName;
    boost::split(partsOfFileName, fileName, boost::is_any_of("."));
    std::string newFileName = partsOfFileName.front() + ".mp4";

    std::string s1 = (path + fileName);
    std::string s2 = (path + newFileName);

    auto convertCommand = boost::format("ffmpeg -i \"%1%\" -qscale 0 \"%2%\"") % s1 % s2;
    system(convertCommand.str().c_str());

    return TgBot::InputFile::fromFile(path+newFileName, "video/mp4");
}
