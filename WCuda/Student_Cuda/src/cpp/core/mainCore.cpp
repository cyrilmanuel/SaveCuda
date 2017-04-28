#include <iostream>
#include <stdlib.h>


using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern bool useHello(void);
extern bool useAddVecteur(void);
extern bool useSlice(void);
extern bool useMontecarlo(void);
extern bool useMontecarloMultiGPU(void);
extern bool useHistogram(void);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainCore();

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainCore()
    {
    bool isOk = true;
//    isOk &= useHello();
   // isOk &=useAddVecteur();
//    isOk &=useSlice();
//    isOk &=useMontecarlo();
//    isOk &=useMontecarloMultiGPU();
    isOk &=useHistogram();

    cout << "\nisOK = " << isOk << endl;
    cout << "\nEnd : mainCore" << endl;

    cout << "Press Enter to quit!"<<endl;
    getchar();
    return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

