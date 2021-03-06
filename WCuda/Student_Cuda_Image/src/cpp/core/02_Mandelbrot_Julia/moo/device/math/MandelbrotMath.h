#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_GPU.h"
#include "ColorTools_GPU.h"
using namespace gpu;

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ MandelbrotMath(uint n) :
		calibreur(Interval<float>(0, n), Interval<float>(0, 1))
	    {
	    this->n = n;
	    }

	// constructeur copie automatique car pas pointeur dans
	//	DamierMath
	// 	calibreur
	// 	IntervalF

	__device__ virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__ void colorXY(uchar4* ptrColor, float x, float y, float t)
	    {
	   	    float z = f(x, y, t);
	   	    calibreur.calibrer(z);
	   	    float hue01 = z;
	   	    if ( z == 0){
	   		ptrColor ->x = 0;
	   		ptrColor ->y = 0;
	   		ptrColor ->z = 0;
	   	    }else{
	   	    ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color
	   	    }

	   	    ptrColor->w = 255; // opaque
	   	    }

    private:

	__device__ float f(float x, float y, float t)
	    {
	    float a0 = 0;
	    float b0 = 0;
	    float aCopy = 0;
	    //black
	    for (int k = 0; k <= t; k++)
		{
		if (((a0 * a0) + (b0 * b0)) > 4)
		    {
		    return k; // condition sortie HSB TROUVER
		    }
		aCopy = a0;
		// = la hue donc le retunr ici égale a noir si explosion
		// couleur si non
		a0 = ((a0 * a0) - (b0 * b0)) + x;
		b0 = 2 * aCopy * b0 + y;
		}
	    return 0;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	uint n;

	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
