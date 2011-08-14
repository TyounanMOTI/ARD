#ifndef FORCE_SPECTRUM_H
#define FORCE_SPECTRUM_H

#include <boost/shared_ptr.hpp>
#include <array_interface.h>

namespace ARD
{
  class ForceSpectrum
  {
  public:
    explicit ForceSpectrum(const ArrayInterfacePointer content) : content_(content->Clone()) {};
    const Size size() const { return content_->size(); };
    const Precision content(const Position& position) const { return content_->content(position); };
    
  private:
    ArrayInterfacePointer content_;
  };

  typedef boost::shared_ptr<ForceSpectrum> ForceSpectrumPointer;
}

#endif // FORCE_SPECTRUM_H
