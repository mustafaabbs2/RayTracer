#include "KernelWrapper.h"

__global__ void cuda_hello()
{
	printf("Hello World from a GPU \n");
}

void RayKernelWrapper()
{
	cuda_hello<<<1, 100>>>();
}