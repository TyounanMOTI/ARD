#include <vtkSmartPointer.h>
#include <vtkImageImport.h>
#include <vtkImageMapToColors.h>
#include <vtkColorTransferFunction.h>
#include <vtkLookupTable.h>
#include <vtkImageViewer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMath.h>
#include <ARD.h>
#include <iostream>

using namespace ARD;

int main(void) {
  FFTWFloat2DArray data = FFTWFloat2DArray(boost::extents[256][256]);
  for (int y = 0; y < 256; y++) {
    for (int x = 0; x < 256; x++) {
      data[y][x] = (float)x / 255.0;
    }
  }

  vtkSmartPointer<vtkImageImport> imageImport = vtkSmartPointer<vtkImageImport>::New();
  imageImport->SetImportVoidPointer(data.data());
  imageImport->SetDataExtent(0,255,0,255,0,0);
  imageImport->SetWholeExtent(0,255,0,255,0,0);
  imageImport->SetDataScalarTypeToFloat();

  vtkSmartPointer<vtkImageMapToColors> imageMapToColors = vtkSmartPointer<vtkImageMapToColors>::New();
  vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
  colorTransferFunction->SetColorSpaceToLab();
  colorTransferFunction->AddRGBPoint(0, 0, 0, 1);
  colorTransferFunction->AddRGBPoint(0.5, 1, 1, 1);
  colorTransferFunction->AddRGBPoint(1, 1, 0, 0);

  imageMapToColors->SetLookupTable(colorTransferFunction);
  imageMapToColors->SetInputConnection(imageImport->GetOutputPort());

  vtkSmartPointer<vtkImageViewer> viewer = vtkSmartPointer<vtkImageViewer>::New();
  viewer->SetInputConnection(imageMapToColors->GetOutputPort());
  viewer->SetColorWindow(255);
  viewer->SetColorLevel(127.5);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  viewer->SetupInteractor(interactor);

  viewer->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
