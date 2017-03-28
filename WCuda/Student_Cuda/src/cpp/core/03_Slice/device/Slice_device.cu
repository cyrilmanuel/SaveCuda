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

__global__ void Slice(float* ptrGMResultat, int nbSlice);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


static __device__ void reductionIntraThread(float* tabSM, int nbSlice);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * output : void required !!
 */
__global__ void Slice(float* ptrGMResultat, int nbSlice)
    {
    extern __shared__ float tabSM[];
    reductionIntraThread(tabSM, nbSlice);
    __syncthreads();
    reductionADD<float>(tabSM, ptrGMResultat);
    }


/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ float aireRectangle(int s){
 // calcul l'aire des Rectangles
    return 1;
}

__device__ void reductionIntraThread(float* tabSM, int nbSlice)
    {
    const int NB_THREAD=Indice1D::nbThread();
    const int TID=Indice1D::tid();

    int s = TID;
    float sumLocal = 0;
       while (s<nbSlice)
   	{
	sumLocal+=aireRectangle(s);
	tabSM[s] = sumLocal;
   	s+= NB_THREAD;
   	}
    }
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

