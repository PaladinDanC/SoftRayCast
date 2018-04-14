#pragma once
#include <math.h>
#include <iostream>

struct Matrix
{
	float points[4][4];
};

struct Vertex
{
	float xyzw[4];
	
	unsigned int color;
};

struct RotateMatrixTwoxTwo
{
	float rotater[4];
};

struct WorldMatrixID
{
	float ID[4][4];
};

