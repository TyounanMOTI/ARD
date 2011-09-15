#include <gtest/gtest.h>
#include "plot/output_array.h"
#include <cufft.h>
#include <math_constants.h>
#include <cuda_runtime.h>

TEST(CUFFTTest, RealToComplexDCT1D) {
  const int NX = 256;
  const int BATCH = 1;
  const int output_length = (NX/2+1)*BATCH;
  const int input_length = output_length*2;
  const int input_max_index = input_length - 1;
  cufftHandle plan;
  cufftReal *original_host;
  cufftReal *input_host;
  cufftReal *input_device;
  cufftComplex *output_device;
  cufftComplex*output_host;
  cufftReal *result_host;

  cudaMallocHost((void**)&original_host, sizeof(cufftReal)*input_length);
  cudaMallocHost((void**)&input_host, sizeof(cufftReal)*input_length);
  cudaMalloc((void**)&input_device, sizeof(cufftReal)*input_length);
  cudaMalloc((void**)&output_device, sizeof(cufftComplex)*output_length);
  cudaMallocHost((void**)&output_host, sizeof(cufftComplex)*output_length);
  cudaMallocHost((void**)&result_host, sizeof(cufftReal)*input_length);

  for (int i = 0; i < input_length; i++) {
    original_host[i] = sin((float)2.0*CUDART_PI_F*i/input_max_index);
  }

  for (int i = 0; i < input_length; i++) {
    input_host[i] = original_host[i] + original_host[input_max_index - i] +
                    2*sin(i*CUDART_PI_F/input_max_index)*(original_host[i] - original_host[input_max_index - i]);
  }

  cudaMemcpy(input_device, input_host, sizeof(cufftReal)*input_length, cudaMemcpyHostToDevice);
   
  cufftPlan1d(&plan, NX, CUFFT_R2C, BATCH);
  cufftExecR2C(plan, input_device, output_device);
  cufftDestroy(plan);

  cudaMemcpy(output_host, output_device, sizeof(cufftComplex)*output_length, cudaMemcpyDeviceToHost);

  cufftReal sum = 0;
  sum += original_host[0]/2.0;
  for (int i = 1; i < input_length-1; i++) {
    sum += original_host[i]*cos(i*CUDART_PI_F/input_max_index);
  }
  sum += original_host[input_max_index]*cos(CUDART_PI_F)/2.0;
  result_host[1] = sum*2.0/input_max_index;

  result_host[0] = output_host[0].x/input_max_index*2.0;
  for (int i = 2; i < input_length; i++) {
    if (i % 2 == 0) {
      result_host[i] = output_host[i/2].x/input_max_index*2.0;
    } else {
      result_host[i] = result_host[2*i-1] + output_host[i/2].y/input_max_index*2.0;
    }
  }

  OutputRealArray(input_length, result_host);

  cudaFreeHost(original_host);
  cudaFreeHost(input_host);
  cudaFree(input_device);
  cudaFreeHost(output_host);
  cudaFree(output_device);
  cudaFreeHost(result_host);
}
