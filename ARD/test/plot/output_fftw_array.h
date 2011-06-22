#ifndef OUTPUT_FFTW_ARRAY_H
#define OUTPUT_FFTW_ARRAY_H

#include <fftw3.h>
#include <fstream>

void OutputRealArrayOfFFTWComplexArray(size_t size, fftw_complex* input);
void OutputFFTWRealArray(size_t size, double* input);
void OutputFFTWReal2DArray(int width, int height, double* input);

#endif // OUTPUT_FFTW_ARRAY_H
