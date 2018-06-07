#ifndef NEWTONIAN_PHYSICS_SANDBOX_TENSOR_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_TENSOR_HPP

#include <libgeodecomp.h>

using namespace LibGeoDecomp;

template<int DIM1, int DIM2>
class Matrix;

template<>
class Matrix<3, 3>
{
public:
    static const int DIM1 = 3;
    static const int DIM2 = 3;

    Matrix() = default;

    template<template<int> class COORD>
    Matrix(const COORD<3>& diagonal){
        for (int i = 0; i < DIM1; ++i)
            for (int j = 0; j < DIM2; ++j)
                dims[i][j] = (i == j) ? diagonal[i] : 0;
    }

    Matrix(double scalar)
    {
        for (int i = 0; i < DIM1; ++i)
            for (int j = 0; j < DIM2; ++j)
                dims[i][j] = scalar;
    }

    static inline
    Matrix<3, 3> diagonal(double scalar)
    {
        Matrix<3, 3> ret;
        for (int i = 0; i < DIM1; ++i)
            for (int j = 0; j < DIM2; ++j)
                ret.dims[i][j] = static_cast<double>(i == j) * scalar;
    }

    inline
    Matrix<3, 3> &operator=(const Matrix<3, 3> &other)
    {
        for (int i = 0; i < DIM1; ++i)
            for (int j = 0; j < DIM2; ++j)
                dims[i][j] = other.dims[i][j];
    }

    inline
    double *operator[](const int index)
    {
        return dims[index];
    }

    inline
    const double *operator[](const int index) const
    {
        return dims[index];
    }

    template<template<int> class COORD>
    inline
    FloatCoord<3> operator*(const COORD<3> &other)
    {
        FloatCoord<3> ret = FloatCoord<3>(0);
        for (int i = 0; i < DIM1; i++)
            for (int j = 0; j < DIM2; i++)
                ret[i] += dims[i][j] * other[j];
    }

    inline
    Matrix<3, 3> &operator=(const double &scalar)
    {
        for (int i = 0; i < DIM1; ++i)
            for (int j = 0; j < DIM2; ++j)
                dims[i][j] = scalar;
    }

    inline
    Matrix<3, 3> operator*(const Matrix<3, 3> &other) const
    {
        Matrix<3, 3> ret = 0.0;

        for (int i = 0; i < DIM1; ++i)
            for (int k = 0; k < DIM1; ++k)
                for (int j = 0; j < DIM2; ++j)
                    ret[i][j] += dims[i][k] * other[k][j];
    }

    inline
    Matrix<3, 3> &operator*=(const Matrix<3, 3> &other)
    {
        Matrix<3, 3> ret = 0.0;
        *this = 0.0;

        for (int i = 0; i < DIM1; ++i)
            for (int k = 0; k < DIM1; ++k)
                for (int j = 0; j < DIM2; ++j)
                    ret[i][j] += dims[i][k] * other[k][j];

        *this = ret;
        return *this;
    }

    inline
    Matrix<3, 3> operator*(const double scalar) const
    {
        Matrix<3, 3> ret = 0.0;

        for (int i = 0; i < DIM1; ++i)
            for (int j = 0; j < DIM2; ++j)
                ret[i][j] = dims[i][j] * scalar;

        return ret;
    }

    inline
    Matrix<3, 3> &operator*=(const double scalar)
    {
        for (int i = 0; i < DIM1; ++i)
            for (int j = 0; j < DIM2; ++j)
                dims[i][j] *= scalar;

        return *this;
    }

    inline
    Matrix<3, 3> operator+(const Matrix<3, 3> &other) const
    {
        Matrix<3, 3> ret;

        for (int i = 0; i < DIM1; ++i)
            for (int j = 0; j < DIM2; ++j)
                ret[i][j] = dims[i][j] + other[i][j];
    }

    inline
    Matrix<3, 3> &operator+=(const Matrix<3, 3> &other)
    {
        for (int i = 0; i < DIM1; ++i)
            for (int j = 0; j < DIM2; ++j)
                dims[i][j] += other[i][j];
    }

    virtual
    Matrix<3, 3> &transpose(void)
    {
        for (int i = 0; i < DIM1; ++i)
            for (int j = 0; j < i; ++j)
                swap(dims[i][j], dims[j][i]);

        return *this;
    }

    virtual
    Matrix<3, 3> getTranspose(void)
    {
        Matrix<3, 3> ret;

        for (int i = 0; i < DIM1; ++i) {
            for (int j = 0; j < i; ++j) {
                ret[i][j] = dims[j][i];
                ret[j][i] = dims[i][j];
            }
        }

        return ret;
    }

    double determinant(void) const {
        return
            dims[0][0] * dims[1][1] * dims[2][2] +
            dims[0][1] * dims[1][2] * dims[2][0] +
            dims[0][2] * dims[1][0] * dims[2][1] -
            dims[0][2] * dims[1][1] * dims[2][0] -
            dims[0][1] * dims[1][0] * dims[2][2] -
            dims[0][0] * dims[1][2] * dims[2][1];
    }

    // FIXME add exception for non-invertible matrix
    // TODO not such hardcoded
    Matrix<3, 3> &inverse(void)
    {
        Matrix<3, 3> ret = *this;

        double det = ret.determinant();

        auto matrixMinor = [ret](int i, int j, int k, int l) -> double {
            return ret[i][k] * ret[j][l] - ret[i][l] * ret[j][k];
        };

        dims[0][0] = matrixMinor(1, 2, 1, 2);
        dims[0][1] = matrixMinor(1, 2, 0, 2);
        dims[0][2] = matrixMinor(1, 2, 0, 1);
        dims[1][0] = matrixMinor(0, 2, 1, 2);
        dims[1][1] = matrixMinor(0, 2, 0, 2);
        dims[1][2] = matrixMinor(0, 2, 0, 1);
        dims[2][0] = matrixMinor(0, 1, 1, 2);
        dims[2][1] = matrixMinor(0, 1, 0, 2);
        dims[2][2] = matrixMinor(0, 1, 0, 1);

        for (int i = 0; i < DIM1; ++i)
            for (int j = 0; j < DIM2; ++j) {
                dims[i][j] /= det;
            }
    }

    Matrix<3, 3> getInversed(void)
    {
        Matrix <3, 3> ret;
        return ret.inverse();
    }

protected:
    double data[9];
    double *dims[3] = {data, data + 3, data + 6};

    inline void swap(double &v1, double &v2)
    {
        double buf = v1;
        v1 = v2;
        v2 = buf;
    }
};

/**
 *
 * AngularVTensor actually useful when we have simulations with angular
 * velocity. This is standard presentation of it a.k.a.
 * angular velocity tensor.
 *
 * @tparam DIM dimensions
 */

template<int DIM1, int DIM2>
class AngularVTensor;

template<>
class AngularVTensor<3, 3>: public Matrix<3, 3>
{
public:

    AngularVTensor() : Matrix<3, 3>() {};

    template<template<int> class COORD>
    explicit AngularVTensor(const COORD<3> &diagonal) : Matrix<3, 3>(diagonal)
    {
    }

    AngularVTensor(const Matrix<3, 3>& matrix)
    {
        for (int i = 0; i < DIM1; ++i)
            for (int j = 0; j < DIM2; ++j)
                dims[i][j] = matrix[i][j];
    }

    explicit AngularVTensor(double scalar)
    {
        for (int i = 0; i < DIM1; i++)
            dims[i][i] = 0;

        dims[0][1] = -scalar;
        dims[1][0] = scalar;

        dims[0][2] = scalar;
        dims[2][0] = -scalar;

        dims[1][2] = -scalar;
        dims[2][1] = scalar;
    }

    template<template<int> class COORD>
    explicit AngularVTensor(const COORD<3> &coord)
    {
        for (int i = 0; i < DIM1; i++)
            dims[i][i] = 0;

        dims[0][1] = -coord[2];
        dims[1][0] = coord[2];

        dims[0][2] = coord[1];
        dims[2][0] = -coord[1];

        dims[1][2] = -coord[0];
        dims[2][1] = coord[0];
    }

    template<template<int> class COORD>
    inline
    AngularVTensor<3, 3> &operator=(const COORD<3> &coord)
    {
        for (int i = 0; i < DIM1; i++)
            dims[i][i] = 0;

        dims[0][1] = -coord[2];
        dims[1][0] = coord[2];

        dims[0][2] = coord[1];
        dims[2][0] = -coord[1];

        dims[1][2] = -coord[0];
        dims[2][1] = coord[0];
    }

    inline
    FloatCoord<3> getFloatCoord(void)
    {
        return FloatCoord<3>(dims[2][1], dims[0][2], dims[1][0]);
    }

    Matrix<3, 3> &transpose(void) override
    {

        dims[1][2] *= -1;
        dims[2][1] *= -1;

        dims[2][0] *= -1;
        dims[0][2] *= -1;

        dims[1][0] *= -1;
        dims[0][1] *= -1;

        return *this;
    }

    Matrix<3, 3> getTranspose(void) override
    {
        return AngularVTensor<3, 3>(FloatCoord<3>(dims[1][2], dims[2][0], dims[0][1]));
    }

};

template<int DIM1, int DIM2>
class InertiaTensor;

template<>
class InertiaTensor<3, 3>: public Matrix<3, 3>
{
public:

    InertiaTensor() = default;

    InertiaTensor(const Matrix<3, 3>& matrix) {
        for (int i = 0; i < DIM1; ++i) {
            for (int j = 0; j < DIM2; ++j) {
                dims[i][j] = matrix[i][j];
            }
        }
    }

    explicit InertiaTensor(double scalar) : Matrix<3, 3>(scalar)
    {
    }

    template<template<int> class COORD>
    explicit InertiaTensor(const COORD<3> &diagonal) : Matrix<3, 3>(diagonal)
    {
    }

    template<template<int> class COORD>
    inline
    InertiaTensor<3, 3> &operator=(const COORD<3> &coord)
    {
//TODO
    }

    inline
    FloatCoord<3> getFloatCoord(void)
    {
        return FloatCoord<3>(dims[2][1], dims[0][2], dims[1][0]);
    }

    Matrix<3, 3> &transpose(void) override
    {
        return *this;
    }

    Matrix<3, 3> getTranspose(void) override
    {
        return *this;
    }

};
#endif //!NEWTONIAN_PHYSICS_SANDBOX_TENSOR_HPP
