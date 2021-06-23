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
void AnalizadorLandmarks::setLandmarks(const vector<Point2f> &lm)
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
inline const float AnalizadorLandmarks::calcularAngulo(const Point2f &a, const Point2f &b)
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
inline const float AnalizadorLandmarks::calcularPendiente(const Point2f &a, const Point2f &b)
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
//cout <<"rotacion: "<<this->rotacion<<"\t"<<"izq original: "<<this->landmarks[0]<<"\t";
//cout<<"izq rotado: "<<this->landmarksNorm[0]<<"\t"<<"der orig: "<<this->landmarks[16]<<"\t"<< "der modif: "<<this->landmarksNorm[16]<<endl;
}

/**
 * @brief Funcion que calcula la asimetria entre ambos lados de la cara
 * 
 * @return const float 
 */
const float AnalizadorLandmarks::calcularAsimetria()
{
	//Estoy usando un float, podria ser un vector y luego sumar los puntos
	//Los valores estan elegidos un poco "a ojo"
	this->asimetria=1;
	// f15:Maximo valor de cocientes entre puntos externos de ojos y centro de boca: (F y G en el paper)
	float F=norm(landmarksNorm[37]-landmarksNorm[58]);
	float G=norm(landmarksNorm[46]-landmarksNorm[58]);
	this->asimetria*=calcularMax(F/G,G/F);
	
	// f16: Maximo valor entre cociente de distancias de labios inferior(Pl y Ql en el paper)
	float Pl=norm(landmarksNorm[50]-landmarksNorm[60]);
	float Ql=norm(landmarksNorm[54]-landmarksNorm[56]);
	this->asimetria*=calcularMax(Pl/Ql,Ql/Pl);

	// f17: Maximo valor entre cociente de distancias de labios superior?(Pu y Qu en el paper)
	float Pu=norm(landmarksNorm[51]-landmarksNorm[59]);
	float Qu=norm(landmarksNorm[53]-landmarksNorm[57]);
	this->asimetria*=calcularMax(Pu/Qu,Qu/Pu);

	// Maximo valor de cocientes entre puntos superiores de quijada y comisuras de labios
	float d1=norm(landmarksNorm[1]-landmarksNorm[49]);
	float d2=norm(landmarksNorm[17]-landmarksNorm[55]);
	this->asimetria*=calcularMax(d1/d2,d2/d1);
	return this->asimetria;
}

/**
 * @brief Devuelve el maximo entre dos valores
 * 
 * @param a 
 * @param b 
 * @return const float 
 */
inline const float AnalizadorLandmarks::calcularMax(const float &a, const float &b)
{
	if (a>b)
	{
		return a;
	}
	else
	{
		return b;
	}
	
}