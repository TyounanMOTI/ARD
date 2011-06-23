#ifndef SPECTRUM_POOL_H
#define SPECTRUM_POOL_H

#include <boost/shared_ptr.hpp>
#include "position.h"
#include "microphone.h"

namespace ARD
{
  class SpectrumPool
  {
  public:
    MicrophonePointer Update(MicrophonePointer microphone);
  };

  typedef boost::shared_ptr<SpectrumPool> SpectrumPoolPointer;
};

#endif // SPECTRUM_POOL_H