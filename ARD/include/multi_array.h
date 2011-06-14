#ifndef MULTI_ARRAY_H
#define MULTI_ARRAY_H

#include <size.h>
#include <fftw3.h>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include "position.h"
#include "pressure.h"

namespace ARD
{
  typedef boost::shared_array<double> MultiArrayContent;
  class MultiArray
  {
  public:
    MultiArray() : size_(Size(0,0)) {};
    MultiArray(const Size& size);
    MultiArray(const Size& size, const MultiArrayContent& content) : size_(size), content_(content) {};
    virtual ~MultiArray() {};
    
    const Size size() const;
    const Pressure content(const Position& position) const;
    void set_content(const Position& position, const Pressure& input);

  private:
    const Size size_;
    MultiArrayContent content_;
  };
  
  typedef boost::shared_ptr<MultiArray> MultiArrayPointer;
  
  const size_t MultiArrayIndexFromPosition(const Position& position, const Size& size);
};

#endif
