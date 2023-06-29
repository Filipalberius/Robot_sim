#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class Robot {
public:
    Robot(int rows, int cols);

    void runCommand(string command);

private:
    int gridCols;
    int gridRows;

    int row = -1;
    int col = -1;
    int heading = -1;

    map<string, int> heading_to_id{{"NORTH", 0}, {"EAST", 1}, {"SOUTH", 2}, {"WEST", 3}};
    map<int, string> id_to_heading{{0, "NORTH"}, {1, "EAST"}, {2, "SOUTH"}, {3, "WEST"}};

    void placeRobot(int x, int y, int f);

    void moveForward();

    void turnLeft();

    void turnRight();

    void report();

    bool positionValid(int row, int col);

    void printGrid();
};

#endif
