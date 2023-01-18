/*
** EPITECH PROJECT, 2022
** gomoku
** File description:
** main
*/

#include <iostream>

#include <string>
#include "Gomoku.hpp"
#include "Exception.hpp"
#include "Protocol.hpp"

int main(int argc, char const *argv[])
{
    Gomoku gomoku;
    std::string str;

    while (str != "END") {
        str = gomoku.get_command();
        if (str == "ERROR")
            return 84;
    }
    return 0;
}