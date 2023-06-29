#include "./Robot.h"

using namespace std;

Robot::Robot(int rows, int cols){
    // Initialize the grid
    gridRows = rows;
    gridCols = cols;
}

// Parser for lines in text input files
void Robot::runCommand(string command) {
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

void Robot::placeRobot(int x, int y, int f) {
    if (x > -1 && x < gridRows && y > -1 && y < gridCols) {
        row = x;
        col = y;
        heading = f;
    }
    else {
        throw "The robot can't be placed outside the grid!";
    }
}

void Robot::moveForward() {
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

void Robot::turnLeft() {
    heading = (heading - 1 + 4) % 4; // decrease heading with overflow from 0 to 3 (north to west)
}

void Robot::turnRight() {
    heading = (heading + 1) % 4; // increase heading with overflow from 3 to 0 (west to north)
}

void Robot::report() {
    printGrid();
    cout << "heading: " << id_to_heading[heading] << endl;
}

// Function to print the grid
void Robot::printGrid() {
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
