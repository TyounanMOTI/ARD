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
  cufftReal *buffer_host;
  cufftReal *buffer_device;
  cufftReal *result_host;

  cudaMallocHost((void**)&original_host, sizeof(cufftReal)*input_length);
  cudaHostAlloc((void**)&buffer_host, sizeof(cufftReal)*input_length, cudaHostAllocMapped);
  cudaMallocHost((void**)&result_host, sizeof(cufftReal)*input_length);

  for (int i = 0; i < input_length; i++) {
    original_host[i] = sin((float)2.0*CUDART_PI_F*i/input_max_index);
  }

  for (int i = 0; i < input_length; i++) {
    buffer_host[i] = original_host[i] + original_host[input_max_index - i] +
                    2*sin(i*CUDART_PI_F/input_max_index)*(original_host[i] - original_host[input_max_index - i]);
  }

  EXPECT_EQ(cudaSuccess, cudaHostGetDevicePointer(&buffer_device, buffer_host, 0));
   
  cufftPlan1d(&plan, NX, CUFFT_R2C, BATCH);
  cufftExecR2C(plan, buffer_device, (cufftComplex*)buffer_device);
  cufftDestroy(plan);
  
  cufftReal sum = 0;
  sum += original_host[0]/2.0f;
  for (int i = 1; i < input_length-1; i++) {
    sum += original_host[i]*cos(i*CUDART_PI_F/input_max_index);
  }
  sum += original_host[input_max_index]/2.0f;
  result_host[1] = sum/input_max_index*2.0f;

  result_host[0] = buffer_host[0];
  for (int i = 2; i < input_length; i++) {
    if (i % 2 == 0) {
      result_host[i] = buffer_host[i]/input_max_index*2.0f;
    } else {
      result_host[i] = (result_host[i-2] + buffer_host[i])/input_max_index*2.0f;
    }
  }

  OutputRealArray(input_length, result_host);

  cudaFreeHost(original_host);
  cudaFreeHost(buffer_host);
  cudaFreeHost(result_host);
}
