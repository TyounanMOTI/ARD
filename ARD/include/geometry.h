#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <boost/shared_ptr.hpp>
#include <vector>
#include "sound_field.h"

class Geometry
{
public:
  virtual SoundField* Decomposit() = 0;
  virtual ~Geometry() {};
};

#endif // GEOMETRY_H