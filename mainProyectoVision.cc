/**
 * @file mainProyectoVision.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Archivo main del proyecto
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
	std::vector<Landmarks> landmarks;
	AnalizadorSimetria analizador;// = new AnalizadorSimetria;
	analizador.setFeeder(new KinectFeeder);
	analizador.setExtractor(new ExtractorLandmarksOpenCV);
	Mat frame;
	cout << "Presione q para finalizar" << endl;
	while (ch != 'q' && ch != 'Q')
	{
		cout <<"1...";
		frame = analizador.step();
		cout<<"7..."<<endl;
		landmarks = analizador.getLandmarks();
		if (!landmarks.front().vacio){
		putText(frame, "Rostro detectado!", landmarks.front().menton.back(), 1, 1, Scalar(255, 0, 0));
		}
		imshow("feeder", frame);
		ch = waitKey(1);
	}
	return 0;
}