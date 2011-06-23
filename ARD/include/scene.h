#ifndef SCENE_H
#define SCENE_H

#include <boost/shared_ptr.hpp>
#include "signal.h"

namespace ARD
{
  class Scene
  {
  public:
    Signal Update();
  };

  typedef boost::shared_ptr<Scene> ScenePointer;
}

#endif // SCENE_H
