#pragma once
#include "pressure_spectrum.h"
#include <cmath>

namespace ARD {
  template <class ArrayType>
  class UpdateFormula
  {};

  template <>
  class UpdateFormula<FFTWFloat2DArray>
  {
  public:
    UpdateFormula(FFTWFloat2DArray& output, float dt)
      :output_(output),
       coeff_current_pressure_(output.shape()),
       coeff_force_(output.shape()),
       previous_(new PressureSpectrum<FFTWFloat2DArray>(output)),
       current_(new PressureSpectrum<FFTWFloat2DArray>(output)),
       next_(new PressureSpectrum<FFTWFloat2DArray>(output)),
       width_(output.shape()[1]),
       height_(output.shape()[0]),
       dt_(dt)
    {
      FFTWFloat2DArray square_omega(output.shape());
      FFTWFloat2DArray temp_cos(output.shape());
      InitSquareOmega(square_omega);
      InitCos(square_omega, temp_cos);
      InitCoeffCurrentPressure(temp_cos, coeff_current_pressure_);
      InitCoeffForce(temp_cos, square_omega, coeff_force_);
    }

    void Execute(const FFTWFloat2DArray& force_spectrum) {
      size_t x, y;
      for (y = 0; y < height_; y++) {
	for (x = 0; x < width_; x++) {
	  next_->data_[y][x] = coeff_current_pressure_[y][x]*current_->data_[y][x] - previous_->data_[y][x] + coeff_force_[y][x]*force_spectrum[y][x];
	}
      }
      next_->data_[0][0] = 0.0f; // coeff_force_[0][0] is NaN or Inf

      next_->InverseDCT();

      // time shift
      next_.swap(current_);
      next_.swap(previous_);
    }

    void InitSquareOmega(FFTWFloat2DArray& output) {
      static const float c = 340.0f; // speed of sound

      size_t x, y;
      for (y = 0; y < height_; y++) {
	for (x = 0; x < width_; x++) {
	  output[y][x] = pow(c, 2) * pow(M_PI, 2) * (pow(x, 2)/pow(width_-1, 2) + pow(y, 2)/pow(height_-1, 2));
	}
      }
    }

    void InitCos(const FFTWFloat2DArray& square_omega, FFTWFloat2DArray& output) {
      size_t x, y;
      for (y = 0; y < height_; y++) {
	for (x = 0; x < width_; x++) {
	  output[y][x] = cos(sqrt(square_omega[y][x])*dt_);
	}
      }
    }

    void InitCoeffCurrentPressure(const FFTWFloat2DArray& temp_cos, FFTWFloat2DArray& output) {
      size_t x, y;
      for (y = 0; y < height_; y++) {
	for (x = 0; x < width_; x++) {
	  output[y][x] = 2.0f * temp_cos[y][x];
	}
      }
    }

    void InitCoeffForce(const FFTWFloat2DArray& temp_cos, const FFTWFloat2DArray& square_omega, FFTWFloat2DArray& output) {
      size_t x, y;
      for (y = 0; y < height_; y++) {
	for (x = 0; x < width_; x++) {
	  output[y][x] = 2.0f / square_omega[y][x] * (1.0f - temp_cos[y][x]);
	}
      }
    }

    //  private:
    FFTWFloat2DArray& output_;
    FFTWFloat2DArray coeff_current_pressure_, coeff_force_;
    std::unique_ptr<PressureSpectrum<FFTWFloat2DArray> > previous_, current_, next_;
    size_t width_, height_;
    float dt_;
  };
}
