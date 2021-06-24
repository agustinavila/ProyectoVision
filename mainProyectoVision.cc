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
#include "analizadorsimetria.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	char ch = 0;
	AnalizadorSimetria analizador;
	Mat frame;
	cout << "Presione q para finalizar" << endl;
	while (ch != 'q' && ch != 'Q')
	{ 
		analizador.step();
		frame=analizador.getFrame();
		imshow("feeder", frame);
		ch = waitKey(1);
	}
	return 0;
}