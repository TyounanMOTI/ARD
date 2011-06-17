#ifndef MODE_MAP_H
#define MODE_MAP_H

#include <boost/shared_ptr.hpp>
#include "multi_array.h"
#include "pressure_map.h"
#include "size.h"
#include "precision.h"
#include <fftw3.h>

namespace ARD
{
  class PressureMap;
  typedef boost::shared_ptr<PressureMap> PressureMapPointer;
  typedef Precision ModeCoefficient;
  typedef boost::shared_ptr<fftw_plan_s> FFTWPlan;

  class ModeMap : public MultiArray
  {
  public:
    ModeMap(const Size& size);
    ModeMap(const Size& size, const MultiArrayContent content);
    PressureMapPointer InverseDCT();
    void Normalize();

  private:
    void Init();
    void InitOutputBuffer();
    void InitPlan();

    MultiArrayPointer idct_output_buffer_;
    FFTWPlan idct_plan_;
  };  

  typedef boost::shared_ptr<ModeMap> ModeMapPointer;
};

#endif
