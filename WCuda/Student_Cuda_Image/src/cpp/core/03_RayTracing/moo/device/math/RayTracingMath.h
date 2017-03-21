#pragma once

#include <math.h>
#include "MathTools.h"
#include "Sphere.h"

#include "ColorTools_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RayTracingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ RayTracingMath(int nbSphere, Sphere* ptrDevTabSphere)
	    {
	this->nbSphere = nbSphere;
	   this->ptrDevTabSphere = ptrDevTabSphere;
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	__device__
	    virtual ~RayTracingMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:


	__device__
	void colorIJ(uchar4* ptrColor, int i, int j, float t)
	    {
	   // todo
	    // regarder la sphere au dessu

	// pour sa convertir i j du pixel en coordonnée x y
	// ensuite vérifier si celle-ci sont présente sur une des spheres du tableau de sphere


	    ptrColor->w = 255; // opaque
	    }

    private:


	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	//input
	Sphere* ptrDevTabSphere;
	int nbSphere;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
