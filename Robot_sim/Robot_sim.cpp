#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

// Create a typedef for convenience
typedef vector<vector<char>> Grid;

class Robot {
    public:
        Robot(int rows, int cols){
            // Initialize the grid
            grid = initializeGrid(rows, cols);
        }

        // Parser for lines in text input files
        void runCommand(string command) {
            istringstream commandStream(command);
            string prompt;
            commandStream >> prompt;

            if (prompt == "PLACE") {
                string x;
                string y;
                string f;

                // If PLACE command: get pose from rest of line
                commandStream >> x;
                commandStream >> y;
                commandStream >> f;

                try {
                    placeRobot(stoi(x), stoi(y), heading_to_id[f]);
                }
                catch (const char* msg) {
                    cerr << msg << endl;
                }
            }
            else if (row != -1) {  // Check Robot is placed
                if (prompt == "MOVE") {
                    try {
                        moveForward();
                    }
                    catch (const char* msg) {
                        cerr << msg << endl;
                    }
                }
                else if (prompt == "RIGHT") {
                    turnRight();
                }
                else if (prompt == "LEFT") {
                    turnLeft();
                }
                else if (prompt == "REPORT") {
                    report();
                }
                else {
                    cerr << "Unrechognized command." << endl;
                }
            }
            else {
                cerr << "Robot must first be placed!" << endl;
            }
        }

    private:
        int row = -1;
        int col = -1;
        int heading = -1;

        Grid grid;

        map<string, int> heading_to_id{{"NORTH", 0}, {"EAST", 1}, {"SOUTH", 2}, {"WEST", 3}};
        map<int, string> id_to_heading{{0, "NORTH"}, {1, "EAST"}, {2, "SOUTH"}, {3, "WEST"}};

        // Function to initialize the grid with empty spaces
        Grid initializeGrid(int rows, int cols) {
            Grid grid(rows, vector<char>(cols, '-'));
            return grid;
        }

        void placeRobot(int x, int y, int f) {
            if (x > -1 && x < grid.size() && y > -1 && y < grid[0].size()) {
                row = x;
                col = y;
                heading = f;
            }
            else {
                throw "Can't place the robot outside the grid!";
            }
        }

        void moveForward() {
            bool success = false;
            grid[row][col] = '-';

            switch (heading) {
                case 0: // North
                    if (row > 0) {
                        row--;
                        success = true;
                    }
                    break;
                case 1: // East
                    if (col < grid.size() - 1) {
                        col++;
                        success = true;
                    }
                    break;
                case 2: // South
                    if (row < grid[0].size() - 1) {
                        row++;
                        success = true;
                    }
                    break;

                case 3: // West
                    if (col > 0) {
                        col--;
                        success = true;
                    }
                    break;
               }

            grid[row][col] = 'x';

            if (!success) {
                throw "Out of bounds! Can't perform move.";
            }
        }

        void turnLeft() {
            heading = (heading - 1 + 4) % 4;
        }

        void turnRight() {
            heading = (heading + 1) % 4;
        }

        void report() {
            printGrid();
            cout << "heading: " << id_to_heading[heading] << endl;
        }

        // Function to print the grid
        void printGrid() {
            for (const auto& row : grid) {
                for (const auto& cell : row) {
                    cout << cell << ' ';
                }
                cout << endl;
            }
        }
};

int main() {
    // Define the dimensions of the grid
    const int GRID_ROWS = 5;
    const int GRID_COLS = 5;

    // Read commands from the text file
    ifstream inputFile("commands.txt");
    string command;
    Robot robot(GRID_ROWS, GRID_COLS);

    while (std::getline(inputFile, command)) {
        // Handle the command and update the robot and grid accordingly
        robot.runCommand(command);
    }

    return 0;
}