#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "Matrix.h"
#include "MatrixBlas.h"
#include "MatrixHand.h"


//4218d

//g++ -std=c++11 -O3 main.cpp -lblas

int main() {
    srand(time(NULL));

//  
    unsigned matrixSize = 4;
    if (0 != matrixSize % 4)
    {
        std::cout << "Wrong matrix size - it should be times four" << std::endl;
        return -1;
    }
    unsigned countRepeat = 10000;
    //unsigned matrixSize = 8;
    //std::vector<float> arr = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    /*std::vector<float> arr = 
    {0, 0, 1, 1, 1, 0, 0, 0,
     1, 1, 1, 0, 0, 0, 0, 1,
     1, 0, 1, 1, 0, 0, 1, 0,
     0, 1, 1, 0, 1, 0, 1, 1,
     1, 1, 1, 1, 1, 1, 0, 1,
     0, 0, 1, 1, 1, 1, 0, 1,
     0, 1, 1, 0, 1, 0, 0, 0,
     1, 0, 0, 0, 1, 0, 1, 0};*/
    //reverse
    /*

    */
    std::vector<float> arr(matrixSize*matrixSize);
    //arr.reserve(matrixSize*matrixSize);
    for (size_t i = 0; i < matrixSize; i++) {
    for (size_t j = 0; j < matrixSize; j++) {
      arr[i*matrixSize+j]=rand()%10;
    }
  }


    /*{
        Matrix matrix(matrixSize, arr);
        
        auto start = clock();

        Matrix matrix1 = matrix.reverse(countRepeat);
        Matrix matrix2 = matrix * matrix1;
        Matrix I(matrixSize, 1);
        Matrix check = I - matrix2;
        std::cout << "CHECK W/O SIMD" << std::endl;
        //check.print();
        
        //matrix.print();
        //matrix1.print();
        
        std::cout << (double) (clock() - start) / CLOCKS_PER_SEC << std::endl;
    }

    {
        MatrixBlas matrix(matrixSize, arr);
        
        auto start = clock();

        MatrixBlas matrix1 = matrix.reverse(countRepeat);
        MatrixBlas matrix2 = matrix * matrix1;
        MatrixBlas I(matrixSize, 1);
        MatrixBlas check = I - matrix2;
        std::cout << "CHECK WITH BLAS" << std::endl;
        //check.print();

        //matrix.print();
        //matrix1.print();
        


        std::cout << (double) (clock() - start) / CLOCKS_PER_SEC << std::endl;
    }*/

    {
        MatrixHand matrix(matrixSize, arr);
        //matrix.print();
        auto start = clock();

        MatrixHand matrix1 = matrix.reverse(countRepeat);
        MatrixHand I(matrixSize, 1);
        //I.print();
        //MatrixHand matrix1 = matrix * matrix;
        MatrixHand matrix2 = matrix * matrix1;
        MatrixHand check = I - matrix2;
        std::cout << "CHECK HANDMADE" << std::endl;
        check.print();


        std::cout << (double) (clock() - start) / CLOCKS_PER_SEC << std::endl;
    }

    return 0;
}