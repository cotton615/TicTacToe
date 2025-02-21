#include <iostream>
#include <string>
#include <cstdlib>

bool win_check(char** arr, const char symbol, const int rows, const int cols) {
    bool win = false;
    bool draw = true;

    for (int i = 0; i < rows; i++) {                // вертикальная проверка 
        bool row_win = true;
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] != symbol) {
                row_win = false;                                                                 
            }
            if (arr[i][j] == '-') {                 // если все ячейки пустые - не ничья
                draw = false;
            }
        }                                                                   
        if (row_win) {
            win = true;
        }
    }

    for (int j = 0; j < cols; j++) {                // горизонтальная проверка
        bool col_win = true;
        for (int i = 0; i < rows; i++) {
            if (arr[i][j] != symbol) {
                col_win = false;
            }
        }
        if (col_win) {
            win = true;
        }
    }

    bool first_diagonal_win = true;
    for (int i = 0; i < rows; i++) {                // проверка на диагональ слева направо 
        if (arr[i][i] != symbol) {
            first_diagonal_win = false;
        }
    }
    if (first_diagonal_win) {
        win = true;
    }
    bool second_diagonal_win = true;
    for (int i = 0; i < rows; i++) {
        if (arr[i][cols - 1 - i] != symbol) {               // проверка на диагональ справа налево
            second_diagonal_win = false;
        }
    }
    if (second_diagonal_win) {
        win = true;
    }

    if (win) {
        std::cout << "Player " << symbol << " won!" << std::endl;
        return true;
    }
    if (draw) {
        std::cout << "DRAW!" << std::endl;
        return true;
    }
    return false;
}
// вставляет символ игрока на данную координату
void insert_symbol(std::pair<int, int>indices, char symbol, char** board) {
    if (board[indices.first][indices.second] != '-') {
        std::cout << "This coordinate is already taken!" << std::endl;
    }
    else {
        board[indices.first][indices.second] = symbol;
    }
}

// переводит координату в индекс двумерного массива
std::pair<int, int> index_of_coordinate(const std::string& coordinate, const int rows, const int cols) {
    int col_index = std::toupper(coordinate[0]) - 'A';
    int row_index = std::stoi(coordinate.substr(1)) - 1;

    if (row_index < 0 || row_index >= rows || col_index < 0 || col_index >= cols) {
        throw std::out_of_range("Coordinate is out of board.");
    }
    else {
        return std::make_pair(row_index, col_index);
    }
}
// принимает от пользователя координату
std::string user_coordinate(int rows, int cols) {
    while (true) {
        std::string coordinate;
        std::cout << "Enter coordinate: ";
        std::cin >> coordinate;
        if (coordinate.length() >= 2 && std::isalpha(coordinate[0]) && std::isdigit(coordinate[1])) {
            try {
                std::pair<int, int> indices = index_of_coordinate(coordinate, rows, cols);
                return coordinate;
            }
            catch (const std::out_of_range e) {
                std::cout << e.what() << std::endl;
            }
        }
        else {
            std::cout << "Type in format: (A1): ";

        }
    }
}

// принимает от пользователя символ игрока
char user_symbol() {
    std::string symbol;
    std::cout << "Enter symbol for the player: ";
    std::cin >> symbol;
    if (symbol.length() == 1) {
        return symbol[0];
    }
    else {
        std::cout << "Please enter only ONE character." << std::endl;
        return user_symbol();
    }
}
// проверяет rows и cols на то, являются ли они int
bool is_integer(const std::string& input) {
    if (input.empty()) return false;

    for (int i = 0; i < input.length(); i++) {
        if (!std::isdigit(input[i])) {
            return false;
        }
    }
    return true;
}
// создаёт двумерный массив
char** create_arr(const int rows, const int cols) {
    char** arr = new char* [rows]; // аллоцирует память
    for (int i = 0; i < rows; i++) {
        arr[i] = new char[cols];
    }

    for (int i = 0; i < rows; i++) { // наполняет массив символом -
        for (int j = 0; j < cols; j++) {
            arr[i][j] = '-';
        }
    }
    return arr;
}
// выводит доску в консоль
void display_board(char** arr, const int rows, const int cols) {
    std::cout << "  ";
    for (int j = 0; j < cols; j++) {
        std::cout << char('A' + j) << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < rows; i++) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < cols; j++)
            std::cout << arr[i][j] << " ";
        std::cout << "\n";
    }
}
// очищает доску из памяти
void delete_arr(char** arr, const int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}
// решает какой символ игрока ставить, а также ведёт игру
void players_turn(char** arr, const int rows, const int cols, std::pair<char, char>symbols, int step) {
    char symbol;
    if (step % 2 == 0) {
        symbol = symbols.first;
        std::cout << "Now it's " << symbol << " turn!" << std::endl;
        insert_symbol(index_of_coordinate(user_coordinate(rows, cols), rows, cols), symbol, arr);
        display_board(arr, rows, cols);
    }
    else {
        symbol = symbols.second;
        std::cout << "Now it's " << symbol << " turn!" << std::endl;
        insert_symbol(index_of_coordinate(user_coordinate(rows, cols), rows, cols), symbol, arr);
        display_board(arr, rows, cols);
    }
}

int main() {
    std::string rows_str, cols_str;
    std::cout << "enter rows: ";
    std::cin >> rows_str;
    std::cout << "enter columns: ";
    std::cin >> cols_str;
    int rows = std::stoi(rows_str);
    int cols = std::stoi(cols_str);
    char** arr = create_arr(rows, cols);
    std::pair<char, char> symbols(user_symbol(), user_symbol());
    if (symbols.first == symbols.second) {
        std::cout << "Player characters must be different!." << std::endl;
    }
    int step = 0;
    display_board(arr, rows, cols);
    while (true) {
        if (is_integer(rows_str) && is_integer(cols_str)) {
            char current_symbol;
            if (step % 2 == 0) {                // выбирает символ для текущего хода
                current_symbol = symbols.first;
            }
            else {
                current_symbol = symbols.second;
            }
            players_turn(arr, rows, cols, symbols, step);
            if (win_check(arr, current_symbol, rows, cols)) {               // если текущий символ побеждает удаляет доску и завершает игру
                delete_arr(arr, rows);
                break;
            }
            step += 1;
        }
        else {
            std::cout << "you must enter only int" << std::endl;
        }
    }
}