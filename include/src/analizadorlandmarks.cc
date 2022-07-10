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

AnalizadorLandmarks::AnalizadorLandmarks()
{
	cout << "Construyendo el analizador de landmarks..." << endl;
}

AnalizadorLandmarks::~AnalizadorLandmarks()
{
	cout << "destructor del analizador de landmarks" << endl;
}

void AnalizadorLandmarks::setLandmarks(const vector<Landmarks> &lm)
{
	this->landmarks = lm;
}

inline const float AnalizadorLandmarks::calcularAngulo(const Point2f &a, const Point2f &b)
{
	if ((a.x - b.x) != 0)
	{
		return atan((a.y - b.y) / (a.x - b.x)) * 180 / CV_PI;
	}
	else
		return 0;
}

inline const float AnalizadorLandmarks::calcularPendiente(const Point2f &a, const Point2f &b)
{
	return abs((a.x - b.x) / (a.y - b.y));
}

void AnalizadorLandmarks::normalizarLandmarks()
{
	Mat matrizRotacion;
	landmarksNorm.clear();
	if (!landmarks.front().empty())
	{
		std::vector<Landmarks>::const_iterator cii;
		Landmarks l, lNorm;
		for (cii = landmarks.begin(); cii != landmarks.end(); cii++)
		{
			l = *cii;
			lNorm.rotacion = calcularAngulo(l.menton.front(), l.menton.back());
			matrizRotacion = getRotationMatrix2D(l.menton.front(), lNorm.rotacion, l.escala);
			transform(l.menton, lNorm.menton, matrizRotacion);
			transform(l.cejaIzq, lNorm.cejaIzq, matrizRotacion);
			transform(l.cejaDer, lNorm.cejaDer, matrizRotacion);
			transform(l.ojoIzq, lNorm.ojoIzq, matrizRotacion);
			transform(l.ojoDer, lNorm.ojoDer, matrizRotacion);
			transform(l.nariz, lNorm.nariz, matrizRotacion);
			transform(l.boca, lNorm.boca, matrizRotacion);
			landmarksNorm.push_back(lNorm);
		}
	}
	else
		landmarksNorm.front().vacio = 1;
}

const float AnalizadorLandmarks::calcularAsimetria()
{
	float asimetria = 1;
	if (!landmarksNorm.front().empty())
	{
		float F = norm(landmarksNorm.front().ojoIzq.at(3) - landmarksNorm.front().boca.at(3));
		float G = norm(landmarksNorm.front().ojoDer.at(3) - landmarksNorm.front().boca.at(3));
		asimetria *= calcularMax(F / G, G / F);

		// f16: Maximo valor entre cociente de distancias de labios inferior(Pl y Ql en el paper)
		float Pl = norm(landmarksNorm.front().boca.at(1) - landmarksNorm.front().boca.at(11));
		float Ql = norm(landmarksNorm.front().boca.at(5) - landmarksNorm.front().boca.at(7));
		asimetria *= calcularMax(Pl / Ql, Ql / Pl);

		// f17: Maximo valor entre cociente de distancias de labios superior?(Pu y Qu en el paper)
		float Pu = norm(landmarksNorm.front().boca.at(2) - landmarksNorm.front().boca.at(10));
		float Qu = norm(landmarksNorm.front().boca.at(4) - landmarksNorm.front().boca.at(8));
		asimetria *= calcularMax(Pu / Qu, Qu / Pu);

		// Maximo valor de cocientes entre puntos superiores de quijada y comisuras de labios
		float d1 = norm(landmarksNorm.front().menton.front() - landmarksNorm.front().boca.front());
		float d2 = norm(landmarksNorm.front().menton.back() - landmarksNorm.front().boca.at(9));
		asimetria *= calcularMax(d1 / d2, d2 / d1);
	}

	return asimetria;
}

inline const float AnalizadorLandmarks::calcularMax(const float &a, const float &b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}