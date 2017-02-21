#include "../02_Slice/00_pi_tools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiSequentiel_OK(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piSequentiel(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiSequentiel_OK(int n)
    {
    return isAlgoPI_OK(piSequentiel,  n, "Pi Sequentiel");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

double piSequentiel(int n)
    {
   //TODO
    return -1;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

