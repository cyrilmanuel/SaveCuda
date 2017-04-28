#include "Indice1D.h"
#include "cudaTools.h"

__device__ void reductionIntraThread(int* tabSM, int* tabGM, int dataSizeSM);
__device__ void reductionInterBlock(int* tabSM, int* tabGM, int dataMax);
__device__ void initSM(int* tabSM, int max);
__device__ void resetGM(int* tabGM, int max);

__global__ void histoPerso(int* ptrDevData, int max, int size);

__global__ void histoPerso(int* ptrDevData, int max, int size)
    {
    extern __shared__ int tabSM[];

    initSM(tabSM, max);
    __syncthreads();
    reductionIntraThread(tabSM, ptrDevData, size);
    __syncthreads();

    resetGM(ptrDevData, max);
    __syncthreads();
    reductionInterBlock(tabSM, ptrDevData, max);
    }

__device__ void initSM(int* tabSM, int max)
    {
    const int TID_LOCAL = Indice1D::tidLocal();
    const int NB_THREAD_LOCAL = Indice1D::nbThreadBlock();

    int s = TID_LOCAL;

    while (s < max)
	{
	tabSM[s] = 0;
	s += NB_THREAD_LOCAL;
	}
    }

__device__ void reductionIntraThread(int* tabSM, int* tabGM, int dataSize)
    {
    const int TID = Indice1D::tid();
    const int NB_THREAD = Indice1D::nbThread();

    int s = TID;

    while (s < dataSize)
	{
	atomicAdd(&tabSM[tabGM[s]], 1);
	s += NB_THREAD;
	}
    }

__device__ void resetGM(int* tabGM, int max)
    {
    const int TID = Indice1D::tid();
    const int NB_THREAD = Indice1D::nbThread();

    int s = TID;

    while (s < max)
	{
	tabGM[s] = 0;
	s += NB_THREAD;
	}
    }

__device__ void reductionInterBlock(int* tabSM, int* tabGM, int dataMax)
    {
    const int TID = Indice1D::tid();
    const int NB_THREAD = Indice1D::nbThread();
    const int TID_LOCAL = Indice1D::tidLocal();
    const int NB_THREAD_LOCAL = Indice1D::nbThreadBlock();

    int s = TID_LOCAL;

    while (s < dataMax)
	{
	atomicAdd(&tabGM[s], tabSM[s]);
	s += NB_THREAD_LOCAL;
	}
    }
