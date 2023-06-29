#ifndef ROBOT_H
#define ROBOT_H

class Robot {
public:
    Robot(int row, int col);

    void runCommand(string command);
};

#endif