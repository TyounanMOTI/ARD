#include <gtest/gtest.h>

enum {
  CONSTRUCTOR,
  COPY_CONSTRUCTOR,
};

class Bar
{
public:
  explicit Bar(const int b) : a(CONSTRUCTOR) {};

  int a;

private:
  Bar(const Bar& bar) : a(COPY_CONSTRUCTOR) {};
};

class Foo
{
public:
  Foo() : bar(0) {};

  Bar bar;
};

TEST(ConstructorTest, FooCallsConstructorOfBar) {
  Foo foo;
  EXPECT_EQ(CONSTRUCTOR, foo.bar.a);

  Bar bar(2);
}
