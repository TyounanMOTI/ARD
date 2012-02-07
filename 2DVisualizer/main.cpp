#include <vtkSmartPointer.h>
#include <vtkImageImport.h>
#include <vtkImageData.h>
#include <vtkImageMapToColors.h>
#include <vtkColorTransferFunction.h>
#include <vtkImageViewer.h>
#include <vtkTIFFWriter.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMath.h>
#include <ARD.h>
#include <iostream>
#include <functional>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>
#include <numeric>
#include <forward_list>

#include <unixstl/performance/performance_counter.hpp>

using namespace ARD;

class Scene {
public:
  Scene(const std::vector<FFTWFloat3DArray::index>& extents, const float dt)
    : _shape(extents),
      _force_field(extents),
      _pressure_field(extents),
      _next(new PressureSpectrum<FFTWFloat3DArray>(extents, _pressure_field)),
      _current(new PressureSpectrum<FFTWFloat3DArray>(extents, _pressure_field)),
      _previous(new PressureSpectrum<FFTWFloat3DArray>(extents, _pressure_field)),
      _forward_dct_engine(_force_field),
      _dt(dt), _speed_of_sound(340.0),
      _omega_square(extents), _cos(extents), _current_pressure_spectrum_coeffient(extents), _force_spectrum_coeffcient(extents),
      _first_frame(true)
  {
    _force_field.Fill(0);
    _force_field[_shape[0]/2][_shape[1]/2][_shape[2]/2] = pow(10,8);
    _pressure_field.Fill(0);
    InitializeOmegaSquare();
    InitializeCos();
    InitializeCurrentPressureSpectrumCoefficient();
    InitializeForceSpectrumCoefficient();
  }

  void InitializeOmegaSquare() {
    for (int z = 0; z < _shape[0]; z++) {
      for (int y = 0; y < _shape[1]; y++) {
        for (int x = 0; x < _shape[2]; x++) {
          _omega_square[z][y][x] = pow(_speed_of_sound, 2) * pow(M_PI, 2) * (pow(x, 2)/pow(_shape[2]-1, 2) + pow(y, 2)/pow(_shape[1]-1, 2) + pow(z, 2)/pow(_shape[0]-1, 2));
        }
      }
    }
  }

  void InitializeCos() {
    for (int z = 0; z < _shape[0]; z++) {
      for (int y = 0; y < _shape[1]; y++) {
        for (int x = 0; x < _shape[2]; x++) {
          _cos[z][y][x] = cos(sqrt(_omega_square[z][y][x])*_dt);
        }
      }
    }
  }

  void InitializeCurrentPressureSpectrumCoefficient() {
    for (int z = 0; z < _shape[0]; z++) {
      for (int y = 0; y < _shape[1]; y++) {
        for (int x = 0; x < _shape[2]; x++) {
          _current_pressure_spectrum_coeffient[z][y][x] = 2.0*_cos[z][y][x];
        }
      }
    }
  }

  void InitializeForceSpectrumCoefficient() {
    for (int z = 0; z < _shape[0]; z++) {
      for (int y = 0; y < _shape[1]; y++) {
        for (int x = 0; x < _shape[2]; x++) {
          _force_spectrum_coeffcient[z][y][x] = 2.0/_omega_square[z][y][x]*(1 - _cos[z][y][x]);
        }
      }
    }
  }

  FFTWFloat2DArray::element* OutputPtr() {
    return _pressure_field.data() + _shape[2]*_shape[1]*_shape[0]/2;
  }

  void Update() {
    if (_first_frame) {
      _first_frame = false;
    } else {
      _force_field.Fill(0);
    }
    _timer.start();
    const FFTWFloat3DArray& _force_spectrum = _forward_dct_engine.Execute();
    _timer.stop();
    std::cout << _timer.get_microseconds() << " ";

    _timer.start();
    for (int z = 0; z < _shape[0]; z++) {
      for (int y = 0; y < _shape[1]; y++) {
        for (int x = 0; x < _shape[2]; x++) {
          _next->_data[z][y][x] = _current_pressure_spectrum_coeffient[z][y][x]*_current->_data[z][y][x] - _previous->_data[z][y][x] + _force_spectrum_coeffcient[z][y][x]*_force_spectrum[z][y][x];
        }
      }
    }
    _next->_data[0][0][0] = 0;
    _timer.stop();
    std::cout << _timer.get_microseconds() << " ";

    _timer.start();
    _next->InverseDCT();
    _timer.stop();
    std::cout << _timer.get_microseconds() << std::endl;

    TimeShift();
  }

  void TimeShift() {
    _next.swap(_current);
    _next.swap(_previous);
  }

  //private:
  std::vector<FFTWFloat3DArray::index> _shape;
  FFTWFloat3DArray _force_field, _pressure_field;
  std::unique_ptr<PressureSpectrum<FFTWFloat3DArray> > _next, _current, _previous;
  DCTEngine<FFTWFloat3DArray, Forward> _forward_dct_engine;
  const float _dt, _speed_of_sound;
  FFTWFloat3DArray _omega_square, _cos, _current_pressure_spectrum_coeffient, _force_spectrum_coeffcient;
  bool _first_frame;
  unixstl::performance_counter _timer;
};


int main(int argc, char** argv) {

  int depth, height, width;
  if (argc < 3) {
    depth = 32;
    height = 32;
    width = 32;
  } else {
    depth = atoi(argv[1]);
    height = atoi(argv[2]);
    width = atoi(argv[3]);
  }

  std::cerr << "<<<< " << depth << " x " << height << " x " << width << " >>>>" << std::endl;

  std::unique_ptr<Scene> scene(new Scene(std::vector<FFTWFloat3DArray::index>({depth, height, width}), 0.001));

  std::forward_list<double> execution_times;
  unixstl::performance_counter counter;
  const int MAX_ITER = 30;
  for (int i = 0; i < MAX_ITER; i++) {
    counter.start();
    scene->Update();
    counter.stop();
    execution_times.push_front(counter.get_microseconds());
    //    std::cerr << i << ": " << counter.get_microseconds() << std::endl;
  }
  //  std::cout << (double)accumulate(execution_times.begin(), execution_times.end(), 0) / MAX_ITER;
  std::cerr << std::endl;

  return EXIT_SUCCESS;
}
