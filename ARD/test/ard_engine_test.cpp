#define BOOST_TEST_MODULE ARDEngineTest
#include <boost/test/included/unit_test.hpp>
#include <boost/scoped_ptr.hpp>
#include <ard_engine.h>

BOOST_AUTO_TEST_CASE( instance_initialization_test )
{
  boost::shared_ptr<Geometry> geometry(new Geometry());
  boost::scoped_ptr<ARDEngine> subject(new ARDEngine(geometry));
  BOOST_CHECK(subject != NULL);
}
