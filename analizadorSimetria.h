/**
 * @file analizadorSimetria.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <vector>

class analizadorSimetria
{
private:
vector<vector<int>> landmarks;
	/* data */
public:
	analizadorSimetria(vector<vector<int>>& landmarks);
	~analizadorSimetria();
};
