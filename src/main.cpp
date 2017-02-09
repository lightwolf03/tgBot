#include <iostream>
#include <tgbot/tgbot.h>
#include "Database.h"
#include "Helpers.h"
#include "Weather.h"

#define BOT_TOKEN "249701168:AAHhfNlRLjY5_YW3QclSCqDfpm4auUta--E"
#define TEST_BOT_TOKEN "331463922:AAHu61CE7IdDe6EFCtQ71GPgFDvuGTq-R7w"

int main() {
    TgBot::Bot bot(TEST_BOT_TOKEN);
    Database db;
    db.Init();
    Weather* weather = new Weather();

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onCommand("n4k", [&bot, &weather](TgBot::Message::Ptr msg) {
       bot.getApi().sendMessage(msg->chat->id, weather->getWeatherForN4k(), false, 0, NULL, "Markdown");
    });
    bot.getEvents().onCommand("4eb", [&bot, &weather](TgBot::Message::Ptr msg) {
        bot.getApi().sendMessage(msg->chat->id, weather->getWeatherFor4eb(),  false, 0, NULL, "Markdown");
    });
    bot.getEvents().onCommand("monday", [&bot, &db](TgBot::Message::Ptr msg) {
        bot.getApi().sendMessage(msg->chat->id, helpers::getClassesFor(db, "Monday"), false, 0, NULL, "Markdown");
    });
    bot.getEvents().onCommand("tuesday", [&bot, &db](TgBot::Message::Ptr msg) {
        bot.getApi().sendMessage(msg->chat->id, helpers::getClassesFor(db, "Tuesday"), false, 0, NULL, "Markdown");
    });
    bot.getEvents().onCommand("wednesday", [&bot, &db](TgBot::Message::Ptr msg) {
        bot.getApi().sendMessage(msg->chat->id, helpers::getClassesFor(db, "Wednesday"), false, 0, NULL, "Markdown");
    });
    bot.getEvents().onCommand("thursday", [&bot, &db](TgBot::Message::Ptr msg) {
        bot.getApi().sendMessage(msg->chat->id, helpers::getClassesFor(db, "Thursday"), false, 0, NULL, "Markdown");
    });
    bot.getEvents().onCommand("friday", [&bot, &db](TgBot::Message::Ptr msg) {
        bot.getApi().sendMessage(msg->chat->id, helpers::getClassesFor(db, "Friday"), false, 0, NULL, "Markdown");
    });
    bot.getEvents().onCommand("saturday", [&bot, &db](TgBot::Message::Ptr msg) {
        bot.getApi().sendMessage(msg->chat->id, helpers::getClassesFor(db, "Saturday"), false, 0, NULL, "Markdown");
    });
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
        delete weather;
    }
    return 0;
}