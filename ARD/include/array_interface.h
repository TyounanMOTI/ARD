#ifndef ARRAY_INTERFACE_H
#define ARRAY_INTERFACE_H

#include <size.h>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include "position.h"
#include "precision.h"

namespace ARD
{
  class ArrayInterface;
  typedef boost::shared_ptr<ArrayInterface> ArrayInterfacePointer;

  class ArrayInterface
  {
  public:
    virtual ~ArrayInterface() {};
    
    virtual Precision_t* get() const = 0;
    virtual const Size size() const = 0;
    virtual const Precision_t content(const Position& position) const = 0;
    virtual void set_content(const Position& position, const Precision_t input) = 0;
    virtual ArrayInterfacePointer Clone() const = 0;

    virtual void FillByZero();
    virtual void FillBy(const Precision_t& input);
    virtual ArrayInterface& operator /= (const Precision_t scalar);
  };
}

#endif // ARRAY_INTERFACE_H
