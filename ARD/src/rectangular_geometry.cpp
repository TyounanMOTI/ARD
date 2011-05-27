#include <vector>
#include <boost/shared_ptr.hpp>
#include <rectangular_geometry.h>
#include <rectangular_sound_field.h>

SoundField* RectangularGeometry::Decomposit() {
  return new RectangularSoundField();
}
