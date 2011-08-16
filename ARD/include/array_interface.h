#ifndef ARRAY_INTERFACE_H
#define ARRAY_INTERFACE_H

#include <size.h>
#include <boost/shared_ptr.hpp>
#include "position.h"

namespace ARD
{
  template<class Precision>
  class ArrayInterface
  {
  private:
    typedef boost::shared_ptr<ArrayInterface<Precision> > ArrayInterfacePointer;
  public:
    virtual ~ArrayInterface() {};
    
    virtual Precision* get() const = 0;
    virtual const Size size() const = 0;
    virtual const Precision content(const Position& position) const = 0;
    virtual void set_content(const Position& position, const Precision& input) = 0;
    virtual ArrayInterfacePointer Clone() const = 0;

    virtual void FillByZero();
    virtual void FillBy(const Precision& input);
    virtual ArrayInterface<Precision>& operator /= (const Precision& scalar);
  };

  template <class Precision>
  void ArrayInterface<Precision>::FillByZero() {
    FillBy(Precision(0)); 
  }

  template <class Precision>
  void ArrayInterface<Precision>::FillBy(const Precision& input) {
    for (int y = 0; y < size().height(); y++) {
      for (int x = 0; x < size().width(); x++) {
        set_content(Position(x,y), input);
      }
    }
  }

  template <class Precision>
  ArrayInterface<Precision>& ArrayInterface<Precision>::operator /= (const Precision& scalar) {
    for (int y = 0; y < size().height(); y++) {
      for (int x = 0; x < size().width(); x++) {
        set_content(Position(x,y), content(Position(x,y))/scalar);
      }
    }
    return *this;
  }
}

#endif // ARRAY_INTERFACE_H
