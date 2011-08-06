#ifndef SCENE_H
#define SCENE_H

#include <boost/shared_ptr.hpp>
#include "signal.h"
#include "size.h"
#include "microphone.h"
#include "source.h"
#include "force_field.h"
#include "spectrum_pool.h"
#include "dct_engine_factory.h"

namespace ARD
{
  class Scene
  {
  public:
    Scene(const Size& size, const double dt, const DCTEngineFactoryPointer engine_factory);
    MicrophonePointer Update();
    Size size() { return size_; };
    void set_microphone(MicrophonePointer microphone) { microphone_ = microphone; };
    void set_source(SourcePointer source) { source_ = source; };

  private:
    Size size_;
    MicrophonePointer microphone_;
    SourcePointer source_;
    ForceFieldPointer force_field_;
    SpectrumPoolPointer spectrum_pool_;
  };

  typedef boost::shared_ptr<Scene> ScenePointer;
}

#endif // SCENE_H
