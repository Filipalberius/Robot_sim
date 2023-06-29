#include "./Robot.h"

using namespace std;

Robot::Robot(int rows, int cols){
    gridRows = rows;
    gridCols = cols;
}

void Robot::runCommand(string command) {
    istringstream commandStream(command);
    string prompt;
    commandStream >> prompt;

    if (prompt == "PLACE") {
        string x;
        string y;
        string f;

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
    else if (row != -1) { 
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

    if (positionValid(tmpRow, tmpCol)) {
        row = tmpRow;
        col = tmpCol;
    } else {
        throw "Out of bounds! Can't perform move.";
    }

}

bool Robot::positionValid(int row, int col){
    if (col < 0 || col > gridCols-1 || row < 0 || row > gridRows-1) {
        return false;
    } else {
        return true;
    }
}

void Robot::turnLeft() {
    heading = (heading - 1 + 4) % 4;
}

void Robot::turnRight() {
    heading = (heading + 1) % 4;
}

void Robot::report() {
    printGrid();
    cout << "heading: " << id_to_heading[heading] << endl;
}

void Robot::printGrid() {
    vector<vector<char>> grid(gridRows, vector<char>(gridCols, '-'));

    grid[row][col] = 'x';

    for (const auto& row : grid) {
        for (const auto& cell : row) {
            cout << cell << ' ';
        }
        cout << endl;
    }
}
