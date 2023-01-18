//
// Created by natan on 14/11/2022.
//

#pragma once

#include <string>
#include <vector>



class Protocol {
    public:
        Protocol() = default;
        ~Protocol() = default;
        struct Answer
        {
            // Is used to respond to the START command, true if everything is good, false otherwise.
            // msg will be ignored if isOk is true.
            void start(bool isOk, std::string msg = "");

            // Is used to respond to the RECTSTART command, true if everything is good, false otherwise.
            // msg will be ignored if isOk is true.
            void rectstart(bool isOk, std::string msg = "");

            // Is used to respond to the RESTART command, true if everything is good, false otherwise.
            void restart(bool isOk = true);

            // Is used to respond to the TAKEBACK command, true if everything is good, false otherwise.
            void takeback(bool isOk);

            // Is used to respond to the PLAY command, repeats the coordinates given by the engine.
            void play(std::pair<int, int> const &coordinates);

            // Is used to respond to the ABOUT command, sends basic info to the engine.
            void about(std::string const &name, std::string const &version, std::string const &author, std::string const &country);
        };
        struct Command
        {
            // Is used to respond to the TURN command, coordinates of the next move to be played by the AI.
            void turn(std::pair<int, int> const &coordinates);

            // Is used to send an error to the engine.
            void error(std::string const &message);

            // Is used to send a message to the engine about an unknown command.
            void unknown(std::string const &message);

            // Is used to send a message to the engine.
            void message(std::string const &message);

            // Is used to send debug information to the engine.
            void debug(std::string const &message);

            // Is used to suggest a move to the engine (probably not used).
            void suggest(std::pair<int, int> const &coordinates);
        };
};