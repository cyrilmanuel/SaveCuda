#include <iostream>
#include "Grid.h"
#include "Device.h"
#include <climits>

using std::cout;
using std::endl;
#define PI 3.14159265358979323846264338327950288419716939937510

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

#include "MontecarloMultiGPU.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarloMultiGPU();

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarloMultiGPU()
    {
    int n = INT_MAX>>2;  //number of samples, here max(unsigned long long int) / 4
    float targetHeight = 4.0;  //height of target
    float tolerance = 0.01;  //tolerance between calculated pi and it's real value

    // Grid cuda
    int mp = Device::getMPCount();
    int coreMP = Device::getCoreCountMP();

    dim3 dg = dim3(24, 1, 1);  		// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
    dim3 db = dim3(1024, 1, 1);   	// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
    Grid grid(dg, db);

    MonteCarloMultiGPU montecarlo(grid, n, targetHeight, tolerance); // on passse la grille à AddVector pour pouvoir facilement la faire varier de l'extérieur (ici) pour trouver l'optimum
    float pi = montecarlo.run();

    cout << "Exact Pi : \t" << PI << endl;
    cout << "Estimation : \t" << pi << endl;

    return true;
    }
