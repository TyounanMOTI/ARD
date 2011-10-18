#pragma once

namespace ARD {
  template <class ArrayType>
  class ForceField : public ArrayType {
  public:
    template <class ExtentList>
    explicit ForceField(const ExtentList& sizes) : ArrayType(sizes) {};
  };
}
