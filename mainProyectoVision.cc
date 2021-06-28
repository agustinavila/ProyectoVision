/**
 * @file mainProyectoVision.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Archivo con un programa ejemplificando el uso de la clase AnalizadorSimetria
 * @version 0.1
 * @date 2021-06-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// includes
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "analizadorsimetria.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	char ch = 0;

	float asimetria;
	std::vector<Landmarks> landmarks;
	AnalizadorSimetria analizador;
	Mat frame;
	cout << "Presione q para finalizar" << endl;
	while (ch != 'q' && ch != 'Q')
	{
		frame = analizador.step();
		landmarks = analizador.getLandmarks();
		if (!landmarks.front().vacio){
		asimetria=analizador.getAsimetria();
		putText(frame, "Rostro detectado!", landmarks.front().menton.back(), 2, 1, Scalar(255, 0, 0));
		cout<< "Asimetria: "<< asimetria <<endl;
		}
		imshow("feeder", frame);
		ch = waitKey(1);
		if ((ch=='o') || (ch=='O')){
			analizador.setExtractor(OPENCV);
			ch=0;
		}
		else if ((ch=='d') || (ch=='D')){
			analizador.setExtractor(DLIB);
			ch=0;
		}
		else if ((ch=='w') || (ch=='W')){
			analizador.setFeeder(WEBCAMFEEDER);
			ch=0;
		}
		else if ((ch=='k') || (ch=='K')){
			analizador.setFeeder(KINECTFEEDER);
			ch=0;
		}
		else if ((ch=='v') || (ch=='V')){
			analizador.setFeeder(VIDEOFEEDER);
			ch=0;
		}
	}
	return 0;
}