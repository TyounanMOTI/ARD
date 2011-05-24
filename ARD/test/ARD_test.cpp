#define BOOST_TEST_MODULE ARDTest
#include <boost/test/included/unit_test.hpp>
#include <boost/scoped_ptr.hpp>
#include <ARD.h>

BOOST_AUTO_TEST_CASE( class_definition_test )
{
  boost::scoped_ptr<ARD> subject(new ARD());
  BOOST_CHECK(subject != NULL);
}
