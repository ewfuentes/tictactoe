#include "tictactoe.hh"


int main() {

    bool run = true;
    int input = -1;
    engine::tictactoe::GameState game_state;
    while (run) {
        // render board
        std::cout << game_state << std::endl;
        std::cout << "Select position for " << game_state.next_player << std::endl;
        std::cin >> input; 
        if (std::cin.fail()) {
            input = -1;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        const engine::tictactoe::GameStateStep step =
            engine::tictactoe::make_move(game_state, input);
        
        if (!step.was_valid_move) {
            std::cout << "Invalid move!" << std::endl;
        } else {
            game_state = step.new_state;
        }

        run = !step.is_game_over;
    }
    std::cout << game_state << std::endl;
    std::cout << game_state.next_player << " is the winner!!" << std::endl;
    return EXIT_SUCCESS;
}
