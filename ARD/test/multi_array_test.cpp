#include <gtest/gtest.h>
#include <boost/multi_array.hpp>
#include <boost/assign.hpp>
#include <multi_array.h>
#include <array>

using namespace ARD;

TEST(MultiArrayTest, InitializeSameShape) {
  typedef boost::multi_array<int, 2> Subject;
  Subject subject(boost::extents[20][10]);
  subject[10][5] = 10;
  std::vector<Subject::size_type> shape(subject.shape(), subject.shape() + subject.num_dimensions());
  Subject result(shape);
  EXPECT_NE(10, result[10][5]);
}

TEST(MultiArrayTest, Fill) {
  MultiArray<int, 2> subject(boost::extents[20][10]);
  subject.Fill(10);
  EXPECT_EQ(10, subject[0][0]);
  EXPECT_EQ(10, subject[5][4]);
  EXPECT_EQ(10, subject[19][9]);
}

TEST(MultiArrayTest, GetElementType) {
  ::testing::StaticAssertTypeEq<boost::multi_array<int, 3>::element, int>();
}

TEST(MultiArrayTest, GetElementTypeUsingTypedef) {
  typedef boost::multi_array<int, 3> MultiArray;
  typedef MultiArray::element Element;
  ::testing::StaticAssertTypeEq<Element, int>();
}

TEST(MultiArrayTest, IndexAccessingByVector) {
  using namespace boost::assign;
  typedef boost::multi_array<int, 3> MultiArray;
  MultiArray subject(boost::extents[20][10][5]);
  std::vector<MultiArray::index> index;
  index += 1,2,3;
  subject(index) = 3;
  EXPECT_EQ(3, subject(index));
}
