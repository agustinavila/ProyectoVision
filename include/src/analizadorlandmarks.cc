/**
 * @file analizadorlandmarks.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Implementacion de la clase AnalizadorLandmarks
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "../analizadorlandmarks.h"

/**
 * @brief Construye un nuevo objeto de la clase Analizador Landmarks:: Analizador Landmarks
 * 
 */
AnalizadorLandmarks::AnalizadorLandmarks()
{
	cout << "constructor del analizador" << endl;
}

/**
 * @brief Destruye el objeto de la clase Analizador Landmarks:: Analizador Landmarks
 * 
 */
AnalizadorLandmarks::~AnalizadorLandmarks()
{
	cout << "destructor del analizador" << endl;
	// Deberia eliminar los vectores?
}

/**
 * @brief Actualiza los landmarks
 * 
 * @param vector<Point2f>lm 
 */
void AnalizadorLandmarks::setLandmarks(vector<Point2f> lm)
{
	this->landmarks=lm;
}

/**
 * @brief Calcula el angulo entre dos puntos a y b
 * 
 * @param a 
 * @param b 
 * @return float 
 */
inline float AnalizadorLandmarks::calcularAngulo(Point2f a, Point2f b)
{
	if ((a.x-b.x)!=0)
	{
	return atan((a.y-b.y)/(a.x-b.x))*180/CV_PI;
	}
	else return 0;
}

/**
 * @brief Calcula la pendiente entre dos puntos
 * 
 * @param a 
 * @param b 
 * @return float 
 */
inline float AnalizadorLandmarks::calcularPendiente(Point2f a, Point2f b)
{
	return abs((a.x-b.x)/(a.y-b.y));
}

/**
 * @brief Normaliza los landmarks, leyendo 'landmarks' y actualizando 'landmarksNorm'
 * 
 */
void AnalizadorLandmarks::normalizarLandmarks()
{
Mat matrizRotacion;
this->landmarksNorm.clear();
this->rotacion=calcularAngulo(this->landmarks[0],this->landmarks[16]);
matrizRotacion=getRotationMatrix2D(this->landmarks[0],this->rotacion,1);
transform(this->landmarks,this->landmarksNorm,matrizRotacion);
cout <<"rotacion: "<<this->rotacion<<"\t"<<"izq original: "<<this->landmarks[0]<<"\t";
cout<<"izq rotado: "<<this->landmarksNorm[0]<<"\t"<<"der orig: "<<this->landmarks[16]<<"\t"<< "der modif: "<<this->landmarksNorm[16]<<endl;
}

/**
 * @brief Funcion que calcula la asimetria entre ambos lados de la cara
 * 
 */
void AnalizadorLandmarks::calcularAsimetria()
{

}
