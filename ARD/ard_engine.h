#ifndef ARD_ENGINE_H
#define ARD_ENGINE_H

#include <geometry.h>
#include <boost/shared_ptr.hpp>
// ARD: Adaptive Rectangular Decomposition
// solver class
class ARDEngine
{
public:
  ARDEngine(boost::shared_ptr<const Geometry> geometry) : geometry(geometry) {};

private:
  boost::shared_ptr<const Geometry> geometry;
};

#endif // ARD_ENGINE_H