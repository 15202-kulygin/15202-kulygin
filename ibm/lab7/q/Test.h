#ifndef _SIMD_TEST_H_
#define _SIMD_TEST_H_

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "vector"
#include "time.h"

using std::vector;

#define MAX_SIZE 256

class matrix{
private:
    float v[MAX_SIZE][MAX_SIZE];
    int size;

public:
    matrix(int size_) : size(size_){
    }

    matrix operator * (const matrix & b){
        matrix result(size);
        for(int i = 0; i < size; ++i){
            for(int j = 0; j < size; ++j){
                float temp_sum = 0.0f;
                for(int pos = 0; pos < size; ++pos){
                    temp_sum += v[i][pos] * b.v[pos][j];
                }
                result.v[i][j] = temp_sum;
            }
        }
        return result;
    }

    matrix operator - (const matrix & b){
        matrix result(size);
        for(int i = 0; i < size; ++i){
            for(int j = 0; j < size; ++j){
                result.v[i][j] = v[i][j] - b.v[i][j];
            }
        }
        return result;
    }

    matrix operator / (float  b){
        matrix result(size);
        for(int i = 0; i < size; ++i){
            for(int j = 0; j < size; ++j){
                result.v[i][j] = v[i][j] / b;
            }
        }
        //result.print();
        return result;
    }

    matrix operator + (const matrix & b){
        matrix result(size);
        for(int i = 0; i < size; ++i){
            for(int j = 0; j < size; ++j){
                result.v[i][j] = v[i][j] + b.v[i][j];
            }
        }
        return result;
    }

    matrix operator ^ (int count){
        matrix result(*this);
        for(int i = 1; i < count; ++i){
            result = result * (*this);
        }
        return result;
    }

    matrix transpose() const {
        matrix result(size);
        for(int i = 0; i < size; ++i){
            for(int j = 0; j < size; ++j){
                result.v[i][j] = v[j][i];
            }
        }
        return result;
    }

    void print(){
        printf("\n");
        for(int i = 0; i < size; ++i){
            for(int j = 0; j < size; ++j){
                printf("%f ", v[i][j]);
            }
            printf("\n");
        }
    }

    float first_magic_number() const {
        float maximum = -1.0f;
        for(int i = 0; i < size; ++i){
            float temp_sum = 0.0f;
            for(int j = 0; j < size; ++j){
                temp_sum += abs(v[i][j]);
            }
            maximum = (maximum < temp_sum) ? (temp_sum) : (maximum);
        }
        return maximum;
    }

    float second_magic_number() const {
        float maximum = -1.0f;
        for(int i = 0; i < size; ++i){
            float temp_sum = 0.0f;
            for(int j = 0; j < size; ++j){
                temp_sum += abs(v[j][i]);
            }
            maximum = (maximum < temp_sum) ? (temp_sum) : (maximum);
        }
        return maximum;
    }

    void rand(){
//        for(int i = 0; i < size; ++i){
//            for(int j = 0; j < size; ++j){
//                v[i][j] = ::rand() % 10000;
//            }
//        }
//        v[0][0] = 2;
//        v[0][1] = 5;
//        v[0][2] = 7;
//        v[1][0] = 6;
//        v[1][1] = 3;
//        v[1][2] = 4;
//        v[2][0] = 5;
//        v[2][1] = -2;
//        v[2][2] = -3;
        v[0][0] = 1;
        v[0][1] = 2;
        v[0][2] = 7;
        v[0][3]=3;
        v[1][0]=2;
        v[1][1]=4;
        v[1][2]=5;
        v[1][3]=6;
        v[2][0]=7;
        v[2][1]=2;
        v[2][2]=8;
        v[2][3]=7;
        v[3][0]=-1;
        v[3][1]=2;
        v[3][2]=3;
        v[3][3]=7;
    }

    void E(){
        for(int i = 0; i < size; ++i){
            v[i][i] = 1.0f;
        }
    }
};


//int main(){
//    int real_size = 0;
//    int step_count = 0;
//
//    scanf("%i %i", &real_size, &step_count);
//    int start_time = clock();
//
//    matrix I(real_size);
//    matrix A(real_size);
//    matrix reverse_in(real_size);
//
//    A.rand();
//    I.E();
//
//    matrix B(real_size);
//    B = A.transpose() / (A.first_magic_number() * A.second_magic_number());
//    matrix R(real_size);
//    R = I - B * A;
//
//    reverse_in = I;
//
//    matrix Rtemp(R);
//    for(int i = 1; i < step_count; ++i){
//        reverse_in = reverse_in + R;
//        R = R * Rtemp;
//    }
//
//    reverse_in = reverse_in * B;
//
//#ifdef DEBUG
//    printf("A:");
//	A.print();
//	printf("A ^ -1:");
//	reverse_in.print();
//	printf("A * A ^ -1:");
//	(reverse_in * A).print();
//#endif
//
//    printf("\nTime (msec): %i\n", (int)((clock() - start_time) / 1000));
//
//    return 0;
//}

#endif //_SIMD_TEST_H_
