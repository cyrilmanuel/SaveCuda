#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	MandelbrotMath(uint n) :
		calibreur(Interval<float>(0, 120), Interval<float>(0, 1))
	    {
	    this->n = n;
	    }

	// constructeur copie automatique car pas pointeur dans
	//	DamierMath
	// 	calibreur
	// 	IntervalF

	virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void colorXY(uchar4* ptrColor, float x, float y, float t)
	    {
	    float z = f(x, y, t);

	    calibreur.calibrer(z);
	    float hue01 = z;

	    ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color

	    ptrColor->w = 255; // opaque
	    }

    private:

	float f(float x, float y, float t)
	    {
	    float a0 = 0;
	    float b0 = 0;
	    float aCopy = 0;

	    for (int k=0; k<=N; K++)
		{
		  if((a0*a0) + (b0*b0) >4)
		      {
			  <// condition sortie HSB TROUVER
		      }
		  float aCopy = a0;
		  		// = la hue donc le retunr ici égale a noir si explosion
		  		// couleur si non
		  a0 = ((a0*a0)-(b0*b0))+x;
		  b0 = 2*aCopy*b0+y
		}
	    //black
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
