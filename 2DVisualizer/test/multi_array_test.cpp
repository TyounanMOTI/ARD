#include <gtest/gtest.h>
#include <boost/multi_array.hpp>
#include <SDL/SDL.h>

TEST(MultiArrayTest, Data) {
  typedef boost::multi_array<Uint32, 2> Array;
  Array subject( boost::extents[10][20] );
  subject[0][0] = 2;
  EXPECT_EQ(2, *subject.data());
}
