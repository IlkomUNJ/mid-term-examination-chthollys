#ifndef CUSTOMMATRIX_H
#define CUSTOMMATRIX_H

#include <iostream>

using namespace std;

class CustomMatrix{
public:
    // Define the kernel size as a constant
    static const int KERNEL_SIZE = 5;

    // Matrix now uses the kernel size
    bool mat[KERNEL_SIZE][KERNEL_SIZE] = {0};

    CustomMatrix(){

    }

    // Alternate constructor (not recommended, as sizeof(m) won't work)
    CustomMatrix(bool m[KERNEL_SIZE][KERNEL_SIZE]){
        fillMatrix(m);
    }

    // Correct way to fill the matrix
    void fillMatrix(bool m[KERNEL_SIZE][KERNEL_SIZE]){
        for (int i = 0; i < KERNEL_SIZE; i++) {
            for(int j = 0; j < KERNEL_SIZE; j++){
                mat[i][j] = m[i][j];
            }
        }
    }

    // Check if matrix is matched
    bool matches(const CustomMatrix& pattern) const {
        for (int i = 0; i < KERNEL_SIZE; i++) {
            for (int j = 0; j < KERNEL_SIZE; j++) {
                if (mat[i][j] != pattern.mat[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }


    // Check if window is empty (all false)
    bool isEmpty() const {
        for (int i = 0; i < KERNEL_SIZE; i++) {
            for (int j = 0; j < KERNEL_SIZE; j++) {
                if (mat[i][j]) return false;
            }
        }
        return true;
    }

    // Print matrix for debugging
    void print() const {
        for (int i = 0; i < KERNEL_SIZE; i++) {
            for (int j = 0; j < KERNEL_SIZE; j++) {
                cout << (mat[i][j] ? "1" : "0") << " ";
            }
            cout << endl;
        }
    }
};

#endif // CUSTOMMATRIX_H
