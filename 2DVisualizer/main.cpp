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
#define _USE_MATH_DEFINES
#include <math.h>

using namespace ARD;

class PressureSpectrum {
public:
  template <class ExtentList>
  PressureSpectrum(const ExtentList& extents, FFTWFloat2DArray& output)
    : _data(extents),
      _dct_engine(_data, output)
  {
    _data.Fill(0);
  }

  const FFTWFloat2DArray& InverseDCT() {
    return _dct_engine.Execute();
  }

  FFTWFloat2DArray _data;

private:
  DCTEngine<FFTWFloat2DArray, Backward> _dct_engine;
};

class Scene {
public:
  Scene(const int width, const int height, const float dt)
    : _extents(boost::extents[width][height]),
      _force_field(_extents),
      _pressure_field(_extents),
      _next(new PressureSpectrum(_extents, _pressure_field)),
      _current(new PressureSpectrum(_extents, _pressure_field)),
      _previous(new PressureSpectrum(_extents, _pressure_field)),
      _forward_dct_engine(_force_field),
      _width(width), _height(height),
      _dt(dt), _speed_of_sound(340.0),
      _omega_square(_extents), _cos(_extents), _current_pressure_spectrum_coeffient(_extents), _force_spectrum_coeffcient(_extents),
      _first_frame(true)
  {
    _force_field.Fill(0);
    _force_field[height/2][width/2] = pow(10,8);
    _pressure_field.Fill(0);
    InitializeOmegaSquare();
    InitializeCos();
    InitializeCurrentPressureSpectrumCoefficient();
    InitializeForceSpectrumCoefficient();
  }

  void InitializeOmegaSquare() {
    for (int y = 0; y < _height; y++) {
      for (int x = 0; x < _width; x++) {
        _omega_square[y][x] = pow(_speed_of_sound, 2) * pow(M_PI, 2) * (pow(x, 2)/pow(_width-1, 2) + pow(y, 2)/pow(_height-1, 2));
      }
    }
  }

  void InitializeCos() {
    for (int y = 0; y < _height; y++) {
      for (int x = 0; x < _width; x++) {
        _cos[y][x] = cos(sqrt(_omega_square[y][x])*_dt);
      }
    }
  }

  void InitializeCurrentPressureSpectrumCoefficient() {
    for (int y = 0; y < _height; y++) {
      for (int x = 0; x < _width; x++) {
        _current_pressure_spectrum_coeffient[y][x] = 2.0*_cos[y][x];
      }
    }
  }

  void InitializeForceSpectrumCoefficient() {
    for (int y = 0; y < _height; y++) {
      for (int x = 0; x < _width; x++) {
        _force_spectrum_coeffcient[y][x] = 2.0/_omega_square[y][x]*(1 - _cos[y][x]);
      }
    }
  }

  FFTWFloat2DArray::element* OutputPtr() {
    return _pressure_field.data();
  }

  void Update() {
    std::cout << "updated" << std::endl;
    if (_first_frame) {
      _first_frame = false;
    } else {
      _force_field.Fill(0);
    }
    const FFTWFloat2DArray& _force_spectrum = _forward_dct_engine.Execute();
    for (int y = 0; y < _height; y++) {
      for (int x = 0; x < _width; x++) {
        _next->_data[y][x] = _current_pressure_spectrum_coeffient[y][x]*_current->_data[y][x] - _previous->_data[y][x] + _force_spectrum_coeffcient[y][x]*_force_spectrum[y][x];
      }
    }
    _next->_data[0][0] = 0;

    _next->InverseDCT();
    TimeShift();
  }

  void TimeShift() {
    _next.swap(_current);
    _next.swap(_previous);
  }

  //private:
  decltype(boost::extents[1][1]) _extents;
  FFTWFloat2DArray _force_field, _pressure_field;
  std::unique_ptr<PressureSpectrum> _next, _current, _previous;
  DCTEngine<FFTWFloat2DArray, Forward> _forward_dct_engine;
  const int _width, _height;
  const float _dt, _speed_of_sound;
  FFTWFloat2DArray _omega_square, _cos, _current_pressure_spectrum_coeffient, _force_spectrum_coeffcient;
  bool _first_frame;
};

std::unique_ptr<Scene> scene;

void Update(void*) {
  scene->Update();
  //  std::cout << "updated" << std::endl;
}

int main(void) {
  const int width = 256;
  const int height = 256;
  scene.reset(new Scene(width, height, 0.001));
  for (int i = 0; i < 100; i++) {
    scene->Update();
  }

  vtkSmartPointer<vtkImageImport> imageImport = vtkSmartPointer<vtkImageImport>::New();
  //  imageImport->SetImportVoidPointer(const_cast<FFTWFloat2DArray::element*>(scene->_next->_data.data()));
  imageImport->SetImportVoidPointer(const_cast<FFTWFloat2DArray::element*>(scene->OutputPtr()));
  imageImport->SetDataExtent(0,width-1,0,height-1,0,0);
  imageImport->SetWholeExtent(0,width-1,0,height-1,0,0);
  imageImport->SetDataScalarTypeToFloat();
  imageImport->SetUpdateDataCallback(Update);
  imageImport->Update();

  const double* range = imageImport->GetOutput()->GetScalarRange();
  const double max_abs = range[1];
  std::cout << "max_abs: " << max_abs << std::endl;

  vtkSmartPointer<vtkImageMapToColors> imageMapToColors = vtkSmartPointer<vtkImageMapToColors>::New();
  vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
  colorTransferFunction->SetColorSpaceToLab();
  colorTransferFunction->AddRGBPoint(-max_abs, 0, 0, 1);
  colorTransferFunction->AddRGBPoint(0, 1, 1, 1);
  colorTransferFunction->AddRGBPoint(max_abs, 1, 0, 0);

  imageMapToColors->SetLookupTable(colorTransferFunction);
  imageMapToColors->SetInputConnection(imageImport->GetOutputPort());

  vtkSmartPointer<vtkImageViewer> viewer = vtkSmartPointer<vtkImageViewer>::New();
  viewer->SetInputConnection(imageMapToColors->GetOutputPort());
  viewer->SetColorWindow(255);
  viewer->SetColorLevel(127.5);

  vtkSmartPointer<vtkTIFFWriter> writer = vtkSmartPointer<vtkTIFFWriter>::New();
  writer->SetInputConnection(imageMapToColors->GetOutputPort());
  writer->SetCompressionToNoCompression();

  vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  viewer->SetupInteractor(interactor);

  viewer->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
