#include <iostream>
#include <vector>
#include <cstdlib>
// Выводит доску в консоль в правильном порядке
void display_board(char board[9]) {
    std::cout << "  A   B   C \n";

    for (int i = 0; i < 9; i++) {
        if ((i % 3) == 0) {
            std::cout << (i / 3) + 1;
            std::cout << " ";
        }
        std::cout << board[i];

        if ((i + 1) % 3 != 0) {
            std::cout << " | ";
        }
        else {
            std::cout << "\n";
        }
    }
}

// функция проверяет на легитимность ввода, а потом возвращает индекс координаты
int move_to_coordinate(std::string &move, std::vector<std::string> &possible_moves) {
    while (true) {
        if (move.length() == 2 && (std::isalpha(move[0]) && std::isdigit(move[1]))) {
            for (size_t i = 0; i < possible_moves.size(); ++i) {
                if (move == possible_moves[i]) {
                    std::cout << "Move accepted: " << move << std::endl; 
                    system("cls");
                    return i; 
                }
            }
            std::cout << "There's no move like this on the board. Try again: ";
            std::cin >> move;
        }
        else if (move.length() == 2 && (std::isalpha(move[1]) && std::isdigit(move[0]))) {
            std::swap(move[1], move[0]);  
            continue;
        } 
        else {
            std::cout << "Ivalid format. Enter again: ";
            std::cin >> move;
        }
    }
}
bool is_board_full(const char board[]) { // Проверка на заполненность доски
    for (int i = 0; i < 9; i++) {
        if (board[i] == '-') {
            return false;
        }
    }
    return true;
}

int main() {
    std::cout << "Welcome to the Tic-Tac-Toe Game!\n";

    std::vector<std::vector<int>> win_combinations = { // Все возможные комбинации побед
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},
    {0, 4, 8},
    {2, 4, 6},
    };

    char board[9] = {'-', '-', '-', // Доска, которая позже изменяется
                     '-', '-', '-', 
                     '-', '-', '-'};
    std::vector<std::string> possible_moves = { "a1", "b1", "c1", // используется для проверки ввода пользователя
                                                "a2", "b2", "c2", 
                                                "a3", "b3", "c3"};
    display_board(board);
    
    bool game_on = true;
    int step = 0;
    
    while (game_on) {
        char symbol;
        if (step % 2 == 0) { // если кол-во ходов четное - Х, если нет - О
            symbol = 'X';
        }
        else {
            symbol = 'O';
        }
        std::string move;
        std::cout << "Enter your move (" << symbol << ") :";
        std::cin >> move;
        int index = move_to_coordinate(move, possible_moves);
        if (board[index] == 'O' || board[index] == 'X') {
            std::cout << "This position is already taken!" << std::endl;
        } else {
            board[index] = symbol;
            step += 1;  
        }

        for (auto combination : win_combinations) {
            if (board[combination[0]] != '-' && board[combination[0]] == board[combination[1]] && board[combination[1]] == board[combination[2]]) {
                std::cout << "Player" << symbol << "wins!" << std::endl;
                game_on = false;
            }
            
        }
        
        if (is_board_full(board)) { // Вывод сообщения о победе
            system("cls");
            display_board(board);
            std::cout << "DRAW!" << std::endl;
            break;
        }
        display_board(board);
    }
}