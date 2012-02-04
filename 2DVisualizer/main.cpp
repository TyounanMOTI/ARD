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
#include <math.h>

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
    std::cout << "updated" << std::endl;
    if (_first_frame) {
      _first_frame = false;
    } else {
      _force_field.Fill(0);
    }
    const FFTWFloat3DArray& _force_spectrum = _forward_dct_engine.Execute();
    for (int z = 0; z < _shape[0]; z++) {
      for (int y = 0; y < _shape[1]; y++) {
        for (int x = 0; x < _shape[2]; x++) {
          _next->_data[z][y][x] = _current_pressure_spectrum_coeffient[z][y][x]*_current->_data[z][y][x] - _previous->_data[z][y][x] + _force_spectrum_coeffcient[z][y][x]*_force_spectrum[z][y][x];
        }
      }
    }
    _next->_data[0][0][0] = 0;

    _next->InverseDCT();
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
};

std::unique_ptr<Scene> scene;

void Update(void*) {
  scene->Update();
  std::cout << "updated" << std::endl;
}

int main(int argc, char** argv) {
  int depth, height, width;
  if (argc < 3) {
    depth = 64;
    height = 64;
    width = 64;
  } else {
    depth = atoi(argv[1]);
    height = atoi(argv[2]);
    width = atoi(argv[3]);
  }
  scene.reset(new Scene(std::vector<FFTWFloat3DArray::index>({depth, height, width}), 0.001));
  for (int i = 0; i < 10; i++) {
    scene->Update();
  }

  vtkSmartPointer<vtkImageImport> imageImport = vtkSmartPointer<vtkImageImport>::New();
  imageImport->SetImportVoidPointer(const_cast<FFTWFloat3DArray::element*>(scene->OutputPtr()));
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
