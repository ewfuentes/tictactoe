#include "engine/tictactoe.hh"

namespace engine::tictactoe {
namespace {

bool check_rows(const GameState &state) {
    bool is_win = false;
    for (int i = 0; i < state.BOARD_SIZE; i++) {
        const int row_idx = i * state.BOARD_SIZE;
        is_win |= state.board[row_idx] == state.board[row_idx + 1] &&
            state.board[row_idx] == state.board[row_idx + 2] &&
            state.board[row_idx] != CellState::EMPTY;
    }
    return is_win;
}

bool check_cols(const GameState &state) {
    bool is_win = false;
    for (int i = 0; i < state.BOARD_SIZE; i++) {
        is_win |= state.board[i] == state.board[i + state.BOARD_SIZE] &&
            state.board[i] == state.board[i + 2 * state.BOARD_SIZE] &&
            state.board[i] != CellState::EMPTY;
    }
    return is_win;
}

bool check_diags(const GameState &state) {
    bool is_up_diag_the_same = true;
    bool is_down_diag_the_same = true;
    const CellState down_diag = state.board[0];
    const CellState up_diag = state.board[state.BOARD_SIZE - 1];
    constexpr int DOWN_DIAG_STEP = state.BOARD_SIZE + 1;
    constexpr int UP_DIAG_STEP = state.BOARD_SIZE - 1;
    for (int i = 1; i < state.BOARD_SIZE; i++) {
        is_up_diag_the_same &= up_diag == state.board[state.BOARD_SIZE - 1 + i * UP_DIAG_STEP];
        is_down_diag_the_same &= down_diag == state.board[i * DOWN_DIAG_STEP];
    }
    return (down_diag != CellState::EMPTY && is_down_diag_the_same) || 
        (up_diag != CellState::EMPTY && is_up_diag_the_same);
}

bool is_board_full(state) {
    bool found_empty = false;
    for (int i = 0; i < state.NUM_SPACES; i++) {
        found_empty |= state.board[i] == CellState::EMPTY;
    }
    return !found_empty;
}

bool is_game_over(const GameState &state) {
    return check_rows(state) || check_cols(state) || check_diags(state) || is_board_full(state);
}
}  // namespace

GameStateStep make_move(const GameState &state, const int move_position) {
    // Check to see that it's a valid move
    if (move_position < 0 ||
        move_position >= state.NUM_SPACES ||
        state.board[move_position] != CellState::EMPTY) {
        return {
            .new_state = state,
            .was_valid_move = false,
            .is_game_over = false
        };
    }

    // Make the move
    GameState new_state{state};
    new_state.board[move_position] = new_state.next_player;

    // Create the state step
    GameStateStep out;
    out.new_state = std::move(new_state);
    out.was_valid_move = true; 
    out.is_game_over = is_game_over(out.new_state);
    if (!out.is_game_over) {
        out.new_state.next_player = new_state.next_player == CellState::X ?
            CellState::O : CellState::X;
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const CellState &state) {
    out << (state == CellState::EMPTY ? "_" :
        (state== CellState::X ? "X" : "O"));
    return out;
}

std::ostream &operator<<(std::ostream &out, const GameState &state) {
    for (int i = 0; i < state.BOARD_SIZE; i++) {
        out << " ";
        for (int j = 0; j < state.BOARD_SIZE; j++) {
           out << state.board[i * state.BOARD_SIZE + j] << " ";
        }
        out << std::endl;
    }
    return out;
}

}  // namespace engine::tictactoe
