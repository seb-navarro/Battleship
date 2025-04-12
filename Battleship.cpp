#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

// Potential Boats = ⛵, 🛥, ⛴, 🚢, 🛥️, 🚤, #

class Board {
    public:

        string grid[5][7] = {
            {"A", "O", "O", "O", "O", "O", "O"}, 
            {"B", "O", "O", "O", "O", "O", "O"}, 
            {"C", "O", "O", "O", "O", "O", "O"}, 
            {"D", "O", "O", "O", "O", "O", "O"}, 
            {" ", "1", "2", "3", "4", "5", "6"}
        };

        string hidden_grid[5][7] = {
            {"A", "O", "O", "O", "O", "O", "O"}, 
            {"B", "O", "O", "O", "O", "O", "O"}, 
            {"C", "O", "O", "O", "O", "O", "O"}, 
            {"D", "O", "O", "O", "O", "O", "O"}, 
            {" ", "1", "2", "3", "4", "5", "6"}
        };

        void show_board() {
            cout << endl;
            for (int a = 0; a < 5; a++) {
                for (int b = 0; b < 7; b++) {
                    cout << grid[a][b] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }

        void show_hidden_board() {
            cout << endl;
            for (int a = 0; a < 5; a++) {
                for (int b = 0; b < 7; b++) {
                    cout << hidden_grid[a][b] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }

        bool mark_grid(string x, string y, bool is_shot) {
            for (int a = 0; a < 5; a++) {
                if (y == grid[a][0]){
                    for (int b = 0; b < 7; b++) {
                        if (x == grid[4][b]){
                            if (is_shot == true) {
                                if (grid[a][b] == "#") {
                                    cout << endl;
                                    cout << "HIT";
                                    cout << endl;
                                    grid[a][b] = "X";
                                    hidden_grid[a][b] = "X";
                                    return true;
                                } else if (grid[a][b] == "O") {
                                    cout << endl;
                                    cout << "MISS";
                                    cout << endl;
                                    grid[a][b] = " ";
                                    hidden_grid[a][b] = " ";
                                    return true;                                    
                                } else {
                                    return false;
                                }
                            } else {
                                if (grid[a][b] == "#") {
                                    return false;
                                } else {
                                    grid[a][b] = "#";
                                    return true;
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
            }
            return false;
        }
};


Board PlayerBoard;
Board EnemyBoard;


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
    sleep_for(seconds(2));

    cout << "Press ENTER to Start";
    cin.get();

    cout << endl;
    cout << "INSTRUCTIONS: \n";
    cout << "1. Position your ships on the grid (10 ships total - Ships = # ). \n";
    cout << "2. Take turns attempting to sink the enemy ships by specifying firing coordinates. \n";
    cout << "3. A hit will be indicated by an 'X', and a miss will be indicated by a ' '. \n";
    cout << "4. The enemy will try to sink your ships. \n";
    cout << "5. First to sink all the opposing ships wins! \n";
    cout << endl;
    sleep_for(seconds(2));

    cout << "Press ENTER to Acknowledge";
    cin.get();
    cout << endl;
}


void show_player_board() {
    cout << endl;
    cout << "PLAYER BOARD \n";
    PlayerBoard.show_board();
}


void show_enemy_board() {
    cout << endl;
    cout << "ENEMY BOARD \n";
    EnemyBoard.show_hidden_board();
}


string get_coordinate_x() {
    string coordinate;
    cout << "Input X Coordinate: ";
    cin >> coordinate;

    while (coordinate != "1" && coordinate != "2" && coordinate != "3" && coordinate != "4" && coordinate != "5" && coordinate != "6"){
        cout << "Please select 1, 2, 3, 4, 5, or 6: ";
        cin >> coordinate;
    }

    return coordinate;
}


string get_coordinate_y() {
    string coordinate;
    cout << "Input Y Coordinate: ";
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


void position_player_ships() {
    for (int a = 5; a > 0; a--) {
        show_player_board();

        bool success = false;

        while(success == false){
            cout << "Position Ship ("; cout << a; cout << " Remaining) \n";
            string ship_x = get_coordinate_x();
            string ship_y = get_coordinate_y();

            success = PlayerBoard.mark_grid(ship_x, ship_y, false);

            if (success == false) {
                cout << endl;
                cout << "INVALID SHIP PLACEMENT \n";
                cout << "SHIP ALREADY IN SPECIFIED POSITION \n";
                cout << endl;
            }  
        }
    }
    show_player_board();
}


void position_enemy_ships() {
    string x_coordinates[6] = {"1", "2", "3", "4", "5", "6"};
    string y_coordinates[4] = {"A", "B", "C", "D"};

    for (int a = 5; a > 0; a--) {
        bool success = false;

        while(success == false){
            int x_index = (rand() % 6);
            int y_index = (rand() % 4);

            string ship_x = x_coordinates[x_index];
            string ship_y = y_coordinates[y_index];

            success = EnemyBoard.mark_grid(ship_x, ship_y, false);
        }
    }
}


void fire() {
    bool success = false;

    cout << "Fire on Enemy Grid \n";

    while (success == false) {
        string coordinate_x = get_coordinate_x();
        string coordinate_y = get_coordinate_y();
        success = EnemyBoard.mark_grid(coordinate_x, coordinate_y, true);

        if (success == false) {
            cout << endl;
            cout << "INVALID SHOT PLACEMENT \n";
            cout << "PLEASE SELECT A COORDINATE THAT HAS NOT PREVIOUSLY BEEN FIRED ON \n";
            cout << endl;
        }
    }
}


void enemy_fire() {
   string x_coordinates[6] = {"1", "2", "3", "4", "5", "6"};
   string y_coordinates[4] = {"A", "B", "C", "D"};

   bool success = false;

    while (success == false) {
        int x_index = (rand() % 6);
        int y_index = (rand() % 4);

        string x_pick = x_coordinates[x_index];
        string y_pick = y_coordinates[y_index];

        success = PlayerBoard.mark_grid(x_pick, y_pick, true);
    }
}


void round() {
    fire();
    sleep_for(seconds(2));
    cout << endl;
    cout << "Enemy's Turn \n";
    sleep_for(seconds(2));
    enemy_fire();
    sleep_for(seconds(2));
    cout << endl;
    cout << "Results \n";
    cout << "   | \n";
    cout << "   V \n";
    sleep_for(seconds(2));
    cout << endl;
    show_enemy_board();
    show_player_board();
}


int main() {
    srand(time(NULL));

    startmenu();

    position_player_ships();
    position_enemy_ships();
    cout << "Ships (#) In Position \n";
    cout << "Press ENTER to Acknowledge";
    cin.get();
    cin.get();
    cout << endl;

    sleep_for(seconds(2));
    cout << endl;
    show_enemy_board();
    sleep_for(seconds(2));
    show_player_board();
    sleep_for(seconds(2));

    round();
    round();
    round();

    return 0;
}