#ifndef FFTW_ARRAY_H
#define FFTW_ARRAY_H

#include <size.h>
#include <fftw3.h>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include "position.h"
#include "precision.h"

namespace ARD
{
  typedef boost::shared_array<Precision> FFTWArrayContent;
  class FFTWArray;
  typedef boost::shared_ptr<FFTWArray> FFTWArrayPointer;

  class FFTWArray
  {
  public:
    FFTWArray() : size_(Size(0,0)) {};
    FFTWArray(const Size& size);
    FFTWArray(const FFTWArray& original);
    virtual ~FFTWArray() {};
    
    Precision* get() const;
    const Size size() const;
    const Precision content(const Position& position) const;
    void set_content(const Position& position, const Precision& input);
    void FillByZero();
    void FillBy(const Precision& input);
    FFTWArray& operator /= (const Precision scalar);

  private:
    const Size size_;
    FFTWArrayContent content_;
  };
};

#endif
