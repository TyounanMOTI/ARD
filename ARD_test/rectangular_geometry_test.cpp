#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <rectangular_geometry.h>

TEST(RectangularGeometry, Decomposit) {
  boost::scoped_ptr<RectangularGeometry> subject(new RectangularGeometry(20, 10));
  boost::scoped_ptr<SoundField> sound_field(subject->Decomposit());
}
