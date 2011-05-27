#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <ard_engine.h>
#include <geometry.h>

TEST(ARDEngineTest, InitializationTest) {
  boost::shared_ptr<Geometry> geometry(new Geometry());
  boost::scoped_ptr<ARDEngine> subject(new ARDEngine(geometry));
}
