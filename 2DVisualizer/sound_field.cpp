#include "sound_field.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>

const double SoundField::dt_ = 0.001;
const double SoundField::c_ = 340.0;

DoubleArray fftw_malloc_double_array(size_t length) {
  return static_cast<double*>(fftw_malloc(sizeof(double)*length));
}

SoundField::SoundField(int width, int height) : width_(width), height_(height), step_(0) {
  force_field_ = fftw_malloc_double_array(width*height);
  pressure_spectrum_previous_ = fftw_malloc_double_array(width*height);
  pressure_spectrum_now_ = fftw_malloc_double_array(width*height);
  pressure_spectrum_next_ = fftw_malloc_double_array(width*height);
  FillByZero(pressure_spectrum_previous_);
  FillByZero(pressure_spectrum_now_);

  force_field_dct_plan_ = FFTWPlan(fftw_plan_r2r_2d(width, height, force_field_, force_field_, FFTW_REDFT10, FFTW_REDFT10, FFTW_ESTIMATE), fftw_destroy_plan);
  pressure_spectrum_idct_plan_ = FFTWPlan(fftw_plan_r2r_2d(width, height, pressure_spectrum_next_, pressure_spectrum_next_, FFTW_REDFT01, FFTW_REDFT01, FFTW_ESTIMATE), fftw_destroy_plan);
}

SoundField::~SoundField() {
  fftw_free(force_field_);
  fftw_free(pressure_spectrum_previous_);
  fftw_free(pressure_spectrum_now_);
  fftw_free(pressure_spectrum_next_);
}

DoubleArray SoundField::Update() {
  FillByZero(force_field_);

  if (step_ == 0) { // emit source only this time
    force_field_[PositionToIndex(width_/2+5, height_/2)] = 1000.0;
    fftw_execute(force_field_dct_plan_.get());
  }
  DoubleArray force_spectrum = force_field_;

  double omega;
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      omega = c_*M_PI*sqrt((double)x*x/((width_-1)*(width_-1)) + ((double)y*y/((height_-1)*(height_-1))));
      if (x == 0 && y ==0) {
        omega = 1.0;
      }
      pressure_spectrum_next_[PositionToIndex(x,y)] = 2.0*pressure_spectrum_now_[PositionToIndex(x,y)]*cos(omega*dt_)
        - pressure_spectrum_previous_[PositionToIndex(x,y)]
        + 2.0*force_spectrum[PositionToIndex(x,y)]/(omega*omega)*(1.0-cos(omega*dt_));
    }
  }
  pressure_spectrum_next_[0] = 0;

  SwapSpectrumBuffers();

  fftw_execute(pressure_spectrum_idct_plan_.get());
  Normalize(pressure_spectrum_next_, width_*height_*4);
    
  step_++;
  printf("%d\n", step_);

  return pressure_spectrum_next_;
}

void SoundField::Normalize(DoubleArray field, double max) {
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      field[PositionToIndex(x,y)] /= max;
    }
  }
}

void SoundField::SwapSpectrumBuffers() {
  memmove(pressure_spectrum_previous_, pressure_spectrum_now_, sizeof(double)*width_*height_);
  memmove(pressure_spectrum_now_, pressure_spectrum_next_, sizeof(double)*width_*height_);
}

void SoundField::FillByZero(DoubleArray target) {
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      target[PositionToIndex(x,y)] = 0;
    }
  }
}

int SoundField::PositionToIndex(int x, int y) {
  return y*width_ + x;
}
