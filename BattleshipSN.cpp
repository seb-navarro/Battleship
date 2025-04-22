#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;


const string default_grid[5][5] = {
    {"A", "O", "O", "O", "O"}, 
    {"B", "O", "O", "O", "O"}, 
    {"C", "O", "O", "O", "O"}, 
    {"D", "O", "O", "O", "O"}, 
    {" ", "1", "2", "3", "4"}
};

const int default_ships = 4;


class Board {
    public:

        int ships_left = 4;

        string grid[5][5] = {
            {"A", "O", "O", "O", "O"}, 
            {"B", "O", "O", "O", "O"}, 
            {"C", "O", "O", "O", "O"}, 
            {"D", "O", "O", "O", "O"}, 
            {" ", "1", "2", "3", "4"}
        };

        string hidden_grid[5][5] = {
            {"A", "O", "O", "O", "O"}, 
            {"B", "O", "O", "O", "O"}, 
            {"C", "O", "O", "O", "O"}, 
            {"D", "O", "O", "O", "O"}, 
            {" ", "1", "2", "3", "4"}
        };


        void show_board() {
            cout << endl;
            for (int a = 0; a < 5; a++) {
                for (int b = 0; b < 5; b++) {
                    cout << grid[a][b] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }


        void show_hidden_board() {
            cout << endl;
            for (int a = 0; a < 5; a++) {
                for (int b = 0; b < 5; b++) {
                    cout << hidden_grid[a][b] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }


        bool mark_grid(string x, string y, bool is_shot) {
            for (int a = 0; a < 5; a++) {
                if (y == grid[a][0]){
                    for (int b = 0; b < 5; b++) {
                        if (x == grid[4][b]){
                            if (is_shot == true) {
                                if (grid[a][b] == "#") {
                                    cout << endl;
                                    cout << "HIT";
                                    cout << endl;
                                    grid[a][b] = "X";
                                    hidden_grid[a][b] = "X";
                                    ships_left -= 1;
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
    cout << "1. Position your ships on the grid (4 ships total - Ships = # ). \n";
    cout << "2. Take turns attempting to sink the enemy ships by specifying firing coordinates. \n";
    cout << "3. A hit will be indicated by an 'X', and a miss will be indicated by a ' '. \n";
    cout << "4. The enemy will try to sink your ships. \n";
    cout << "5. First to sink all the opposing ships wins! \n";

    cout << endl;
    sleep_for(seconds(2));
    cout << "Press ENTER to Begin Playing BATTLESHIP";
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


void show_enemy_ships() {
    cout << endl;
    cout << "ENEMY SHIPS STILL AFLOAT \n";
    EnemyBoard.show_board();
}


string get_coordinate_x() {
    string coordinate;
    cout << "Input X Coordinate: ";
    cin >> coordinate;

    while (coordinate != "1" && coordinate != "2" && coordinate != "3" && coordinate != "4"){
        cout << "*ERROR* - Please select 1, 2, 3, or 4: ";
        cin >> coordinate;
    }

    return coordinate;
}


string get_coordinate_y() {
    string coordinate;
    cout << "Input Y Coordinate: ";
    cin >> coordinate;

    while (coordinate != "a" && coordinate != "A" && coordinate != "b" && coordinate != "B" && coordinate != "c" && coordinate != "C" && coordinate != "d" && coordinate != "D"){
        cout << "*ERROR* - Please select A, B, C, or D: ";
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
    for (int a = 4; a > 0; a--) {
        show_player_board();

        bool success = false;

        while(success == false){
            cout << "Position Ship ("; cout << a; cout << " Remaining) \n";
            string ship_x = get_coordinate_x();
            string ship_y = get_coordinate_y();

            success = PlayerBoard.mark_grid(ship_x, ship_y, false);

            if (success == false) {
                cout << endl;
                cout << "*ERROR* - INVALID SHIP PLACEMENT \n";
                cout << "SHIP ALREADY IN SPECIFIED POSITION \n";
                cout << endl;
            }  
        }
    }
    show_player_board();
}


void position_enemy_ships() {
    string x_coordinates[6] = {"1", "2", "3", "4"};
    string y_coordinates[4] = {"A", "B", "C", "D"};

    for (int a = 4; a > 0; a--) {
        bool success = false;

        while(success == false){
            int x_index = (rand() % 4);
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
            cout << "*ERROR* - INVALID SHOT PLACEMENT \n";
            cout << "PLEASE SELECT A COORDINATE THAT HAS NOT PREVIOUSLY BEEN FIRED ON \n";
            cout << endl;
        }
    }
}


void enemy_fire() {
   string x_coordinates[6] = {"1", "2", "3", "4"};
   string y_coordinates[4] = {"A", "B", "C", "D"};

   bool success = false;

    while (success == false) {
        int x_index = (rand() % 4);
        int y_index = (rand() % 4);

        string x_pick = x_coordinates[x_index];
        string y_pick = y_coordinates[y_index];

        success = PlayerBoard.mark_grid(x_pick, y_pick, true);
    }
}


void game_over() {
    sleep_for(seconds(2));
    cout << "The enemy has destroyed all your ships! \n";
    sleep_for(seconds(2));
    cout << endl;
    show_enemy_ships();
    sleep_for(seconds(2));
    cout << "GAME OVER \n";
}


void game_win() {
    sleep_for(seconds(2));
    cout << "You have destroyed all the enemy ships! \n";
    sleep_for(seconds(2));
    cout << "*****YOU WIN***** \n";
}


void game_draw() {
    sleep_for(seconds(2));
    cout << "The last shots have destroyed both the enemy and your last ship simultaneously! \n";
    sleep_for(seconds(2));
    cout << "THE GAME IS A DRAW \n";
}


bool round() {
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

    if (PlayerBoard.ships_left == 0 && EnemyBoard.ships_left == 0) {
        game_draw();
        return false;
    } else if (PlayerBoard.ships_left == 0) {
        game_over();
        return false;
    } else if (EnemyBoard.ships_left == 0) {
        game_win();
        return false;
    } else {
        return true;
    }
}


void play_game(bool replay) {
    string choice;

    if (replay == true) {
        for (int a = 0; a < 5; ++a)
            for (int b = 0; b < 5; ++b)
                PlayerBoard.grid[a][b] = default_grid[a][b];

        for (int a = 0; a < 5; ++a)
            for (int b = 0; b < 5; ++b)
                PlayerBoard.hidden_grid[a][b] = default_grid[a][b];

        for (int a = 0; a < 5; ++a)
            for (int b = 0; b < 5; ++b)
                EnemyBoard.grid[a][b] = default_grid[a][b];

        for (int a = 0; a < 5; ++a)
            for (int b = 0; b < 5; ++b)
                EnemyBoard.hidden_grid[a][b] = default_grid[a][b];

        PlayerBoard.ships_left = default_ships;
        EnemyBoard.ships_left = default_ships;

        cout << "Welcome Back To BATTLESHIP \n";
        cout << "Press ENTER To Begin";
        cin.get();
        cin.get();
        cout << endl;
    }

    position_player_ships();
    position_enemy_ships();
    cout << "Ships (#) In Position \n";
    cout << "Press ENTER to Acknowledge";
    cin.get();
    cin.get();
    cout << endl;
    cout << endl;

    show_enemy_board();
    sleep_for(seconds(2));
    show_player_board();
    sleep_for(seconds(2));

    bool repeat = true;

    while (repeat == true) {
        repeat = round();
    }

    sleep_for(seconds(2));
    cout << "Would You Like To Play Again? (Y/N): ";
    cin >> choice;
    cout << endl;

    while (choice != "Y" && choice != "y" && choice != "N" && choice != "n") {
        cout << "*ERROR* - Please select YES with 'Y' or NO with 'N': ";
        cin >> choice;
        cout << endl;
    }

    if (choice == "Y" || choice == "y") {
        play_game(true);
    } else if (choice =="N" || choice == "n") {
        sleep_for(seconds(2));
        cout << "Thank You For Playing \n";
        cout << "Made by Sebastian Navarro \n";
        sleep_for(seconds(2));
        cout  << "Press ENTER to Exit";
        cin.get();
        cin.get();
        cout << endl;
        sleep_for(seconds(1));
    }
}



int main() {
    srand(time(NULL));

    startmenu();

    play_game(false);

    return 0;
}