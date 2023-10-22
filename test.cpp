#include <iostream>

int main() {
    // Dimensions of the 2D array
    int rows = 3;
    int cols = 4;

    // Create a 2D dynamic array
    int** arr = new int*[rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];
    }

    // Populate the 2D array with some data
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = i * cols + j;
        }
    }

    // Iterate through the 2D dynamic array using pointers
    for (int** rowPtr = arr; rowPtr < arr + rows; rowPtr++) {
        for (int* colPtr = *rowPtr; colPtr < *rowPtr + cols; colPtr++) {
            std::cout << *colPtr << " ";
        }
        std::cout << std::endl;
    }

    // Free the allocated memory
    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
}