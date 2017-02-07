#include <iostream>
#include <tgbot/tgbot.h>
#include "Database.h"
#include "Helpers.h"

#define BOT_TOKEN "249701168:AAHhfNlRLjY5_YW3QclSCqDfpm4auUta--E"
#define TEST_BOT_TOKEN "331463922:AAHu61CE7IdDe6EFCtQ71GPgFDvuGTq-R7w"

int main() {
    TgBot::Bot bot(TEST_BOT_TOKEN);
    Database db;
    db.Init();

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onCommand("n4k", [&bot](TgBot::Message::Ptr msg) {
       bot.getApi().sendMessage(msg->chat->id, helpers::getWeatherForN4k(), false, 0, NULL, "Markdown");
    });
//    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
//        printf("User wrote %s\n", message->text.c_str());
//        if (StringTools::startsWith(message->text, "/start")) {
//            return;
//        }
//        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
//    });
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
//            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}