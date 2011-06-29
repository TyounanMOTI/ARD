#ifndef SOUND_FIELD_H
#define SOUND_FIELD_H

#include <fftw3.h>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>

typedef double* DoubleArray;
typedef boost::shared_ptr<fftw_plan_s> FFTWPlan;

class SoundField
{
public:
  SoundField(int width, int height);
  ~SoundField();
  DoubleArray Update();

private:
  void SwapSpectrumBuffers();
  void FillByZero(DoubleArray target);
  int PositionToIndex(int x, int y);
  void SoundField::Normalize(DoubleArray field, double max);

  long step_;
  static const double dt_;
  static const double c_;
  DoubleArray pressure_spectrum_previous_, pressure_spectrum_now_, pressure_spectrum_next_;
  DoubleArray force_field_;
  FFTWPlan force_field_dct_plan_, pressure_spectrum_idct_plan_;
  int width_, height_;
};

#endif // SOUND_FIELD_H