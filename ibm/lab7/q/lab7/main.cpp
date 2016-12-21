#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Matrix.h"
#include "MatrixBlas.h"
#include "MatrixHand.h"


//4218

//g++ -std=c++11 -O3 main.cpp -lblas

int main() {
    srand(time(NULL));

//    unsigned matrixSize = 2048;
    unsigned countRepeat = 10000;
    unsigned matrixSize = 4;
    //std::vector<float> arr = {1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0};
    arr.reserve(matrixSize*matrixSize);
    for(unsigned i = 0, size = matrixSize*matrixSize; i < size; ++i) {
        arr.push_back(rand());
        for (int j = 0; j < matrixSize; ++j)
        {arr[i*matrixSize + j] = }
    }


    {
        Matrix matrix(matrixSize, arr);
        //matrix.print();
        auto start = clock();

        Matrix matrix1 = matrix.reverse(countRepeat);
        //matrix1.print();

        std::cout << (double) (clock() - start) / CLOCKS_PER_SEC << std::endl;
    }

    {
        MatrixBlas matrix(matrixSize, arr);
        auto start = clock();

        MatrixBlas matrix1 = matrix.reverse(countRepeat);

        std::cout << (double) (clock() - start) / CLOCKS_PER_SEC << std::endl;
    }

    {
        MatrixHand matrix(matrixSize, arr);
        auto start = clock();

        MatrixHand matrix1 = matrix.reverse(countRepeat);

        std::cout << (double) (clock() - start) / CLOCKS_PER_SEC << std::endl;
    }

    return 0;
}