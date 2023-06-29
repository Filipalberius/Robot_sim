#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "Robot/Robot.h"

using namespace std;

int main(int argc, char* argv[]) {
    const int GRID_ROWS = 5;
    const int GRID_COLS = 5;

    string commandFile = "../../../resources/";
    commandFile.append(argv[1]);

    ifstream inputFile(commandFile);
    string command;
    Robot robot(GRID_ROWS, GRID_COLS);

    while (getline(inputFile, command)) {
        robot.runCommand(command);
    }

    return 0;
}
