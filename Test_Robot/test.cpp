#include "pch.h"
#include "../../Robot_sim/Robot_sim/Robot.h"

// Include the necessary headers for your function and dependencies

// Define the function runCommand from your code

// Define a fixture for the unit tests
class RunCommandTest : public ::testing::Test {
protected:
    // Define any setup or teardown functions if required

    // Helper function to compare the grid state with an expected state
    void compareGridState(const Grid& expectedGrid, const Grid& actualGrid) {
        ASSERT_EQ(expectedGrid.size(), actualGrid.size());

        for (size_t i = 0; i < expectedGrid.size(); ++i) {
            ASSERT_EQ(expectedGrid[i].size(), actualGrid[i].size());
            for (size_t j = 0; j < expectedGrid[i].size(); ++j) {
                ASSERT_EQ(expectedGrid[i][j], actualGrid[i][j]);
            }
        }
    }
};

TEST_F(RunCommandTest, TestPlaceCommand) {
    Grid initialGrid = initializeGrid(5, 5);
    Grid expectedGrid = initializeGrid(5, 5);
    expectedGrid[2][3] = 'N';

    runCommand("PLACE 2 3 NORTH");

    compareGridState(expectedGrid, grid);
}

TEST_F(RunCommandTest, TestMoveCommand) {
    // Define the initial grid state and the expected grid state after executing the MOVE command
    Grid initialGrid = initializeGrid(5, 5);
    initialGrid[2][3] = 'N';
    Grid expectedGrid = initializeGrid(5, 5);
    expectedGrid[1][3] = 'N';

    // Create an instance of the class containing the runCommand function
    // Perform any necessary setup

    // Set up the initial grid state
    grid = initialGrid;

    // Execute the MOVE command
    runCommand("MOVE");

    // Compare the grid state after executing the command with the expected grid state
    compareGridState(expectedGrid, grid);
}

// Add more test cases for the other commands

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}