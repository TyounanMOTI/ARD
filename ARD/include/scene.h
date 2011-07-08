#ifndef SCENE_H
#define SCENE_H

#include <boost/shared_ptr.hpp>
#include "signal.h"
#include "size.h"
#include "point_microphone.h"
#include "source.h"

namespace ARD
{
  class Scene
  {
  public:
    Scene(const Size& size) : size_(size) {};
    PointMicrophonePointer Update();
    Size size() { return size_; };
    void set_microphone(PointMicrophonePointer microphone) { microphone_ = microphone; };
    void set_source(SourcePointer source) { source_ = source; };

  private:
    Size size_;
    PointMicrophonePointer microphone_;
    SourcePointer source_;
  };

  typedef boost::shared_ptr<Scene> ScenePointer;
}

#endif // SCENE_H
