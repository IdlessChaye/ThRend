#ifndef COLORMP
#define COLORMP

#include <string>
#include <vector>
#include <glm.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
using namespace glm;

typedef struct{
	int r;
	int g;
	int b;
} colorInt;

vector<vec3> colormap;

//min and max temperatures of the colormap
float tmin;
float tmax;
//min and max temperatures of the reflection colormap
float tmin_reflected ;
float tmax_reflected ;

void loadColormapFromFile(string file){
	std::ifstream ifs(file);
	glm::vec3 c;

	colormap.clear();
	while (ifs >> c.x >> c.y >> c.z) {
		colormap.push_back(c);
	}
	std::cout << "Colormap loaded succesfully...\n";
}


//get temp with tmin and tmax
int getColor(float t){
	float tt = (t - 273.15);

	if (tt < tmin)
		tt = tmin;
	else if (tt > tmax)
		tt = tmax;

	int ind = floor(((tt - tmin) / (tmax - tmin))*(colormap.size() - 1));
	return ind;
}

//get temp with other values (for reflections)
int getColor2(float t){
	float tt = (t - 273.15);

	if (tt < tmin_reflected)
		tt = tmin_reflected;
	else if (tt > tmax_reflected)
		tt = tmax_reflected;

	int ind = floor(((tt - tmin_reflected) / (tmax_reflected - tmin_reflected))*(colormap.size() - 1));
	return ind;
}

int maxttt = 0;
int max(int a, int b)
{
	return a > b ? a : b;
}

vec3 getValue(float t)
{
	float tt = (t - 273.15);
	float minTemp = -10;
	float maxTemp = 30;
	float maxtt = 50;
	maxttt = max(maxttt, tt);
	float value = tt / maxtt;
	return vec3(value, value, value);
}

#endif

