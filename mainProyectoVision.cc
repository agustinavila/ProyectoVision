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
	AnalizadorSimetria *analizador = new AnalizadorSimetria(new WebcamFeeder, new ExtractorLandmarksDlib);
	Mat frame;
	cout << "Presione q para finalizar" << endl;
	while (ch != 'q' && ch != 'Q')
	{ 
		analizador->step();
		frame=analizador->getFrame();
		landmarks=analizador->getLandmarks();
		putText(frame, "Rostro detectado!", landmarks.front().menton.back(), 1, 1, Scalar(255, 0, 0));
		// drawContours(frame, landmarks[0].ojoDer, -1, Scalar(255, 0, 0));
		imshow("feeder", frame);
		ch = waitKey(1);
	}
	ch=0;
	analizador->setExtractor(new ExtractorLandmarksOpenCV);
		while (ch != 'q' && ch != 'Q')
	{ 
		analizador->step();
		frame=analizador->getFrame();
		landmarks=analizador->getLandmarks();
		// putText(frame, "Rostro detectado!", *landmarks[0].menton.end(), 1, 1, Scalar(255, 0, 0));
		// drawContours(frame, landmarks[0].ojoDer, -1, Scalar(255, 0, 0));
		imshow("feeder", frame);
		ch = waitKey(1);
	}
	return 0;
}