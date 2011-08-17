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
  template <class Precision>
  class FFTWArray : public ArrayInterface<Precision>
  {
  private:
    typedef boost::shared_array<Precision> FFTWArrayContent;
    typedef boost::shared_ptr<ArrayInterface<Precision> > ArrayInterfacePointer;
    
  public:
    FFTWArray() : size_(Size(0,0)) {};
    explicit FFTWArray(const Size& size);
    FFTWArray(const FFTWArray& original);
    ~FFTWArray() {};
    
    Precision* get() const { return content_.get(); };
    const Size size() const { return size_; };
    const Precision content(const Position& position) const;
    void set_content(const Position& position, const Precision& input);
    ArrayInterfacePointer Clone() const;

  private:
    FFTWArrayContent Allocate(const Size& size);
    
    const Size size_;
    FFTWArrayContent content_;
  };
  
  template <class Precision>
  FFTWArray<Precision>::FFTWArray(const Size& size) : size_(size) {
    content_ = Allocate(size);
    ArrayInterface<Precision>::FillByZero();
  }
  
  template <class Precision>
  FFTWArray<Precision>::FFTWArray(const FFTWArray& original) : size_(original.size_) {
    content_ = Allocate(original.size_);
    memcpy(content_.get(), original.content_.get(), sizeof(Precision)*original.size_.Length());
  }
  
  template <class Precision>
  inline const Precision FFTWArray<Precision>::content(const Position& position) const {
    return content_[position.Serialize(size_)];
  }
  
  template <class Precision>
  inline void FFTWArray<Precision>::set_content(const Position& position, const Precision& input) {
    content_[position.Serialize(size_)] = input;
  }
  
  template <class Precision>
  typename FFTWArray<Precision>::ArrayInterfacePointer FFTWArray<Precision>::Clone() const {
    return ArrayInterfacePointer(new FFTWArray(*this));
  }
  
  template <class Precision>
  typename FFTWArray<Precision>::FFTWArrayContent FFTWArray<Precision>::Allocate(const Size& size) {
    return FFTWArrayContent(static_cast<Precision*>(malloc(sizeof(Precision)*size.Length())),
                            free);
  }
  
  template <>
  FFTWArray<double>::FFTWArrayContent FFTWArray<double>::Allocate(const Size& size);
}

#endif // FFTW_ARRAY_H
