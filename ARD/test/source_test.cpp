#include <gtest/gtest.h>
#include <source.h>

using namespace ARD;

TEST(SourceTest, Pop) {
  std::vector<Power> content;
  content.push_back(Power(5.0));
  content.push_back(Power(1.0));
  SourcePointer subject(new Source(Position(0,0), content));
  EXPECT_EQ(Power(5.0), subject->Pop());
  EXPECT_EQ(Power(1.0), subject->Pop());
}

TEST(SourceTest, EmptyPop) {
  std::vector<Power> content;
  SourcePointer subject(new Source(Position(0,0), content));
  EXPECT_EQ(Power(0.0), subject->Pop());
}
