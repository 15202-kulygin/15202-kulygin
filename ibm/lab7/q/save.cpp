#ifndef _SIMD_MATRIXHAND_H_
#define _SIMD_MATRIXHAND_H_


#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include "xmmintrin.h"

#define N 4

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
                std::cout << get(i, j) << " ";
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





    float firstConst() const {
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
        return (*this) * (1/d);
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
        

        __m128 s;
        for(unsigned i = 0; i < size_; ++i) {
            for(unsigned j = 0; j < size_; ++j) {
                if (0 == i)               
                //std::cout << "CHEEEEECK  " << *(((float *)m2) + 4*j ) << " " << *(((float *)m2) + 4*j + 1) << " " << *(((float *)m2)  + 4*j  + 2) << " " << *(((float *)m2) + 4*j  + 3) << std::endl;
                s = _mm_setzero_ps();
                s = _mm_mul_ps(m1 + i,m2 + j);
                __m128 p = _mm_setzero_ps();
                p = _mm_movehl_ps(p,s);
                s = _mm_add_ps(s,p);
                p = _mm_shuffle_ps(s,s,1);
                s = _mm_add_ss(s,p);
                float sum;
                _mm_store_ss(&sum, s);
                
                result.set(i, j, sum);
            }
        }

        return result;
    }
/*MatrixHand operator* (const MatrixHand &other) const {
        __m128 *m1 = (__m128*)matrix_;
        float * transp = other.transpose().matrix_;
        __m128 * m2 = (__m128*)transp;
        float * result = new float[size_*size_];
        MatrixHand res(size_);
        for(unsigned i = 0; i < size_; ++i) 
        {
            for(unsigned j = 0; j < size_; ++j) 
            {
                result[i*size_+j] = inner2(matrix_ + i*size_, transp + j*size_);
                res.set(i, j, result[i*size_ + j]);
                //std::cout << result[i*size_+j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        
        for (int i = 0; i < size_; ++i)
        {
            for (int j = 0; j < size_; ++j)
            {
                res.set(i, j, result[i*size_ + j]);
            }
        }

        return res;
        
    }*/

    MatrixHand operator+ (const MatrixHand &other) const {
        /*if(size_ != other.size_) {
            throw std::runtime_error("MatrixHand have different size");
        }
        MatrixHand result(size_, 0);
        __m128 *m1 = (__m128*)matrix_;
        __m128 *m2 = (__m128*)other.matrix_;
        __m128 *m3 = (__m128*)result.matrix_;
        this->print();
        other.print();
        result.print();
        //std::cout << size_ << std::endl;
        for(unsigned i = 0; i < size_; ++i) {
            //std::cout << i << std::endl;
            for(unsigned j = 0, size = size_ / 4; j < size; ++j) {
                m3[j + i*size_] = _mm_add_ps(m1[j+i*size_], m2[j + i*size_]);
                float check;
                _mm_store_ss(&check, m3[j + i*size_ ]);
                std::cout << check << std::endl;

            }
        }*/
        MatrixHand result(size_, 0);
        __m128 *m1 = (__m128*)matrix_;
        __m128 *m2 = (__m128*)other.matrix_;
        __m128 *m3 = (__m128*)result.matrix_;
        for(size_t i = 0; i < size_*size_/4; ++i) {
            m3[i] = _mm_add_ps(m1[i],m2[i]);
        }
        return result;
    }

    MatrixHand operator- (const MatrixHand &other) const {
        MatrixHand result(size_, 0);
        __m128 *m1 = (__m128*)matrix_;
        __m128 *m2 = (__m128*)other.matrix_;
        __m128 *m3 = (__m128*)result.matrix_;
        for(size_t i = 0; i < size_*size_/4; ++i) {
            m3[i] = _mm_sub_ps(m1[i],m2[i]);
        }

        return result;
    }

private:
    float * matrix_ = nullptr;
    unsigned size_ = 0;
};

#endif //_SIMD_MATRIXHAND_H_