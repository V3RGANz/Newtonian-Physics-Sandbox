#ifndef NEWTONIAN_PHYSICS_SANDBOX_TENSOR_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_TENSOR_HPP

#include <libgeodecomp.h>

using namespace LibGeoDecomp;

template <int DIM>
class Matrix;

template <>
class Matrix<3> {
public:
  static const int DIM = 3;

  Matrix() = default;

  // constructor below is deprecated because of main diagonal should be zero
//  AngularVTensor(double a11, double a12, double a13,
//         double a21, double a22, double a23,
//         double a31, double a32, double a33) : {
//
//    dims[1][1] = a11; dims[1][2] = a12; dims[1][3] = a13;
//    dims[2][1] = a21; dims[2][2] = a22; dims[2][3] = a23;
//    dims[3][1] = a31; dims[3][2] = a32; dims[3][3] = a33;
//
//  }

  virtual Matrix(double scalar){
    for (int i = 0; i < DIM; ++i) {
      for (int j = 0; j < DIM; ++j) {
        dims[i][j] = scalar;
      }
    }
  }

  static inline
  Matrix<3> diagonal(double scalar){
    Matrix<3> ret;
    for (int i = 0; i < DIM; ++i) {
      for (int j = 0; j < DIM; ++j) {
        ret.dims[i][j] = static_cast<double>(i == j) * scalar;
      }
    }
  }

  template<template<int> class OTHER_MATRIX>
  inline
  Matrix<3>& operator=(OTHER_MATRIX& other){
    for (int i = 0; i < DIM; ++i) {
      for (int j = 0; j < DIM; ++j) {
        dims[i][j] = other.dims[i][j];
      }
    }
  }

  inline
  double* operator[](const int index){
    return dims[index];
  }

  inline
  const double* operator[](const int index) const {
    return dims[index];
  }

  template<template<int> class COORD>
  inline
  FloatCoord<3> operator*(const COORD<3>& other) {
    FloatCoord<3> ret = 0;
    for (int i = 0; i < DIM; i++) {
      for (int j = 0; j < DIM; i++) {
        ret[i] += dims[i][j]*other[j];
      }
    }
  }

  inline
  Matrix<3>& operator=(const double& scalar){
    for (int i = 0; i < DIM; ++i)
      for (int j = 0; j < DIM; ++j)
        dims[i][j] = scalar;
  }

  template<template<int> class OTHER_MATRIX>
  inline
  Matrix<3> operator*(const OTHER_MATRIX<3>& other) const {
    Matrix<3> ret = 0.0;

    for (int i = 0; i < DIM; ++i)
      for (int k = 0; k < DIM; ++k)
        for (int j = 0; j < DIM; ++j)
          ret[i][j] += dims[i][k] * other[k][j];
  }


  template<template<int> class OTHER_MATRIX>
  inline
  Matrix<3>& operator*=(const OTHER_MATRIX<3>& other) {
    Matrix<3> ret = 0.0;
    *this = 0.0;

    for (int i = 0; i < DIM; ++i)
      for (int k = 0; k < DIM; ++k)
        for (int j = 0; j < DIM; ++j)
          ret[i][j] += dims[i][k] * other[k][j];

    *this = ret;
    return *this;
  }


  virtual
  Matrix<3>& transpose(void) {
    for (int i = 0; i < DIM; ++i) {
      for (int j = 0; j < i; ++j) {
        swap(dims[i][j], dims[j][i]);
      }
    }

    return *this;
  }

  virtual
  Matrix<3> getTranspose(void){
    Matrix<3> ret;

    for (int i = 0; i < DIM; ++i) {
      for (int j = 0; j < i; ++j) {
        ret[i][j] = dims[j][i];
        ret[j][i] = dims[i][j];
      }
    }

    return ret;
  }

  Matrix<3>& inverse(void){
    //TODO
    return *this;
  }

protected:
  double data[9];
  double* dims[3] = {data, data + 3, data + 6};

  inline void swap(double& v1, double& v2){
    double buf = v1;
    v1 = v2;
    v2 = buf;
  }
};

/**
 *
 * InertiaTensor actually useful when we have simulations with angular
 * velocity. This is standard presentation of it a.k.a.
 * angular velocity tensor.
 *
 * @tparam DIM dimensions
 */

template <int DIM>
class AngularVTensor;

template <>
class AngularVTensor<3> : public Matrix<3>{
public:

  AngularVTensor() = default;

  // constructor below is deprecated because of main diagonal should be zero
//  AngularVTensor(double a11, double a12, double a13,
//         double a21, double a22, double a23,
//         double a31, double a32, double a33) : {
//
//    dims[1][1] = a11; dims[1][2] = a12; dims[1][3] = a13;
//    dims[2][1] = a21; dims[2][2] = a22; dims[2][3] = a23;
//    dims[3][1] = a31; dims[3][2] = a32; dims[3][3] = a33;
//
//  }

  explicit AngularVTensor(double scalar){
    for (int i = 0; i < DIM; i++)
      dims[i][i] = 0;

    dims[0][1] = -scalar;
    dims[1][0] = scalar;

    dims[0][2] = scalar;
    dims[2][0] = -scalar;

    dims[1][2] = -scalar;
    dims[2][1] = scalar;
  }

  template<template<int> class COORD>
  explicit AngularVTensor(const COORD<3>& coord) {
    for (int i = 0; i < DIM; i++)
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
  AngularVTensor<3>& operator=(const COORD<3>& floatCoord) {
    for (int i = 0; i < DIM; i++)
      dims[i][i] = 0;

    dims[0][1] = -floatCoord[2];
    dims[1][0] = floatCoord[2];

    dims[0][2] = floatCoord[1];
    dims[2][0] = -floatCoord[1];

    dims[1][2] = -floatCoord[0];
    dims[2][1] = floatCoord[0];
  }

  inline
  FloatCoord<3> getFloatCoord(void){
    return FloatCoord<3>(dims[2][1], dims[0][2], dims[1][0]);
  }

  Matrix<3>& transpose(void) override {

    dims[1][2] *= -1;
    dims[2][1] *= -1;

    dims[2][0] *= -1;
    dims[0][2] *= -1;

    dims[1][0] *= -1;
    dims[0][1] *= -1;

    return *this;
  }

  Matrix<3> getTranspose(void) override {
    return AngularVTensor<3>(FloatCoord<3>(dims[1][2], dims[2][0], dims[0][1]));
  }

};

#endif //!NEWTONIAN_PHYSICS_SANDBOX_TENSOR_HPP
