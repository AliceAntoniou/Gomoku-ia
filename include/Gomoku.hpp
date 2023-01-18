/*
** EPITECH PROJECT, 2022
** gomoku
** File description:
** Gomoku
*/

#pragma once

#include <map>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include "Protocol.hpp"

class Gomoku {
    public:
        Gomoku(void) = default;

        Gomoku(const Gomoku &) noexcept = delete;
        Gomoku(Gomoku &&) noexcept = default;
        ~Gomoku(void) noexcept = default;

        Gomoku &operator=(const Gomoku &) noexcept = delete;
        Gomoku &operator=(Gomoku &&) noexcept = default;

        std::string get_command(void);

        void play();
        void playing_defensive_move();
        void defense_horizontal(int y_manager_move, int x_manager_move);
        void defense_vertical(int y_manager_move, int x_manager_move);
        void defense_diagonal_1(int y_manager_move, int x_manager_move);
        void defense_diagonal_2(int y_manager_move, int x_manager_move);
        void calculate_defensive_move(int y_manager_move, int x_manager_move);
        void calculate_range_around_enemy(int y, int x);
        void playing_attack_move();

        void start(int size);
        bool start(void);
        void turn(void);
        void begin(void);
        void board(void);
        void about(void);

        void info(void);

        void end(void);

        void write_map();
        bool get_map();

        enum Tile_t { manager = 'O', brain = 'x', empty = ' ' };
        using board_t = std::vector<std::vector<Tile_t>>;
        using weights_t = std::vector<std::vector<int>>;

    private:
        Protocol protocol;
        size_t board_size = 0;
        board_t _board = {};
        weights_t weights = {};
        std::map<std::string, int> settings = {
            {"timeout_turn", 0}, {"timeout_match", 0}, {"max_memory", 0}, {"time_left", 0}, {"game_type", 1}, {"rule", 0}};
        std::string folder = "";
        Tile_t _turn = Tile_t::manager;
        bool can_win = false;
        bool game_started = false;
        bool map_is_set = false;
        int x_just_played;
        int y_just_played;
        std::vector<std::pair<int,int>> next_moves;
        std::vector<int> m_line_size;
};
