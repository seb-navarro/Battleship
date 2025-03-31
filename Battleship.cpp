#include <iostream>
using namespace std;

int main() {

    string board[5][7] = {{"A", "O", "O", "O", "O", "O", "O"}, {"B", "O", "O", "O", "O", "O", "O"}, {"C", "O", "O", "O", "O", "O", "O"}, {"D", "O", "O", "O", "O", "O", "O"}, {" ", "1", "2", "3", "4", "5", "6"}};

    for (int a = 0; a < 5; a++) {
        for (int b = 0; b < 7; b++) {
            cout << board[a][b] << " ";
        }
        cout << endl;
    }

    return 0;
}