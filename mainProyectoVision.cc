/**
 * @file mainProyectoVision.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */



// includes
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/video/video.hpp>
#include <opencv2/core/core.hpp>
#include "feeder.h"
#include "webcamfeeder.h"
#include "framelogger.h"

using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
//Definiciones de propiedades
    char ch = 0;
	Mat frame;
//parseo de argumentos

//instanciacion de objetos
	Feeder *ptrFeeder;
	WebcamFeeder webcamFeeder;
	ptrFeeder = &webcamFeeder;
	FrameLogger logger;

//ejecutar las acciones / bucle
    cout << "Presione q para finalizar"<<endl;
	while (ch != 'q' && ch != 'Q')
    {
		frame=ptrFeeder->getFrame();
		logger.log(frame);	//Guarda frames, segun parametros podria desactivarse o no
		imshow("feeder",frame); 
		ch = waitKey(1);
	}
//RECONOCER SIGNALS PARA PARAR EJECUCION
return 0;
}