#ifndef _SIMD_MATRIX_H_
#define _SIMD_MATRIX_H_

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>



class Matrix {
public:
    Matrix(unsigned size, float val = 1) : size_(size) {
        matrix_ = new float[size_*size_]();

        for(unsigned i = 0; i < size_; ++i) {
            set(i, i, val);
        }
    }

    Matrix(unsigned size, const std::vector<float> &val) : size_(size) {
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

    Matrix(const Matrix &other) : size_(other.size_) {
        matrix_ = new float[size_*size_]();

        memcpy(matrix_, other.matrix_, size_ * size_ * sizeof(float));
    }

    Matrix &operator= (const Matrix &other) {
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

    ~Matrix() {
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

    Matrix transpose() const {
        Matrix result(size_);
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
            float tmp = 0;
            for(unsigned j = 0; j < size_; ++j) {
                tmp += fabs(get(j, i));
            }
            if(max < tmp) {
                max = tmp;
            }
        }

        return max;
    }

    float secondConst() const {
        float max = 0;
        for(unsigned i = 0; i < size_; ++i) {
            float tmp = 0;
            for(unsigned j = 0; j < size_; ++j) {
                tmp += fabs(get(i, j));
            }
            if(max < tmp) {
                max = tmp;
            }
        }

        return max;
    }

    Matrix reverse(unsigned count) const {
        Matrix result(size_);
        Matrix I(size_);
        Matrix B = this->transpose() / (firstConst() * secondConst());
        Matrix R = I - B*(*this);
        const Matrix constR = R;

        for(unsigned i = 1; i < count; ++i) {
            result = result + R;
            R = R * constR;
        }

        return result * B;
    }

    Matrix operator/ (float d) const {
        Matrix result(size_);
        for(unsigned i = 0; i < size_; ++i) {
            for(unsigned j = 0; j < size_; ++j) {
                result.set(i, j, get(i, j) / d);
            }
        }

        return result;
    }

    Matrix operator* (float d) const {
        Matrix result(size_);
        for(unsigned i = 0; i < size_; ++i) {
            for(unsigned j = 0; j < size_; ++j) {
                result.set(i, j, get(i, j) * d);
            }
        }

        return result;
    }

    Matrix operator* (const Matrix &other) const {
        if(size_ != other.size_) {
            throw std::runtime_error("Matrix have different size");
        }
        Matrix result(size_);
        for(unsigned i = 0; i < size_; ++i) {
            for(unsigned j = 0; j < size_; ++j) {
                float tmp = 0.0f;
                for(unsigned k = 0; k < size_; ++k) {
                    tmp += get(i, k) * other.get(k, j);
                }
                result.set(i, j, tmp);
            }
        }

        return result;
    }

    Matrix operator+ (const Matrix &other) const {
        if(size_ != other.size_) {
            throw std::runtime_error("Matrix have different size");
        }
        Matrix result(size_);
        for(unsigned i = 0; i < size_; ++i) {
            for(unsigned j = 0; j < size_; ++j) {
                result.set(i, j, get(i, j) + other.get(i, j));
            }
        }

        return result;
    }

    Matrix operator- (const Matrix &other) const {
        if(size_ != other.size_) {
            throw std::runtime_error("Matrix have different size");
        }
        Matrix result(size_);
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

#endif //_SIMD_MATRIX_H_