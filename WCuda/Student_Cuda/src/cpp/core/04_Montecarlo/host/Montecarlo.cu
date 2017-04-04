#include <iostream>

#include "Device.h"
#include "Montecarlo.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void Montecarlo(float* ptrGMResultat, int nbSlice, float* ptrGenerator);

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
 |*		Constructeur			*|
 \*-------------------------------------*/

Montecarlo::Montecarlo(const Grid& grid, float* ptrGMResultat, int nbSlice, float* ptrGenerator) :
	ptrGMResultat(ptrGMResultat), nbSlice(nbSlice), ptrGenerator(ptrGenerator)
    {
    this->sizeOctet = nbSlice * sizeof(float); // octet
    // MM
	{

	// MM (malloc Device)
	    {
	    Device::malloc(&ptrGMDevResultat, sizeOctet);
	    Device::malloc(&ptrGenerator, sizeOctet);

	    Device::memclear(ptrGMDevResultat, sizeOctet);
	    Device::memclear(ptrGenerator, sizeOctet);
	    }

	// MM (copy Host->Device)
	    {
	    Device::memcpyHToD(ptrGMDevResultat, ptrGMResultat, sizeOctet);
	    Device::memcpyHToD(ptrDevGenerator, ptrGenerator, sizeOctet);
	    }

	Device::lastCudaError("montecarlo MM (end allocation)"); // temp debug, facultatif
	}

    // Grid
	{
	this->dg = grid.dg;
	this->db = grid.db;
	}
    }

Montecarlo::~Montecarlo(void)
    {
    //MM (device free)
	{
	Device::free(ptrGMDevResultat);
	Device::free(ptrDevGenerator);
	Device::lastCudaError("AddVector MM (end deallocation)"); // temp debug, facultatif
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void Montecarlo::run()
    {
    Device::lastCudaError("slice (before)"); // temp debug
    Montecarlo<<<dg,db>>>(ptrGMResultat, nbSlice); // assynchrone
    Device::lastCudaError("slice (after)"); // temp debug

    Device::synchronize(); // Temp,debug, only for printf in  GPU

    // MM (Device -> Host)
	{
	Device::memcpyDToH(ptrGMResultat, ptrGMDevResultat, sizeOctet); // barriere synchronisation implicite
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
