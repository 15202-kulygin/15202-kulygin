#ifndef _SIMD_MATRIXHAND_H_
#define _SIMD_MATRIXHAND_H_


#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include "xmmintrin.h"

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
        __m128 *data = (__m128*)result.matrix_;
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
        __m128 *m2 = (__m128*)other.matrix_;
        __m128 tmp;
        for(unsigned i = 0; i < size_; ++i) {
            for(unsigned j = 0; j < size_; ++j) {
                tmp = _mm_setzero_ps();
                for(unsigned k = 0, size = size_ / 4; k < size; ++k) {
                    tmp = _mm_add_ps(tmp, _mm_mul_ps(m1[k], m2[k]));
                }
                float sum;
                _mm_store_ss(&sum, tmp);
                result.set(i, j, sum);
            }
        }

        return result;
    }

    MatrixHand operator+ (const MatrixHand &other) const {
        if(size_ != other.size_) {
            throw std::runtime_error("MatrixHand have different size");
        }
        MatrixHand result(size_);
        __m128 *m1 = (__m128*)matrix_;
        __m128 *m2 = (__m128*)other.matrix_;
        __m128 *m3 = (__m128*)result.matrix_;
        for(unsigned i = 0; i < size_; ++i) {
            for(unsigned j = 0, size = size_ / 4; j < size; ++j) {
                m3[j] = _mm_add_ps(m1[j], m2[j]);
            }
        }

        return result;
    }

    MatrixHand operator- (const MatrixHand &other) const {
        if(size_ != other.size_) {
            throw std::runtime_error("MatrixHand have different size");
        }
        MatrixHand result(size_);
        __m128 *m1 = (__m128*)matrix_;
        __m128 *m2 = (__m128*)other.matrix_;
        __m128 *m3 = (__m128*)result.matrix_;
        for(unsigned i = 0; i < size_; ++i) {
            for(unsigned j = 0, size = size_ / 4; j < size; ++j) {
                m3[j] = _mm_sub_ps(m1[j], m2[j]);
            }
        }

        return result;
    }

private:
    float *matrix_ = nullptr;
    unsigned size_ = 0;
};

#endif //_SIMD_MATRIXHAND_H_
