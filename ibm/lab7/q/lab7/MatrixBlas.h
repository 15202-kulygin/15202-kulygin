#ifndef _SIMD_MATRIXBLAS_H_
#define _SIMD_MATRIXBLAS_H_

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <cblas.h>
#include <iomanip>


class MatrixBlas {
public:
    MatrixBlas(unsigned size, float val = 1) : size_(size) {
        matrix_ = new float[size_*size_]();

        for(unsigned i = 0; i < size_; ++i) {
            set(i, i, val);
        }
    }

    MatrixBlas(unsigned size, const std::vector<float> &val) : size_(size) {
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

    MatrixBlas(const MatrixBlas &other) : size_(other.size_) {
        matrix_ = new float[size_*size_]();

        memcpy(matrix_, other.matrix_, size_ * size_ * sizeof(float));
    }

    MatrixBlas &operator= (const MatrixBlas &other) {
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

    ~MatrixBlas() {
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




    MatrixBlas transpose() const {
        MatrixBlas result(size_);
        for(unsigned i = 0; i < size_; ++i) {
            for(unsigned j = 0; j < size_; ++j) {
                result.set(j, i, get(i, j));
            }
        }

        return result;
    }

    float firstConst() const {
        float max = 0;
        for(unsigned i = 0; i < size_; ++i) {
            float tmp = cblas_sasum(size_, matrix_ + i, size_);
            if(max < tmp) {
                max = tmp;
            }
        }

        return max;
    }

    float secondConst() const {
        float max = 0;
        for(unsigned i = 0; i < size_; ++i) {
            float tmp = cblas_sasum(size_, matrix_ + i * size_, 1);
            if(max < tmp) {
                max = tmp;
            }
        }

        return max;
    }

    MatrixBlas reverse(unsigned count) const {
        MatrixBlas result(size_);
        MatrixBlas I(size_);
        MatrixBlas B = this->transpose() / (firstConst() * secondConst());
        MatrixBlas R = I - B*(*this);
        const MatrixBlas constR = R;

        for(unsigned i = 1; i < count; ++i) {
            result = result + R;
            R = R * constR;
        }

        return result * B;
    }

    MatrixBlas operator/ (float d) const {
        return (*this) * (1/d);
    }

    MatrixBlas operator* (float d) const {
        MatrixBlas result = *this;
        cblas_sscal(size_*size_, d, result.matrix_, 1);
        return result;
    }

    MatrixBlas operator* (const MatrixBlas &other) const {
        if(size_ != other.size_) {
            throw std::runtime_error("MatrixBlas have different size");
        }
        MatrixBlas result(size_);
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, size_, size_, size_, 1, matrix_, size_, other.matrix_,
                    size_, 0.f, result.matrix_, size_);

        return result;
    }

    MatrixBlas operator+ (const MatrixBlas &other) const {
        if(size_ != other.size_) {
            throw std::runtime_error("MatrixBlas have different size");
        }
        MatrixBlas result(size_);
        for(unsigned i = 0; i < size_; ++i) {
            for(unsigned j = 0; j < size_; ++j) {
                result.set(i, j, get(i, j) + other.get(i, j));
            }
        }

        return result;
    }

    MatrixBlas operator- (const MatrixBlas &other) const {
        if(size_ != other.size_) {
            throw std::runtime_error("MatrixBlas have different size");
        }
        MatrixBlas result(size_);
        for(unsigned i = 0; i < size_; ++i) {
            for(unsigned j = 0; j < size_; ++j) {
                result.set(i, j, get(i, j) - other.get(i, j));
            }
        }

        return result;
    }

private:
    float *matrix_ = nullptr;
    unsigned size_ = 0;
};

#endif //_SIMD_MATRIXBLAS_H_
