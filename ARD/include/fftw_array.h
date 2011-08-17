#ifndef FFTW_ARRAY_H
#define FFTW_ARRAY_H

#include <size.h>
#include <fftw3.h>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include "position.h"
#include "array_interface.h"

namespace ARD
{
  class FFTWArray : public ArrayInterface<double>
  {
  private:
    typedef boost::shared_array<double> FFTWArrayContent;
    typedef boost::shared_ptr<ArrayInterface<double> > ArrayInterfacePointer;
    
  public:
    FFTWArray() : size_(Size(0,0)) {};
    explicit FFTWArray(const Size& size);
    FFTWArray(const FFTWArray& original);
    ~FFTWArray() {};
    
    double* get() const { return content_.get(); };
    const Size size() const { return size_; };
    const double content(const Position& position) const;
    void set_content(const Position& position, const double& input);
    ArrayInterfacePointer Clone() const;

  private:
    FFTWArrayContent Allocate(const Size& size);
    const Size size_;
    FFTWArrayContent content_;
  };
  
  typedef boost::shared_ptr<FFTWArray> FFTWArrayPointer;
  
  inline const double FFTWArray::content(const Position& position) const {
    return content_[position.Serialize(size_)];
  }

  inline void FFTWArray::set_content(const Position& position, const double& input) {
    content_[position.Serialize(size_)] = input;
  }
}

#endif // FFTW_ARRAY_H
