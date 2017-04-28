#pragma once

#include "Montecarlo.h"

class MonteCarloMultiGPU
    {
    public:
	MonteCarloMultiGPU(const Grid& grid, int nbSamples, float hauteur = 4.0, float tolerance = 0.001);
	virtual ~MonteCarloMultiGPU();

	float run();

    private:
	Grid grid;
	float tolerance;
	int nbSamples;
	float hauteur;
	float pi;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
