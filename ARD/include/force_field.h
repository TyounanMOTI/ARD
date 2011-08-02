#ifndef FORCE_FIELD_H
#define FORCE_FIELD_H

#include <boost/shared_ptr.hpp>
#include "force_spectrum.h"
#include "fftw_plan.h"
#include <fftw_array.h>

namespace ARD {
  class ForceSpectrum;
  class ForceField : public FFTWArray
  {
  public:
    ForceField(const Size& size);
    ForceField(const ForceField& original);
    ForceSpectrumPointer DCT();

  private:
    void Init();
    void InitOutputBuffer();
    void InitPlan();

    ForceSpectrumPointer dct_output_buffer_;
    FFTWPlan dct_plan_;
  };

  typedef boost::shared_ptr<ForceField> ForceFieldPointer;
};

#endif // FORCE_FIELD_H
