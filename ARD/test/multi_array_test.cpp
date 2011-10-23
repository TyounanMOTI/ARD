#include <gtest/gtest.h>
#include <boost/multi_array.hpp>
#include <boost/strong_typedef.hpp>
#include <boost/assign.hpp>
#include <multi_array.h>
#include <array>

TEST(MultiArrayTest, InitializeSameShape) {
  typedef boost::multi_array<int, 2> Subject;
  Subject subject(boost::extents[20][10]);
  subject[10][5] = 10;
  std::vector<Subject::size_type> shape(subject.shape(), subject.shape() + subject.num_dimensions());
  Subject result(shape);
  EXPECT_NE(10, result[10][5]);
}

TEST(MultiArrayTest, Fill) {
  boost::multi_array<int, 2> subject(boost::extents[20][10]);
  ARD::Fill(subject, 10);
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

TEST(MultiArrayTest, WeakTyping) {
  typedef float cudaReal;
  typedef float fftwReal;
  ::testing::StaticAssertTypeEq<boost::multi_array<cudaReal, 3>, boost::multi_array<fftwReal, 3> >();
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

TEST(StrongTypedefTest, StrongTypedefining) {
  BOOST_STRONG_TYPEDEF(float, cudaReal);
  BOOST_STRONG_TYPEDEF(float, fftwReal);
  // should fail
  // ::testing::StaticAssertTypeEq<boost::multi_array<cudaReal, 3>, boost::multi_array<fftwReal, 3> >();
  EXPECT_EQ(sizeof(float), sizeof(cudaReal));
  EXPECT_EQ(sizeof(cudaReal), sizeof(fftwReal));
}

TEST(StrongTypedefTest, SizeofDouble) {
  BOOST_STRONG_TYPEDEF(double, cudaReal);
  EXPECT_EQ(sizeof(double), sizeof(cudaReal));
}
