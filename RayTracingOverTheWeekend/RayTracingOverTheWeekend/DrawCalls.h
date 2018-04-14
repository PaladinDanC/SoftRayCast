#pragma once
#pragma once
#include <iostream>
#include <math.h>
#include "includes.h"

unsigned int rasterArray[numofPixs];
unsigned int zBuffer[numofPixs];
using namespace std;

static void PlotPixel(float x, float y, unsigned int color)
{
	if (TwoDtoOneD(x, y, WWidth) > numofPixs | TwoDtoOneD(x, y, WWidth) < 0)
		return;
	else {
		rasterArray[TwoDtoOneD(x, y, WWidth)] = color;
	}
}


void DansParametric(Vertex X, Vertex Y, unsigned int color)
{

	X.xyzw[0] = fromNormtoRasterX(X.xyzw[0]);
	X.xyzw[1] = fromNormtoRasterY(X.xyzw[1]);
	Y.xyzw[0] = fromNormtoRasterX(Y.xyzw[0]);
	Y.xyzw[1] = fromNormtoRasterY(Y.xyzw[1]);

	float dltaX = X.xyzw[0] - Y.xyzw[0];
	float dltaY = X.xyzw[1] - Y.xyzw[1];
	float longest = rtrnMax(abs(dltaX), abs(dltaY));
	for (float i = 0; i < longest; i++)
	{
		float ratio = (float)(i / longest);
		int currX = LERP(X.xyzw[0], Y.xyzw[0], ratio);
		int currY = LERP(X.xyzw[1], Y.xyzw[1], ratio);
		PlotPixel(currX, currY, color);
		/*PlotPixel(currY, currX, 0x00FFFFFF);*/

	}
}



void Draw(const Vertex &start, const Vertex &end, unsigned int color)
{

	Vertex copy_start = start;
	Vertex copy_end = end;

	if (VertexShader)
	{
		VertexShader(copy_start);
		VertexShader(copy_end);
	}


	DansParametric(copy_start, copy_end, color);
}