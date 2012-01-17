#include <boost/multi_array.hpp>

namespace ARD {
  template <typename ValueType,
            std::size_t NumDims,
            typename Allocator = std::allocator<ValueType> >
    class MultiArray : public boost::multi_array<ValueType,
                                                 NumDims,
                                                 Allocator>
  {
    typedef boost::multi_array<ValueType, NumDims, Allocator> super_type;

  public:
    typedef typename super_type::size_type size_type;
    typedef boost::array<size_type, NumDims> size_list;

    MultiArray() : super_type() {}

    template <typename ExtentList>
    explicit MultiArray(const ExtentList& sizes) : super_type(sizes) {}

    size_list shape() const {
      return super_type::extent_list_;
    }
  };

  template <class ArrayType, class T>
  void Fill(ArrayType& target, const T& value) {
    std::fill(target.origin(), target.origin() + target.num_elements(), value);
  }
}
