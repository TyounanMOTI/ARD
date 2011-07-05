#include <gtest/gtest.h>
#include <source.h>

using namespace ARD;

TEST(SourceTest, Pop) {
  std::vector<Power> content;
  content.push_back(Power(5.0));
  content.push_back(Power(1.0));
  SourcePointer subject(new Source(content));
  EXPECT_EQ(Power(5.0), subject->Pop());
  EXPECT_EQ(Power(1.0), subject->Pop());
}
