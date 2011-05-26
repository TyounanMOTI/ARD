#define BOOST_TEST_MODULE ARDTest
#include <boost/test/included/unit_test.hpp>
#include <boost/scoped_ptr.hpp>
#include <ARD.h>

BOOST_AUTO_TEST_CASE( instance_initialization_test )
{
  boost::shared_ptr<Geometry> geometry(new Geometry());
  boost::scoped_ptr<ARD> subject(new ARD(geometry));
  BOOST_CHECK(subject != NULL);
}
