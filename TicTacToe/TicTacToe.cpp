#include <iostream>
#include <string>
#include <cstdlib>

bool win_check(char** arr, const char symbol, const std::pair<int, int>size) {
    bool win = false;

    for (int i = 0; i < size.first; i++) {                // вертикальная проверка 
        bool row_win = true;
        for (int j = 0; j < size.second; j++) {
            if (arr[i][j] != symbol) {
                row_win = false;
            }
        }                                                                   
        if (row_win) {
            win = true;
        }
    }

    for (int j = 0; j < size.second; j++) {                // горизонтальная проверка
        bool col_win = true;
        for (int i = 0; i < size.first; i++) {
            if (arr[i][j] != symbol) {
                col_win = false;
            }
        }
        if (col_win) {
            win = true;
        }
    }

    bool first_diagonal_win = true;
    for (int i = 0; i < size.first; i++) {                // проверка на диагональ слева направо 
        if (arr[i][i] != symbol) {
            first_diagonal_win = false;
        }
    }
    if (first_diagonal_win) {
        win = true;
    }
    bool second_diagonal_win = true;
    for (int i = 0; i < size.first; i++) {
        if (arr[i][size.second - 1 - i] != symbol) {               // проверка на диагональ справа налево
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
    return false;
}
// вставляет символ игрока на данную координату
void insert_symbol(std::pair<int, int>indices, char symbol, char** board, int& step) {
    if (board[indices.first][indices.second] != '-') {
        std::cout << "This coordinate is already taken!" << std::endl;
    }
    else {
        board[indices.first][indices.second] = symbol;
        step += 1;
    }
}

// принимает от пользователя координату
std::pair<int, int> user_coordinate(std::pair<int, int>size) {
    std::pair<int, int> indices;
    char column;

    std::cout << "Enter coordinate in format (A 1): ";
    while (true) {
        if (!(std::cin >> column >> indices.second)) {
            std::cout << "Invalid input." << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        indices.first = std::toupper(column) - 'A';
        indices.second -= 1;
        // если координата не выходит за пределы доски - создать пару индексов
        if (indices.first >= 0 && indices.first < size.second && indices.second >= 0 && indices.second < size.first) { 
            return std::make_pair(indices.second, indices.first);
        }
        else {
            std::cout << "Coordinate is out of board." << std::endl;
            continue;
        }
    }
}

// принимает от пользователя символ игрока
std::pair<char, char> user_symbol(int step) {
    std::pair<char, char> user_names;
    for (int i = 0; i < 2; i++) {
        std::cout << "Enter symbol for " << i+1 << " player :" << std::endl;
        char symbol;
        std::cin >> symbol;
        if (i == 0) {
            user_names.first = symbol;
        }
        else {
            user_names.second = symbol;
        }
    }
    return user_names;  
}
// создаёт двумерный массив
char** create_arr(const std::pair<int, int> size) {
    char** arr = new char* [size.first]; // аллоцирует память
    for (int i = 0; i < size.first; i++) {
        arr[i] = new char[size.second];
    }

    for (int i = 0; i < size.first; i++) { // наполняет массив символом -
        for (int j = 0; j < size.second; j++) {
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


int main() {
    int rows, cols;
    std::pair<int, int> size;
    int step = 0;
    std::cout << "enter rows, columns (r c): ";
    while (true) {
        if (!(std::cin >> rows >> cols)) {
            std::cout << "You must enter two digits. Enter again: " << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        else {
            size = std::make_pair(rows, cols);
            break;
        }
    }
    char** arr = create_arr(size);
    std::pair<char, char> symbols(user_symbol(step));
    while (symbols.first == symbols.second) {
        std::cout << "Player characters must be different!." << std::endl;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        symbols = user_symbol(step);
    }

    while (true) {
        display_board(arr, size.first, size.second);
        char current_symbol;
        if (step % 2 == 0) {                // выбирает символ для текущего хода
            current_symbol = symbols.first;
        }
        else {
            current_symbol = symbols.second;
        }
        std::cout << "Now it's " << current_symbol << " turn!" << std::endl;
        insert_symbol(user_coordinate(size), current_symbol, arr, step);

        if (win_check(arr, current_symbol, size)) {               // если текущий символ побеждает удаляет доску и завершает игру
            delete_arr(arr, rows);
            break;
        } 
        else if ((size.first*size.second) == step+1) {
            std::cout << "DRAW!" << std::endl;
            break;
        }
    }
}