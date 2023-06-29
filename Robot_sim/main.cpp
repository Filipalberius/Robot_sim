#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "Robot.h"
using namespace std;

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