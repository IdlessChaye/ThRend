#pragma once
#ifndef FURNACE_TEST_LOADER
#define FURNACE_TEST_LOADER

#include <string>
#include <vector>
#include <glm.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>


using namespace std;
using namespace glm;

unsigned const int LUT_WIDTH = 64;
unsigned const int LUT_HEIGHT = 64;
float** furnaceEs;
float* furnaceEavgs;

float getFurnaceTestF(float ndotv, float roughness)
{
	int i = roughness * 1.0f * (LUT_HEIGHT - 0.5f);
	int j = ndotv * 1.0f * (LUT_WIDTH - 0.5f);
	return furnaceEs[i][j];
}

float getFurnaceTestFavg(float roughness)
{
	int i = roughness * 1.0f * (LUT_HEIGHT - 0.5f);
	return furnaceEavgs[i];
}


void loadFurnaceTestFs(std::string filename)
{
	//LUT_WIDTH = width;
	//LUT_HEIGHT = height;
	furnaceEs = new float* [LUT_HEIGHT];//动态申请二维数组nxm
	for (int i = 0; i < LUT_HEIGHT; ++i)
	{
		furnaceEs[i] = new float[LUT_WIDTH];
	}
	furnaceEavgs = new float[LUT_HEIGHT];

	ifstream file(filename.c_str());
	if (!file)
	{
		std::cout << "FURNACE TEST FAILED!\n";
		return;
	}

	int i = -1, j = 0;
	std::cout << "Loading furnace Test " << filename << " \n";
	string line;
	while (getline(file, line))
	{
		if (j % LUT_WIDTH == 0)
		{
			j = 0;
			i++;

			if (i == LUT_HEIGHT)
			{
				break;
			}
		}

		stringstream linestream(line);

		float ndotv, roughness, enegy;
		linestream >> ndotv;
		linestream >> roughness;
		linestream >> enegy;

		furnaceEs[i][j] = enegy;
		j++;
	}

	volatile float v = 0;
	for (int i = 0; i < LUT_HEIGHT; i++)
	{
		v = 0;
		for (int j = 0; j < LUT_WIDTH; j++)
		{
			v += furnaceEs[i][j] * j / (LUT_WIDTH - 1) / (LUT_WIDTH);
		}
		v *= 2;
		//furnaceEavgs.push_back(value);
		furnaceEavgs[i] = v;
	}

	std::cout << "FurnaceTest loaded succesfully \n";
}


#endif

