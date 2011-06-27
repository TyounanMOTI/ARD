#include <gtest/gtest.h>
#include <boost/random.hpp>

using namespace boost;

TEST(RandomTest, MinStdRand) {
  minstd_rand    gen( 42 );
	uniform_real<> dst( 0, 1 );
	variate_generator<minstd_rand&, uniform_real<>> rand( gen, dst );
  EXPECT_TRUE( rand() <= 1 );
}
