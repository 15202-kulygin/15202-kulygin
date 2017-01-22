#ifndef _SIMD_MATRIXHAND_H_
#define _SIMD_MATRIXHAND_H_


#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <iomanip>
#include "xmmintrin.h"

//#define N 4

class MatrixHand {
public:
    MatrixHand(unsigned size, float val = 1) : size_(size) {
        matrix_ = new float[size_*size_]();

        for(unsigned i = 0; i < size_; ++i) {
            set(i, i, val);
        }
    }

    MatrixHand(unsigned size, const std::vector<float> &val) : size_(size) {
        if(val.size() < size_*size_) {
            throw std::runtime_error("Need more values");
        }

        matrix_ = new float[size_*size_]();

        for(unsigned i = 0; i < size_; ++i) {
            for(unsigned j = 0; j < size_; ++j) {
                set(i, j, val[i * size_ + j]);
            }
        }
    }

    MatrixHand(const MatrixHand &other) : size_(other.size_) {
        matrix_ = new float[size_*size_]();

        memcpy(matrix_, other.matrix_, size_ * size_ * sizeof(float));
    }

    MatrixHand &operator= (const MatrixHand &other) {
        if(this != &other) {
            if(size_ != other.size_) {
                delete[] matrix_;
                size_ = other.size_;
                matrix_ = new float[size_*size_];
            }
            memcpy(matrix_, other.matrix_, size_ * size_ * sizeof(float));
        }

        return *this;
    }

    ~MatrixHand() {
        delete[] matrix_;
        matrix_ = nullptr;
    }

    void print() const {
        for(unsigned i = 0; i < size_; ++i) {
            for(unsigned j = 0; j < size_; ++j) {
                std::cout << std::fixed << std::setprecision(1) << (get(i, j)) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void set(unsigned h, unsigned w, float val) {
        *(matrix_ + h * size_ + w) = val;
    }

    float get(unsigned h, unsigned w) const {
        return *(matrix_ + h * size_ + w);
    }

    MatrixHand transpose() const {
        MatrixHand result(size_);
        for(unsigned i = 0; i < size_; ++i) {
            for(unsigned j = 0; j < size_; ++j) {
                result.set(j, i, get(i, j));
            }
        }
        return result;
    }





    MatrixHand operator* (const MatrixHand &other) const {
        if(size_ != other.size_) {
            throw std::runtime_error("MatrixHand have different size");
        }
        MatrixHand result(size_);
        __m128 *m1 = (__m128*)matrix_;
        MatrixHand transposed = other.transpose();
        __m128 *m2 = (__m128*)(transposed.matrix_);
        /*for (int i = 0; i < 4*4; ++i)
        {
            std::cout << transposed.matrix_[i] << " ";
            if (3 == i%4)
                std::cout << std::endl;
        }

        std::cout << "CHECKING" << std::endl;
        this->print();
        transposed.print();
        std::cout << "CHECKING END" << std::endl;*/
        
        int N = size_;
        float * res_matrix = new float[N*N]();
        for(unsigned i = 0; i < N; ++i) 
        {
            for(unsigned j = 0; j < N; ++j) 
            {
                res_matrix[i*N+j]=inner2(matrix_+i*N,transposed.matrix_+j*N);
            }
        }
        free(result.matrix_);
        result.matrix_ = res_matrix;
        return result;
    }
    


    
float inner2(float* x, float* y) const{
        int N = size_;
  __m128 *xx, *yy;
  __m128 p, s;
  xx = (__m128*)x;
  yy = (__m128*)y;
  s = _mm_setzero_ps();
  for(int i=0; i<N/4; i++){
    p = _mm_mul_ps(xx[i],yy[i]);
    s = _mm_add_ps(s,p);
  }
  p = _mm_movehl_ps(p,s);
  s = _mm_add_ps(s,p);
  p = _mm_shuffle_ps(s,s,1);
  s = _mm_add_ss(s,p);
  float sum;
  _mm_store_ss(&sum,s);
  return sum;
}


    MatrixHand operator+ (const MatrixHand &other) const 
    {
        MatrixHand result(size_, 0);
        __m128 *m1 = (__m128*)matrix_;
        __m128 *m2 = (__m128*)other.matrix_;
        __m128 *m3 = (__m128*)result.matrix_;
        for(size_t i = 0; i < size_*size_/4; ++i) {
            m3[i] = _mm_add_ps(m1[i],m2[i]);
        }
        return result;
    }

    MatrixHand operator- (const MatrixHand &other) const 
    {
        MatrixHand result(size_, 0);
        __m128 *m1 = (__m128*)matrix_;
        __m128 *m2 = (__m128*)other.matrix_;
        __m128 *m3 = (__m128*)result.matrix_;
        for(size_t i = 0; i < size_*size_/4; ++i) {
            m3[i] = _mm_sub_ps(m1[i],m2[i]);
        }

        return result;
    }

    MatrixHand operator/(float number) const
    {
        int N = size_;
        MatrixHand res(size_);
        delete res.matrix_;
        float * result = new float[N*N]();
        __m128 *m1 = (__m128*)matrix_;
        __m128 m2 = {number, number, number ,number};
        __m128 *m3 = (__m128*)result;
        for(unsigned j = 0; j < N*N/4; j++) 
        {
            m3[j]=_mm_div_ps(m1[j],m2);
        }
        res.matrix_ = result;
        return res;
    }
    MatrixHand operator*(float number) const
    {
        int N = size_;
        MatrixHand res(size_);
        delete res.matrix_;
        float * result = new float[N*N]();
        __m128 *m1 = (__m128*)matrix_;
        __m128 m2 = {number, number, number ,number};
        __m128 *m3 = (__m128*)result;
        for(unsigned j = 0; j < N*N/4; j++) 
        {
            m3[j]=_mm_mul_ps(m1[j],m2);
        }
        res.matrix_ = result;
        return res;
    }



float firstConst() const
{
  int N = size_;
  __m128 *d = (__m128*)matrix_;
  __m128 tmp,tmp2;
  float sum = 0;
  float max = 0;
  for(unsigned i = 0; i < N; ++i) {
    tmp = _mm_setzero_ps();
    for(unsigned j=0; j < N/4; ++j) {
      tmp = _mm_add_ps(tmp, d[i*N/4+j]);
    }
    tmp2 = _mm_shuffle_ps(tmp,tmp,1);
    tmp = _mm_add_ss(tmp,tmp2);
    tmp2 = _mm_shuffle_ps(tmp,tmp,2);
    tmp = _mm_add_ss(tmp,tmp2);
    tmp2 = _mm_shuffle_ps(tmp,tmp,3);
    tmp = _mm_add_ss(tmp,tmp2);
    _mm_store_ss(&sum, tmp);
    if(max < sum) {
      max = sum;
    }
  }
  return max;
}

float secondConst() const
{
    MatrixHand temp = this->transpose();
    return temp.firstConst();
}

MatrixHand reverse(unsigned count) const {
        MatrixHand result(size_);
        MatrixHand I(size_);
        MatrixHand B = this->transpose() / (firstConst() * secondConst());
        MatrixHand R = I - B*(*this);
        const MatrixHand constR = R;

        for(unsigned i = 1; i < count; ++i) {
            result = result + R;
            R = R * constR;
        }

        return result * B;
    }





private:
    float * matrix_ = nullptr;
    unsigned size_ = 0;
};





#endif //_SIMD_MATRIXHAND_H_


   /* float firstConst() const {
        __m128 *d = (__m128*)matrix_;
        __m128 tmp;
        float sum = 0;
        float max = 0;
        for(unsigned i = 0; i < size_; ++i) {
            tmp = _mm_setzero_ps();
            for(unsigned j = 0, size = size_ / 4; j < size; ++j) {
                tmp = _mm_add_ps(tmp, d[j]);
            }
            __m128 res;
            res = _mm_movehl_ps(res,tmp);
            tmp = _mm_add_ps(tmp, res);
            res = _mm_shuffle_ps(tmp, tmp, 1);
            tmp = _mm_add_ss(res, tmp);
            _mm_store_ss(&sum, tmp);
            if(max < sum) {
                max = sum;
            }
        }

        return max;
    }

    float secondConst() const {
        __m128 *d = (__m128*)matrix_;
        __m128 tmp;
        float sum = 0;
        float max = 0;
        for(unsigned i = 0; i < size_; ++i) {
            tmp = _mm_setzero_ps();
            for(unsigned j = 0, size = size_ / 4; j < size; ++j) {
                tmp = _mm_add_ps(tmp, d[j]);
            }
            __m128 res;
            res = _mm_movehl_ps(res,tmp);
            tmp = _mm_add_ps(tmp, res);
            res = _mm_shuffle_ps(tmp, tmp, 1);
            tmp = _mm_add_ss(res, tmp);
            _mm_store_ss(&sum, tmp);
            if(max < sum) {
                max = sum;
            }
        }

        return max;
    }

    MatrixHand reverse(unsigned count) const {
        MatrixHand result(size_);
        MatrixHand I(size_);
        MatrixHand B = this->transpose() / (firstConst() * secondConst());
        MatrixHand R = I - B*(*this);
        const MatrixHand constR = R;

        for(unsigned i = 1; i < count; ++i) {
            result = result + R;
            R = R * constR;
        }

        return result * B;
    }

    MatrixHand operator/ (float d) const {
        return (*this) * (1.0/d);
    }

    MatrixHand operator* (float d) const {
        MatrixHand result(size_);
        __m128 * data = (__m128*)result.matrix_;
        __m128 tmp = {d, d, d ,d};
        for(unsigned i = 0; i < size_; ++i) {
            for(unsigned j = 0, size = size_ / 4; j < size; ++j) {
                data[j] = _mm_mul_ps(data[j], tmp);
            }
        }

        return result;
    }*/