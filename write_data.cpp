#include <iostream>
#include <fstream>

int main() {
    const int numRows = 3;
    const int numCols = 2;
    int dataArray[numRows][numCols] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };

    std::ofstream outputFile("data.txt");
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            outputFile << dataArray[row][col] << ' ';
        }
        outputFile << '\n';
    }

    outputFile.close();

    return 0;
}
