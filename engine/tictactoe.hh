#pragma once

#include <vector>
#include <iostream>

namespace engine::tictactoe {
enum CellState {
    EMPTY, X, O
};

// The board is in row major order
struct GameState {
    static constexpr int BOARD_SIZE = 3;
    static constexpr int NUM_SPACES = BOARD_SIZE * BOARD_SIZE;
    CellState board[NUM_SPACES];
    CellState next_player = CellState::X;
    GameState() {
        for (int i = 0; i < NUM_SPACES; i++) {
            board[i] = CellState::EMPTY;
        }
    }
};

struct GameStateStep {
    GameState new_state;
    // Was the move that created this step valid
    bool was_valid_move = false;
    // Only set if move was valid
    bool is_game_over = false;
    CellState winner = CellState::EMPTY;
};

GameStateStep make_move(const GameState &state, const int move_position);
std::ostream &operator<<(std::ostream &out, const GameState &state);
std::ostream &operator<<(std::ostream &out, const CellState &state);

}  // namespace engine::tictactoe
