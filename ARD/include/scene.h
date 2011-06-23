#ifndef SCENE_H
#define SCENE_H

#include <boost/shared_ptr.hpp>
#include "signal.h"
#include "size.h"

namespace ARD
{
  class Scene
  {
  public:
    Scene(const Size& size) : size_(size) {};
    Signal Update();
    Size size() { return size_; };

  private:
    Size size_;
  };

  typedef boost::shared_ptr<Scene> ScenePointer;
}

#endif // SCENE_H
