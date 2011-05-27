#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <ard_engine.h>
#include <rectangular_geometry.h>

TEST(ARDEngineTest, InitializationTest) {
  boost::shared_ptr<RectangularGeometry> geometry(new RectangularGeometry(20, 10));
  boost::scoped_ptr<ARDEngine> subject(new ARDEngine(geometry));
}
