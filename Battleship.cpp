#include <iostream>
using namespace std;

string board[5][7] = {{"A", "O", "O", "O", "O", "O", "O"}, {"B", "O", "O", "O", "O", "O", "O"}, {"C", "O", "O", "O", "O", "O", "O"}, {"D", "O", "O", "O", "O", "O", "O"}, {" ", "1", "2", "3", "4", "5", "6"}};


void show_board() {
    for (int a = 0; a < 5; a++) {
        for (int b = 0; b < 7; b++) {
            cout << board[a][b] << " ";
        }
        cout << endl;
    }
}

string get_coordinate() {
    string coordinate;
    cout << "Input Coordinate to Fire On";
    cin >> coordinate;

    return coordinate;
}

int main() {

    show_board();

    return 0;
}