#pragma once
#include <deque>
#include "microphone.h"

namespace ARD {
  template <class ArrayType>
  class Scene
  {
    typedef std::deque<std::shared_ptr<Microphone<ArrayType> > > MicrophoneDeque;
    
  public:
    template <class ExtentList>
    Scene(const ExtentList& extents) {}

    void AddMicrophone(std::shared_ptr<Microphone<ArrayType> > microphone) {
      _microphones.push_back(microphone);
    }
    
    MicrophoneDeque Update() {
      return _microphones;
    }

  private:
    MicrophoneDeque _microphones;
  };
}
