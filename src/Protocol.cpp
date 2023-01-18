//
// Created by natan on 15/11/2022.
//

#include "Protocol.hpp"
#include <iostream>

void Protocol::Answer::start(bool isOk, std::string msg) {
    if (isOk) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "ERROR " << msg << std::endl;
    }
}

void Protocol::Answer::rectstart(bool isOk, std::string msg) {
    if (isOk) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "ERROR " << msg << std::endl;
    }
}
void Protocol::Answer::restart(bool isOk)
{
    if (isOk) {
        std::cout << "OK" << std::endl;
    } else {
        std::cerr << "Restart function failed, unable to send ERROR to the engine" << std::endl;
    }
}

void Protocol::Answer::takeback(bool isOk) {
    if (isOk) {
        std::cout << "OK" << std::endl;
    } else {
        std::cerr << "Takeback function failed, unable to send ERROR to the engine" << std::endl;
    }
}

void Protocol::Answer::play(std::pair<int, int> const &coordinates) {
    std::cout << "PLAY " << coordinates.first << "," << coordinates.second << std::endl;
}

void Protocol::Answer::about(std::string const &name, std::string const &version, std::string const &author, std::string const &country) {
    //name="SomeBrain", version="1.0", author="Nymand", country="USA"
    std::cout << "name=\"" << name << "\", version=\"" << version << "\", author=\"" << author << "\", country=\"" << country << "\"" << std::endl;
}

void Protocol::Command::turn(std::pair<int, int> const &coordinates) {
    std::cout << coordinates.first << "," << coordinates.second << std::endl;
}

void Protocol::Command::error(std::string const &message) {
    std::cerr << "ERROR " << message << std::endl;
}

void Protocol::Command::unknown(const std::string &message) {
    std::cerr << "UNKNOWN " << message << std::endl;
}

void Protocol::Command::message(std::string const &message) {
    std::cout << "MESSAGE " << message << std::endl;
}

void Protocol::Command::debug(std::string const &message) {
    std::cout << "DEBUG " << message << std::endl;
}

void Protocol::Command::suggest(std::pair<int, int> const &coordinates) {
    std::cout << "SUGGEST " << coordinates.first << "," << coordinates.second << std::endl;
}
