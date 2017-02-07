cmake_minimum_required(VERSION 3.6)
project(raspBot)
set(CMAKE_CXX_STANDARD 14)

set(Boost_USE_MULTITHREADED ON)

set(Date_INCLUDE_DIR ext/date)
set(Json_INCLUDE_DIR ext/json)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system iostreams REQUIRED)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR} ${Date_INCLUDE_DIR} ${Json_INCLUDE_DIR})

add_executable(raspBot src/main.cpp src/Database.cpp src/Database.h src/Helpers.h)

target_link_libraries(raspBot /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} -lsqlite3 -lcurl)