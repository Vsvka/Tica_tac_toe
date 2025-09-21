

#include <iostream>
#include <vector>
using namespace std;


//board set up
void printBoard(const vector<char>& board) {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        cout << " " << (board[i] == ' ' ? char('1' + i) : board[i]);
        if (i % 3 != 2) cout << " |";
        if (i % 3 == 2 && i != 8) cout << "\n-----------\n";
    }
    cout << "\n\n";
}

//function for checking winning condition
bool checkWin(const vector<char>& board, char player) {
    vector<vector<int>> wins = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8}, 
        {0,4,8}, {2,4,6}           
    };
    for (vector<int> line : wins) {
        if (board[line[0]] == player && board[line[1]] == player && board[line[2]] == player) {
            return true;
        }
    }
    return false;
}


//checking if all spots are filled
bool boardCheck(const vector<char>& board) {
    for (char c : board) if (c == ' ') return false;
    return true;
}


//main function where everything is connected
int main() {
    vector<char> board(9, ' ');
    char current = 'X';
    cout << "Welcome to Tic-Tac-Toe\nPlayer 1: X, Player 2: O\n";
    while (true) {
        printBoard(board);
        int move;
        cout << "Player " << current << ", turn (1-9): ";
        if (!(cin >> move)) {
            cout << "Invalid input. Try again please.\n";
            break;
        }
        if (move < 1 || move > 9 || board[move - 1] != ' ') {
            cout << "Invalid move. Try again please.\n";
            continue;
        }
        board[move - 1] = current;
        if (checkWin(board, current)) {
            printBoard(board);
            cout << current << " won\n";
            break;
        }
        if (boardCheck(board)) {
            printBoard(board);
            cout << "Tie\n";
            break;
        }
        current = (current == 'X') ? 'O' : 'X';
    }
    return 0;
}
