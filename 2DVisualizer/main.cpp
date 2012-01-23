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

using namespace ARD;

class Scene {
public:
  Scene(const int width, const int height)
    : _force_field(FFTWFloat2DArray(boost::extents[width][height])),
      _forward_dct_engine(_force_field)
  {};

  void Update() {
    _force_field.Fill(0);
    //    const FFTWFloat2DArray& _force_spectrum = _forward_dct_engine.Execute();
  }

private:
  FFTWFloat2DArray _force_field;
  DCTEngine<FFTWFloat2DArray, Forward> _forward_dct_engine;
};

int main(void) {
  const int width = 256;
  const int height = 256;
  Scene scene(width, height);
  FFTWFloat2DArray force_field = FFTWFloat2DArray(boost::extents[width][height]);
  force_field.Fill(0);
  force_field[height/2][width/2] = 1;

  typedef DCTEngine<FFTWFloat2DArray, Forward> ForwardEngine;
  ForwardEngine forward_engine(force_field);
  const FFTWFloat2DArray& force_spectrum = forward_engine.Execute();

  typedef DCTEngine<FFTWFloat2DArray, Backward> BackwardEngine;
  BackwardEngine backward_engine(force_spectrum);
  const FFTWFloat2DArray& result = backward_engine.Execute();

  vtkSmartPointer<vtkImageImport> imageImport = vtkSmartPointer<vtkImageImport>::New();
  imageImport->SetImportVoidPointer(const_cast<FFTWFloat2DArray::element*>(result.data()));
  imageImport->SetDataExtent(0,255,0,255,0,0);
  imageImport->SetWholeExtent(0,255,0,255,0,0);
  imageImport->SetDataScalarTypeToFloat();
  imageImport->Update();

  double* range = imageImport->GetOutput()->GetScalarRange();
  std::cout << "min: " << range[0] << ", max: " << range[1] << std::endl;
  std::cout << "center: " << (range[0] + range[1])/2 << std::endl;

  vtkSmartPointer<vtkImageMapToColors> imageMapToColors = vtkSmartPointer<vtkImageMapToColors>::New();
  vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
  colorTransferFunction->SetColorSpaceToLab();
  colorTransferFunction->AddRGBPoint(range[0], 0, 0, 1);
  colorTransferFunction->AddRGBPoint((range[1]+range[0])/2, 1, 1, 1);
  colorTransferFunction->AddRGBPoint(range[1], 1, 0, 0);

  imageMapToColors->SetLookupTable(colorTransferFunction);
  imageMapToColors->SetInputConnection(imageImport->GetOutputPort());

  vtkSmartPointer<vtkImageViewer> viewer = vtkSmartPointer<vtkImageViewer>::New();
  viewer->SetInputConnection(imageMapToColors->GetOutputPort());
  viewer->SetColorWindow(255);
  viewer->SetColorLevel(127.5);

  vtkSmartPointer<vtkTIFFWriter> writer = vtkSmartPointer<vtkTIFFWriter>::New();
  writer->SetInputConnection(imageMapToColors->GetOutputPort());
  writer->SetCompressionToNoCompression();
  writer->SetFileName("out.tiff");
  writer->Write();

  vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  viewer->SetupInteractor(interactor);

  viewer->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
