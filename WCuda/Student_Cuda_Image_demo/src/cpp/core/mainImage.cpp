#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Device.h"
#include "cudaTools.h"

#include "RipplingProvider.h"
#include "MandelbrotProvider.h"
#include "RayTracingProvider.h"

#include "Settings_GPU.h"
#include "Viewer_GPU.h"
using namespace gpu;

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainImage(Settings& settings);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainImage(Settings& settings)
    {
    cout << "\n[Image] mode" << endl;

    GLUTImageViewers::init(settings.getArgc(), settings.getArgv()); //only once

    // ImageOption : (boolean,boolean) : (isSelection,isAnimation)
    ImageOption zoomable(true, true, true, true);
    ImageOption nozoomable(false);

    Viewer<RipplingProvider> rippling(nozoomable, 25, 25); // imageOption px py
    //taille 450*450
    rippling.setSize(450, 450);
    rippling.setPosition(0, 0);

    Viewer<MandelbrotProvider>mandelbrot(zoomable, 25, 25); // imageOption px py
    mandelbrot.setPosition(280, 100);
    mandelbrot.setSize(450, 450);

    Viewer<RayTracingProvider> raytracing(nozoomable, 25, 25); // imageOption px py
    raytracing.setSize(450, 450);
    raytracing.setPosition(400, 200);

    // Common
    GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    cout << "\n[Image] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

