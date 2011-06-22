#ifndef FFTW_PLAN_H
#define FFTW_PLAN_H

#include <boost/shared_ptr.hpp>
#include <fftw3.h>

namespace ARD
{
  typedef boost::shared_ptr<fftw_plan_s> FFTWPlan;  
};

#endif // FFTW_PLAN_H