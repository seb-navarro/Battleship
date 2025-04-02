#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

string board[5][7] = {{"A", "O", "O", "O", "O", "O", "O"}, {"B", "O", "O", "O", "O", "O", "O"}, {"C", "O", "O", "O", "O", "O", "O"}, {"D", "O", "O", "O", "O", "O", "O"}, {" ", "1", "2", "3", "4", "5", "6"}};

void startmenu(){
    cout << endl;
    cout << "******        **       ********    ********    **          ********     ******     **    **    **    ******    \n";
    cout << "**    **     ** **        **          **       **          **          **          **    **    **    **    **  \n";
    cout << "**    **    **   **       **          **       **          **          **          **    **    **    **    **  \n";
    cout << "******      *******       **          **       **          ********     ******     ********    **    ******    \n";
    cout << "**    **    **   **       **          **       **          **                **    **    **    **    **        \n";
    cout << "**    **    **   **       **          **       **          **                **    **    **    **    **        \n";
    cout << "******      **   **       **          **       ********    ********     ******     **    **    **    **        \n";
    cout << endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout << "Press Enter to Start";
    cin.ignore();
    cin.get();
}

void show_board() {
    cout << endl;
    for (int a = 0; a < 5; a++) {
        for (int b = 0; b < 7; b++) {
            cout << board[a][b] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

string get_coordinate_x() {
    string coordinate;
    cout << "Input X Coordinate to Fire On: ";
    cin >> coordinate;

    while (coordinate != "1" && coordinate != "2" && coordinate != "3" && coordinate != "4" && coordinate != "5" && coordinate != "6"){
        cout << "Please select 1, 2, 3, 4, 5, or 6: ";
        cin >> coordinate;
    }

    return coordinate;
}

string get_coordinate_y() {
    string coordinate;
    cout << "Input Y Coordinate to Fire On: ";
    cin >> coordinate;

    while (coordinate != "a" && coordinate != "A" && coordinate != "b" && coordinate != "B" && coordinate != "c" && coordinate != "C" && coordinate != "d" && coordinate != "D"){
        cout << "Please select A, B, C, or D: ";
        cin >> coordinate;
    }

    if (coordinate == "a"){
        coordinate = "A";
    } else if (coordinate == "b"){
        coordinate = "B";
    } else if (coordinate == "c"){
        coordinate = "C";
    } else if (coordinate == "d"){
        coordinate = "D";
    }

    return coordinate;
}

void fire() {
    string coordinate_x = get_coordinate_x();
    string coordinate_y = get_coordinate_y();

    for (int a = 0; a < 5; a++) {
        if (coordinate_y == board[a][0]){

            for (int b = 0; b < 7; b++) {
                if (coordinate_x == board[4][b]){
                    cout << endl;
                    cout << "HIT";
                    cout << endl;
                    board[a][b] = "X";
                }
            }
        }
       
    }
}


int main() {

    startmenu();

    show_board();

    fire();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    show_board();

    return 0;
}