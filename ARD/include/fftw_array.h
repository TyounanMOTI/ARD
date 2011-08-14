#ifndef FFTW_ARRAY_H
#define FFTW_ARRAY_H

#include <size.h>
#include <fftw3.h>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include "position.h"
#include "precision.h"
#include "array_interface.h"

namespace ARD
{
  class FFTWArray;
  typedef boost::shared_array<Precision> FFTWArrayContent;
  typedef boost::shared_ptr<FFTWArray> FFTWArrayPointer;

  class FFTWArray : public ArrayInterface
  {
  public:
    FFTWArray() : size_(Size(0,0)) {};
    FFTWArray(const Size& size);
    FFTWArray(const FFTWArray& original);
    virtual ~FFTWArray() {};
    
    Precision* get() const { return content_.get(); };
    const Size size() const { return size_; };
    const Precision content(const Position& position) const;
    void set_content(const Position& position, const Precision input);
    ArrayInterfacePointer Clone() const;
    FFTWArray& operator /= (const Precision scalar);

  private:
    const Size size_;
    FFTWArrayContent content_;
  };
  
  inline const Precision FFTWArray::content(const Position& position) const {
    return content_[position.Serialize(size_)];
  }

  inline void FFTWArray::set_content(const Position& position, const Precision input) {
    content_[position.Serialize(size_)] = input;
  }
}


#endif // FFTW_ARRAY_H
