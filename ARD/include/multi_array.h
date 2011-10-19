#include <boost/multi_array.hpp>

namespace ARD {
  template <typename T, std::size_t Dim, typename Allocator>
  void Fill(boost::multi_array<T, Dim, Allocator>& target, const T& value) {
    std::fill(target.origin(), target.origin() + target.num_elements(), value);
  }
}
