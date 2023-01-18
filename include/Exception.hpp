/*
** EPITECH PROJECT, 2022
** gomoku
** File description:
** Exception
*/

#pragma once

#include <exception>
#include <string>

class GomokuException : std::exception {
    public:
        GomokuException(void) noexcept = default;
        GomokuException(const std::string &msg) noexcept { error += msg; };

        GomokuException(const GomokuException &) noexcept = default;
        GomokuException(GomokuException &&) noexcept = default;
        ~GomokuException(void) noexcept override = default;

        GomokuException &operator=(const GomokuException &rhs) noexcept = default;
        GomokuException &operator=(GomokuException &&rhs) noexcept = default;

        const char *what() const noexcept final;

    private:
        std::string error = "ERROR message - ";
};
