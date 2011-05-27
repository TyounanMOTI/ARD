#ifndef RECTANGULAR_GEOMETRY_H
#define RECTANGULAR_GEOMETRY_H

#include <boost/shared_ptr.hpp>
#include "geometry.h"
#include "rectangular_sound_field.h"
#include "sound_field.h"

class RectangularGeometry : public Geometry
{
public:
  RectangularGeometry(int width, int height) : width(width), height(height) {};
  SoundField* Decomposit();

private:
  int width, height;
};

#endif //RECTANGULAR_GEOMETRY_H