#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

class Robot {
    public:
        Robot(int rows, int cols){
            // Initialize the grid
            gridRows = rows;
            gridCols = cols;
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
        int gridCols;
        int gridRows;

        int row = -1;
        int col = -1;
        int heading = -1;

        // Numerical representation of headings enables some efficient handling of turning
        map<string, int> heading_to_id{{"NORTH", 0}, {"EAST", 1}, {"SOUTH", 2}, {"WEST", 3}};
        map<int, string> id_to_heading{{0, "NORTH"}, {1, "EAST"}, {2, "SOUTH"}, {3, "WEST"}};

        void placeRobot(int x, int y, int f) {
            if (x > -1 && x < gridRows && y > -1 && y < gridCols) {
                row = x;
                col = y;
                heading = f;
            }
            else {
                throw "The robot can't be placed outside the grid!";
            }
        }

        void moveForward() {
            int tmpRow = row;
            int tmpCol = col;

            switch (heading) {
                case 0:  // North
                    tmpRow--;
                    break;
                case 1:  // East
                    tmpCol++;
                    break;
                case 2:  // South
                    tmpRow++;
                    break;
                case 3:  // West
                    tmpCol--;
                    break;
               }

            // Check if move is legal
            if (tmpCol < 0 || tmpCol > gridCols-1 || tmpRow < 0 || tmpRow > gridRows-1) {
                throw "Out of bounds! Can't perform move.";
            } else {
                row = tmpRow;
                col = tmpCol;
            }

        }

        void turnLeft() {
            heading = (heading - 1 + 4) % 4; // decrease heading with overflow from 0 to 3 (north to west)
        }

        void turnRight() {
            heading = (heading + 1) % 4; // increase heading with overflow from 3 to 0 (west to north)
        }

        void report() {
            printGrid();
            cout << "heading: " << id_to_heading[heading] << endl;
        }

        // Function to print the grid
        void printGrid() {
            // Create visual representation of grid
            vector<vector<char>> grid(gridRows, vector<char>(gridCols, '-'));

            grid[row][col] = 'x';

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

    while (getline(inputFile, command)) {
        // Handle the command and update the robot and grid accordingly
        robot.runCommand(command);
    }

    return 0;
}