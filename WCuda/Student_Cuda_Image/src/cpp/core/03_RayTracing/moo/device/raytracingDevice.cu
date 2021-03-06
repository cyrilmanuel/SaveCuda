#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "IndiceTools_GPU.h"

#include "RayTracingMath.h"
using namespace gpu;

// Attention : 	Choix du nom est impotant!
//		VagueDevice.cu et non Vague.cu
// 		Dans ce dernier cas, probl�me de linkage, car le nom du .cu est le meme que le nom d'un .cpp (host)
//		On a donc ajouter Device (ou n'importequoi) pour que les noms soient diff�rents!

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/
__constant__ Sphere TAB_CM[20]; //20 = nb sphere
__constant__ Sphere TAB_SM[20];
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
__global__ void raytracing_GM(uchar4* ptrDevPixels, uint w, uint h, float t, int nbSphere, Sphere* ptrDevTabSphere);
__global__ void raytracing_CM(uchar4* ptrDevPixels, uint w, uint h, float t);
__global__ void raytracing_SM(uchar4* ptrDevPixels, uint w, uint h, float t, int nbSphere, Sphere* ptrDevTabSphere);

// pour host
__host__ void uploadGPU(Sphere* SphereTab);

// pour device
__device__ void copyGMToSM(int nbSphere, Sphere* ptrDevTabGM, Sphere* ptrDevTabSM);
__device__ void work(uchar4* ptrDevPixels, uint w, uint h, float t, int nbSphere, Sphere* ptrDevTabSphere);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void raytracing_GM(uchar4* ptrDevPixels, uint w, uint h, float t, int nbSphere, Sphere* ptrDevTabSphere)
    {
    work(ptrDevPixels, w, h, t, nbSphere, ptrDevTabSphere);
    }
__global__ void raytracing_CM(uchar4* ptrDevPixels, uint w, uint h, float t)
    {
    work(ptrDevPixels, w, h, t, 20, TAB_CM);
    }
__global__ void raytracing_SM(uchar4* ptrDevPixels, uint w, uint h, float t, int nbSphere, Sphere* ptrDevTabSphere)
    {
    extern __shared__ Sphere tabSM[];
    copyGMToSM(nbSphere, ptrDevTabSphere, tabSM );
    __syncthreads();
    work(ptrDevPixels, w, h, t, nbSphere, tabSM);
    }

/**
 * apeller par le host
 */
__host__ void uploadGPU(Sphere* SphereTab)
    {
    size_t size = 20 * sizeof(Sphere);
    HANDLE_ERROR(cudaMemcpyToSymbol(TAB_CM, SphereTab, size, 0, cudaMemcpyHostToDevice));
    }

__device__ void copyGMToSM(int nbSphere, Sphere* ptrDevTabGM, Sphere* ptrDevTabSM)
    {

    const int TID_LOCAL = Indice2D::tidLocal();
    const int NB_THREAD_LOCAL = Indice2D::nbThreadLocal();

    int s = TID_LOCAL;

    while (s < nbSphere)
	{
	ptrDevTabSM[s] = ptrDevTabGM[s];
	s += NB_THREAD_LOCAL;
	}
    }

__device__ void work(uchar4* ptrDevPixels, uint w, uint h, float t, int nbSphere, Sphere* ptrDevTabSphere)
    {
    RayTracingMath rayTracingMath = RayTracingMath(nbSphere, ptrDevTabSphere);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    int i, j;

    int s = TID;
    while (s < w * h)
	{
	IndiceTools::toIJ(s, w, &i, &j);

	rayTracingMath.colorIJ(&s[ptrDevPixels], i, j, t);

	s += NB_THREAD;
	}
    }
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

