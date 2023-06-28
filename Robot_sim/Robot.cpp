#include "robot.h"

class Robot {
public:
    Robot(int initialRow, int initialColumn, char initialDirection)
        : row(initialRow), column(initialColumn), direction(initialDirection) {}

    void moveForward() {
        // Update the robot's position based on its direction
        // Handle grid boundaries appropriately
    }

    void turnLeft() {
        // Update the robot's direction to the left
    }

    void turnRight() {
        // Update the robot's direction to the right
    }

private:
    int row;
    int column;
    char direction;
};
