#include <iostream>
#include "Device.h"
#include "RayTracing.h"
#include <assert.h>
#include "Sphere.h"
#include "SphereCreator.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void raytracing_GM(uchar4* ptrDevPixels, uint w, uint h, float t, int nbSphere, Sphere* ptrDevTabSphere);
extern __global__ void raytracing_CM(uchar4* ptrDevPixels, uint w, uint h, float t);
extern __global__ void raytracing_SM(uchar4* ptrDevPixels, uint w, uint h, float t, int nbSphere, Sphere* ptrDevTabSphere);

extern __host__ void uploadGPU(Sphere* SphereTab);
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

RayTracing::RayTracing(const Grid& grid, uint w, uint h, float dt, int nbSphere) :
	Animable_I<uchar4>(grid, w, h, "RayTracing_Cuda_RGBA_uchar4_Jeanneret_cyril"), i(0)
    {

    // Inputs
    this->dt = dt;

    // Tools
    this->t = 0; // protected dans Animable

    // Tools
    this->nbSphere = nbSphere;
    this->sizeOctetSpheres = sizeof(Sphere) * nbSphere;

    SphereCreator sphereCreator = SphereCreator(nbSphere, w, h);
    Sphere* ptrTabSphere = sphereCreator.getTabSphere();

    //GM transfert
    toGM(ptrTabSphere);

    //CM transfert
    toCM(ptrTabSphere);
    }

RayTracing::~RayTracing()
    {
    // rien
    Device::free(ptrDevTabSphere);
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */

void RayTracing::toCM(Sphere* ptrTab)
    {
    uploadGPU(ptrTab);
    }

void RayTracing::toGM(Sphere* ptrTab)
    {
    Device::malloc(&ptrDevTabSphere, sizeOctetSpheres);
    Device::memclear(ptrDevTabSphere, sizeOctetSpheres);
    Device::memcpyHToD(ptrDevTabSphere, ptrTab, sizeOctetSpheres);

    }

void RayTracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    Device::lastCudaError("RayTracing rgba uchar4 (before kernel)"); // facultatif, for debug only, remove for release

    // TODO lancer le kernel avec <<<dg,db>>>
    // le kernel est importer ci-dessus (ligne 19)

    if (i % 3 == 0)
	{
    raytracing_GM<<<dg,db>>>(ptrDevPixels, w, h, t, this->nbSphere, this->ptrDevTabSphere);
    }
else if (i % 3 == 1)
    {
raytracing_CM<<<dg,db>>>(ptrDevPixels, w, h, t);
}
else if (i % 3 == 2)
{
raytracing_SM<<<dg,db, this->sizeOctetSpheres>>>(ptrDevPixels, w, h, t, this->nbSphere, this->ptrDevTabSphere);
}
this->i++;

Device::lastCudaError("RayTracing rgba uchar4 (after kernel)"); // facultatif, for debug only, remove for release
}

/**
 * Override
 * Call periodicly by the API
 */
void RayTracing::animationStep()
{
t += dt;
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

