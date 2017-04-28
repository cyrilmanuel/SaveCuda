#include "Indice2D.h"
#include "Indice1D.h"
#include "cudaTools.h"

#include "reductionADD.h"
#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void Montecarlo(float* ptrGMResultat, int nbSlice, float* ptrGenerator);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void reductionIntraThread(float* tabSM, int nbSlice, float* ptrGenerator);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * output : void required !!
 */
__global__ void Montecarlo(float* ptrGMResultat, int nbSlice, float* ptrGenerator)
    {
    extern __shared__ float tabSM[];
    reductionIntraThread(tabSM, nbSlice);
    __syncthreads();
    reductionADD<float>(tabSM, ptrGMResultat);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ float work(float x, float y);
    {
    // regarde si la fleche est en dessous ou en dessus
    return 1;
    }

__device__ void reductionIntraThread(float* tabSM, int nbSlice, float* ptrGenerator)
    {

    const int TID = Indice1D::tid();

    // Global Memory -> Register (optimization)
    curandState localGenerator = ptrGenerator[TID];

    float xAlea;
    float yAlea;
    for (long i = 1; i <= n; i++)
    {
    xAlea = curand_uniform(&localGenerator);
    yAlea = curand_uniform(&localGenerator);

    // la fonction work va pouvoir determiner si le thread (plus précisement la flechette)
    // se trouve en dessus ou en dessous dans le caré
    work(xAlea,yAlea);

    }

}
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

