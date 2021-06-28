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


/**
 * @brief Programa de ejemplo del uso de la clase AnalizadorSimetria
 * 
 * @details Este es un programa de ejemplo mostrando algunas de las funcionalidades de la clase.
 * Se puede cambiar durante ejecucion el tipo de feeder y de extractor de landmarks sin problemas.
 * No se agregó la posibilidad de habilitar o deshabilitar el registro de video o landmarks, pero seria 
 * muy sencillo de implementar los metodos enableVideoLog, disableVideoLog, etc.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
	cout << "Programa de muestra de la clases Analizador Simetria" <<endl;
	cout << "El programa lee la configuración del archivo 'config.yaml'"<<endl<<endl;
	cout << "Presionando la tecla 'o', se utiliza el extractor de landmarks de openCV"<<endl;
	cout << "Presionando la tecla 'd', se utiliza el extractor de landmarks de dlib"<<endl;
	cout << "Presionando la tecla 'w', se intenta obtener imágenes de una webcam"<<endl;
	cout << "Presionando la tecla 'k', se intenta obtener imágnees de una kinect"<<endl;
	cout << "Presionando la tecla 'v', se intenta abrir un archivo de video (por defecto, 'video.avi') "<<endl;
	char ch = 0;
	float asimetria;
	std::vector<Landmarks> landmarks;
	AnalizadorSimetria analizador(string("config.yaml"));
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