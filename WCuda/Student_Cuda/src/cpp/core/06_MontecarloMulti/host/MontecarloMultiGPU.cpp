#include "MontecarloMultiGPU.h"
#include <cmath>
#include <iostream>
#include "Device.h"
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

using std::cout;
using std::endl;

MonteCarloMultiGPU::MonteCarloMultiGPU(const Grid& grid, int nbSamples, float hauteur, float tolerance)
    {
    this->tolerance = tolerance;
    this->pi = 0;
    this->grid = grid;
    this->nbSamples = nbSamples;
    this->hauteur = hauteur;
    }

MonteCarloMultiGPU::~MonteCarloMultiGPU()
    {

    }

float MonteCarloMultiGPU::run()
    {

    int nbDevices = Device::getDeviceCount();
    int nbSamplesPerGPU = nbSamples / nbDevices;

    int r = 0;
    auto t1 = Clock::now();

#pragma omp parallel for reduction(+ : r)
    for(int id = 0; id < nbDevices; id++)
	{
	Device::setDevice(id);
	MonteCarlo m(grid, nbSamplesPerGPU, hauteur, tolerance);
	m.run();
	r = m.getNbSuccessSamples();
	}


    auto t2 = Clock::now();

    std::cout << "Performance Montecarlo MultiGPU : "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
              << " nanoseconds" << std::endl;

    cout << "R : " << r << endl;

    r /= nbDevices;
    pi =  4.0 * r * hauteur / (nbSamplesPerGPU);
    return pi;
    }
