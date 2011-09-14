#pragma once

#include <boost/shared_array.hpp>
#include "array_interface.h"
#include <cuda_runtime.h>

namespace ARD
{
  class CufftRealArray : public ArrayInterface<float>
  {
  private:
    typedef boost::shared_array<float> ArrayContent;
    typedef boost::shared_ptr<ArrayInterface<float> > ArrayInterfacePointer;
    
  public:
    explicit CufftRealArray(const Size& size);
    
    float* get() const { return content_.get(); };
    const Size size() const { return size_; };
    const float content(const Position& position) const { return content_[position.Serialize(size_)]; };
    void set_content(const Position& position, const float& input) { content_[position.Serialize(size_)] = input; };
    ArrayInterfacePointer Clone() const;
    
  private:
    ArrayContent Allocate(const Size& size) const;
    const Size size_;
    ArrayContent content_;
  };
}
