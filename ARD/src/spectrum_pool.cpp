#include <spectrum_pool.h>

using namespace ARD;

const double SpectrumPool::c = 340.0;

SpectrumPool::SpectrumPool(const Size& size, const double dt) : dt_(dt) {
  previous_.reset(new PressureSpectrum(size));
  now_.reset(new PressureSpectrum(size));
  next_.reset(new PressureSpectrum(size));
}

PressureSpectrumPointer SpectrumPool::Update(const ForceSpectrumPointer force_spectrum) {
  Size size = force_spectrum->content()->size();
  Position position;
  double omega = 0.0;
  for (long y = 0; y < size.height(); y++) {
    for (long x = 0; x < size.width(); x++) {
      omega = c * M_PI * sqrt((double)x*x/(size.width()*size.width()-1) + (double)y*y/(size.height()*size.height()-1));
      position = Position(x,y);
      next_->set_content(position,
                        ModeCoefficient(2.0*now_->content(position)*cos(omega*dt_) - previous_->content(position)
                        + 2.0*force_spectrum->content()->content(position)/(omega*omega)*(1-cos(omega*dt_))));
    }
  }
  next_->set_content(Position(0,0), ModeCoefficient(0.0)); // next_[0,0] is divided by zero
  PressureSpectrumPointer result = next_;
  TimeShift();
  return next_;
}

void SpectrumPool::TimeShift() {
  PressureSpectrumPointer temp = previous_;
  previous_ = now_;
  now_ = next_;
  next_ = temp;
}
