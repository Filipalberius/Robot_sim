#ifndef ROBOT_H
#define ROBOT_H

class Robot {
public:
    Robot(int initialRow, int initialColumn, char initialDirection)
        : row(initialRow), column(initialColumn), direction(initialDirection) {}

    void moveForward();

    void turnLeft();

    void turnRight();

private:
    int row;
    int column;
    char direction;
};

#endif
