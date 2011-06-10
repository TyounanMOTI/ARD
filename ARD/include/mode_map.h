#ifndef MODE_MAP_H
#define MODE_MAP_H

#include <boost/shared_ptr.hpp>
#include "multi_array.h"
#include "pressure_map.h"
#include "size.h"

namespace ARD
{
  class PressureMap;
  typedef boost::shared_ptr<PressureMap> PressureMapPointer;
  
  class ModeMap : public MultiArray
  {
  public:
    ModeMap(Size size) : MultiArray(size) {};
    PressureMapPointer InverseDCT();
  };  

  typedef boost::shared_ptr<ModeMap> ModeMapPointer;
};

#endif
