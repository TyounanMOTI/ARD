#pragma once

namespace ARD {
  template <class ArrayType>
  class ForceField {
  public:
    template <class ExtentList>
    explicit ForceField(const ExtentList& sizes) : _data(ArrayType(sizes)) {};

    typename ArrayType::reference operator[](typename ArrayType::index i) {
      return _data[i];
    }

    template <class IndexList>
    typename ArrayType::element& operator()(const IndexList& indices) {
      return _data(indices);
    }

    template <class IndexList>
    const typename ArrayType::element& operator()(const IndexList& indices) const {
      return _data(indices);
    }

  private:
    ArrayType _data;
  };
}
