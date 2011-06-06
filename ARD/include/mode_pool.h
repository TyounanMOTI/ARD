#ifndef MODE_POOL_H
#define MODE_POOL_H

#include <boost/shared_ptr.hpp>
#include "position.h"
#include "microphone.h"

namespace ARD
{
  class ModePool
  {
  public:
    MicrophonePointer Update(MicrophonePointer microphone);
  };
};

#endif // MODE_POOL_H