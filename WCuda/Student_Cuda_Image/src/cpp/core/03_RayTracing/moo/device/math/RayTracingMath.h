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
	    float distMinSphere = 10000;
	    float hueSphereProche = -1000;
	    float brightnessSphereProche = -100;


	    // regarder la sphere au dessu
	    float2 positionXYsol;
	    positionXYsol.x = i;
	    positionXYsol.y = j;

	    for (int z = 0; z < nbSphere; z++)
		{
		    //parcour le tableau de sphere
		    Sphere sphereActuel = ptrDevTabSphere[z];
		    float hcarre = sphereActuel.hCarre(positionXYsol);

		    //test si en dessous.
		    if(sphereActuel.isEnDessous(hcarre)){

			float dz = sphereActuel.dz(hcarre);
			float dist = sphereActuel.distance(dz);

			if (dist < distMinSphere){
			    distMinSphere = dist;
			    hueSphereProche = sphereActuel.hue(t);
			    brightnessSphereProche = sphereActuel.brightness(dz);
			}
		    }
		}

	    //application de la couleur
	    if ( hueSphereProche < 0){
	    	   		ptrColor ->x = 0;
	    	   		ptrColor ->y = 0;
	    	   		ptrColor ->z = 0;
	    	   	    }else{
	    	   	    ColorTools::HSB_TO_RVB(hueSphereProche,1.f,brightnessSphereProche, ptrColor); // update color
	    	   	    }
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
