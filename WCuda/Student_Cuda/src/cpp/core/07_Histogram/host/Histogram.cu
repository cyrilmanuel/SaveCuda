#include <iostream>
#include <cmath>

#include "Device.h"

#include "DataCreator.h"
#include "Histogram.h"

using std::cout;
using std::endl;

extern __global__ void histoPerso(int* ptrDevData, int max, int size);

Histogram::Histogram(const Grid& grid, int dataMax)
    {
    // Grid
	{
	this->dg = grid.dg;
	this->db = grid.db;
	}

    //Data
    this->dataMax = dataMax;
    DataCreator dataCreator(dataMax);
    data = dataCreator.getTabData();
    dataSize = dataCreator.getLength();

    //Threads
    this->nbThreads = grid.threadCounts();

    //GM
    sizeOctet = dataSize * sizeof(int);

    //SM
    this->sizeSM = dataMax * sizeof(int);

    //output
    histogram = nullptr;

    // MM
	{
	// MM (malloc Device)
	    {
	    Device::malloc(&ptrDevData, sizeOctet);
	    Device::memclear(ptrDevData, sizeOctet);
	    Device::memcpyHToD(ptrDevData, data, sizeOctet);
	    }
	}
    }

Histogram::~Histogram(void)
    {
    //MM (device free)
	{
	Device::free(ptrDevData);
	}
    }

int* Histogram::run()
    {
    Device::lastCudaError("Histogram (before)"); // temp debug
    histoPerso<<<dg, db, sizeSM>>>(ptrDevData, dataMax, dataSize); // assynchrone
    Device::lastCudaError("Histogram (after)"); // temp debug

    int* result = new int[dataMax]();

    Device::memcpyDToH(result, ptrDevData, dataMax * sizeof(int)); // barriere synchronisation implicite
    Device::memclear(ptrDevData, sizeOctet);

    histogram = result;
    return histogram;
    }