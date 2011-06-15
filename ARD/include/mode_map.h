#ifndef MODE_MAP_H
#define MODE_MAP_H

#include <boost/shared_ptr.hpp>
#include "multi_array.h"
#include "pressure_map.h"
#include "size.h"
#include "precision.h"

namespace ARD
{
  class PressureMap;
  typedef boost::shared_ptr<PressureMap> PressureMapPointer;
  typedef Precision ModeCoefficient;

  class ModeMap : public MultiArray
  {
  public:
    ModeMap(const Size& size) : MultiArray(size) {};
    ModeMap(const Size& size, const MultiArrayContent& content) : MultiArray(size, content) {};
    PressureMapPointer InverseDCT() const;
  };  

  typedef boost::shared_ptr<ModeMap> ModeMapPointer;
};

#endif
