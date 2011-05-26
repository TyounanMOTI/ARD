#ifndef ARD_H
#define ARD_H

#include <geometry.h>
#include <boost/shared_ptr.hpp>

// ARD: Adaptive Rectangular Decomposition
// solver class
class ARD
{
public:
  ARD(boost::shared_ptr<const Geometry> geometry) : geometry(geometry) {};

private:
  boost::shared_ptr<const Geometry> geometry;
};

#endif // ARD_H