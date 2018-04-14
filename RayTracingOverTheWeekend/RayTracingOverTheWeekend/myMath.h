#pragma once
#include <math.h>
#include "allStructs.h"

static int TwoDtoOneD(int x, int y, int width)
{
	return (y*width + x);
};

static int ILE(int sX, float fX, int eX, int sY, float fY, int eY)
{
	return (((sY - eY)* fX) + ((eX - sX)*fY) + (sX* eY) - (sY*eX));
};

static float LERP(int sY, int Y, float ratio)
{
	return (sY + ratio*(Y - sY));
};

static float myRatio(int currNum, int maxNum)
{
	return (currNum / maxNum);
};

static unsigned int BlendTriColor(unsigned int matrix, unsigned int Y, float ratio) {

	int xA = ((matrix & 0xFF000000) >> 24);
	int xR = ((matrix & 0x00FF0000) >> 16);
	int xG = ((matrix & 0x0000FF00) >> 8);
	int xB = ((matrix & 0x000000FF));

	int yA = ((Y & 0xFF000000) >> 24);
	int yR = ((Y & 0x00FF0000) >> 16);
	int yG = ((Y & 0x0000FF00) >> 8);
	int yB = ((Y & 0x000000FF));



	float lerpA = LERP(xA, yA, ratio);
	float lerpR = LERP(xR, yR, ratio);
	float lerpG = LERP(xG, yG, ratio);
	float lerpB = LERP(xB, yB, ratio);





	unsigned int answer = 0x00000000;

	answer = answer | ((int)(lerpB));
	answer = answer | ((int)(lerpG) << 8);
	answer = answer | ((int)(lerpR) << 16);
	answer = answer | ((int)(lerpA) << 24);
	return answer;
}

static float fromNormtoRasterY(float Y) {
	float multiplier = 1 - Y;
	return(multiplier * (WWidth*AspectRatio /2));
}

static float fromNormtoRasterX(float matrix) {
	float multiplier = matrix + 1;
	return(multiplier * (WHeight*AspectRatio / 2));
}

static float fromRastertoNormY(float Y) {
	return (1 - (Y / (WWidth*AspectRatio / 2)));
}

static float fromRastertoNormX(float matrix) {
	return ((matrix / (WWidth*AspectRatio / 2)) - 1);
}

static int rtrnMax(float num1, float num2)
{
	if (num1 > num2)
		return num1;
	else
		return num2;

}

static Matrix SetIDMatrix()
{
	Matrix Identity;

	Identity.points[0][0] = 1;
	Identity.points[1][0] = 0;
	Identity.points[2][0] = 0;
	Identity.points[3][0] = 0;

	Identity.points[0][1] = 0;
	Identity.points[1][1] = 1;
	Identity.points[2][1] = 0;
	Identity.points[3][1] = 0;

	Identity.points[0][2] = 0;
	Identity.points[1][2] = 0;
	Identity.points[2][2] = 1;
	Identity.points[3][2] = 0;

	Identity.points[0][3] = 0;
	Identity.points[1][3] = 0;
	Identity.points[2][3] = 0;
	Identity.points[3][3] = 1;

	return Identity;
}

static void MultiplyVertexByMatrix(Vertex &vert, Matrix matrix) {
	Vertex vertx;
	vertx.xyzw[0] = (vert.xyzw[0] * matrix.points[0][0]) + (vert.xyzw[1] * matrix.points[1][0]) + (vert.xyzw[2] * matrix.points[2][0]) + (vert.xyzw[3] * matrix.points[3][0]);
	vertx.xyzw[1] = (vert.xyzw[0] * matrix.points[0][1]) + (vert.xyzw[1] * matrix.points[1][1]) + (vert.xyzw[2] * matrix.points[2][1]) + (vert.xyzw[3] * matrix.points[3][1]);
	vertx.xyzw[2] = (vert.xyzw[0] * matrix.points[0][2]) + (vert.xyzw[1] * matrix.points[1][2]) + (vert.xyzw[2] * matrix.points[2][2]) + (vert.xyzw[3] * matrix.points[3][2]);
	vertx.xyzw[3] = (vert.xyzw[0] * matrix.points[0][3]) + (vert.xyzw[1] * matrix.points[1][3]) + (vert.xyzw[2] * matrix.points[2][3]) + (vert.xyzw[3] * matrix.points[3][3]);
	vert = vertx;
}

static Matrix TranslationMatrix(float x, float y, float z)
{
	Matrix Translate;

	Translate.points[0][0] = 1.0;
	Translate.points[0][1] = 0.0;
	Translate.points[0][2] = 0.0;
	Translate.points[0][3] = 0.0;
	//
	Translate.points[1][0] = 0.0;
	Translate.points[1][1] = 1.0;
	Translate.points[1][2] = 0.0;
	Translate.points[1][3] = 0.0;
	//
	Translate.points[2][0] = 0.0;
	Translate.points[2][1] = 0.0;
	Translate.points[2][2] = 1.0;
	Translate.points[2][3] = 0.0;
	//
	Translate.points[3][0] = x;
	Translate.points[3][1] = y;
	Translate.points[3][2] = z;
	Translate.points[3][3] = 1.0;

	return Translate;
}

static Matrix MatrixMultMatrix(Matrix matrix, Matrix matrix1)
{
	Matrix multi;
	multi.points[0][0] = (matrix.points[0][0] * matrix1.points[0][0]) + (matrix.points[0][1] * matrix1.points[1][0]) + (matrix.points[0][2] * matrix1.points[2][0]) + (matrix.points[0][3] * matrix1.points[3][0]);
	multi.points[0][1] = (matrix.points[0][0] * matrix1.points[0][1]) + (matrix.points[0][1] * matrix1.points[1][1]) + (matrix.points[0][2] * matrix1.points[2][1]) + (matrix.points[0][3] * matrix1.points[3][1]);
	multi.points[0][2] = (matrix.points[0][0] * matrix1.points[0][2]) + (matrix.points[0][1] * matrix1.points[1][2]) + (matrix.points[0][2] * matrix1.points[2][2]) + (matrix.points[0][3] * matrix1.points[3][2]);
	multi.points[0][3] = (matrix.points[0][0] * matrix1.points[0][3]) + (matrix.points[0][1] * matrix1.points[1][3]) + (matrix.points[0][2] * matrix1.points[2][3]) + (matrix.points[0][3] * matrix1.points[3][3]);

	multi.points[1][0] = (matrix.points[1][0] * matrix1.points[0][0]) + (matrix.points[1][1] * matrix1.points[1][0]) + (matrix.points[1][2] * matrix1.points[2][0]) + (matrix.points[1][3] * matrix1.points[3][0]);
	multi.points[1][1] = (matrix.points[1][0] * matrix1.points[0][1]) + (matrix.points[1][1] * matrix1.points[1][1]) + (matrix.points[1][2] * matrix1.points[2][1]) + (matrix.points[1][3] * matrix1.points[3][1]);
	multi.points[1][2] = (matrix.points[1][0] * matrix1.points[0][2]) + (matrix.points[1][1] * matrix1.points[1][2]) + (matrix.points[1][2] * matrix1.points[2][2]) + (matrix.points[1][3] * matrix1.points[3][2]);
	multi.points[1][3] = (matrix.points[1][0] * matrix1.points[0][3]) + (matrix.points[1][1] * matrix1.points[1][3]) + (matrix.points[1][2] * matrix1.points[2][3]) + (matrix.points[1][3] * matrix1.points[3][3]);

	multi.points[2][0] = (matrix.points[2][0] * matrix1.points[0][0]) + (matrix.points[2][1] * matrix1.points[1][0]) + (matrix.points[2][2] * matrix1.points[2][0]) + (matrix.points[2][3] * matrix1.points[3][0]);
	multi.points[2][1] = (matrix.points[2][0] * matrix1.points[0][1]) + (matrix.points[2][1] * matrix1.points[1][1]) + (matrix.points[2][2] * matrix1.points[2][1]) + (matrix.points[2][3] * matrix1.points[3][1]);
	multi.points[2][2] = (matrix.points[2][0] * matrix1.points[0][2]) + (matrix.points[2][1] * matrix1.points[1][2]) + (matrix.points[2][2] * matrix1.points[2][2]) + (matrix.points[2][3] * matrix1.points[3][2]);
	multi.points[2][3] = (matrix.points[2][0] * matrix1.points[0][3]) + (matrix.points[2][1] * matrix1.points[1][3]) + (matrix.points[2][2] * matrix1.points[2][3]) + (matrix.points[2][3] * matrix1.points[3][3]);

	multi.points[3][0] = (matrix.points[3][0] * matrix1.points[0][0]) + (matrix.points[3][1] * matrix1.points[1][0]) + (matrix.points[3][2] * matrix1.points[2][0]) + (matrix.points[3][3] * matrix1.points[3][0]);
	multi.points[3][1] = (matrix.points[3][0] * matrix1.points[0][1]) + (matrix.points[3][1] * matrix1.points[1][1]) + (matrix.points[3][2] * matrix1.points[2][1]) + (matrix.points[3][3] * matrix1.points[3][1]);
	multi.points[3][2] = (matrix.points[3][0] * matrix1.points[0][2]) + (matrix.points[3][1] * matrix1.points[1][2]) + (matrix.points[3][2] * matrix1.points[2][2]) + (matrix.points[3][3] * matrix1.points[3][2]);
	multi.points[3][3] = (matrix.points[3][0] * matrix1.points[0][3]) + (matrix.points[3][1] * matrix1.points[1][3]) + (matrix.points[3][2] * matrix1.points[2][3]) + (matrix.points[3][3] * matrix1.points[3][3]);

	return multi;
}

static void SetMatrixInverse(Matrix matrix) {

	
	Matrix inverseMatrix;
	//set the inverse of the matrix and get ready to swap
	inverseMatrix.points[0][1] = matrix.points[1][0];
	inverseMatrix.points[0][2] = matrix.points[2][0];
	inverseMatrix.points[1][0] = matrix.points[0][1];
	inverseMatrix.points[1][2] = matrix.points[2][1];
	inverseMatrix.points[2][0] = matrix.points[0][2];
	inverseMatrix.points[2][1] = matrix.points[1][2];

	matrix = inverseMatrix;

	matrix.points[3][0] = -( (matrix.points[3][0] * matrix.points[0][0]) + (matrix.points[3][1] * matrix.points[1][0]) + (matrix.points[3][2] * matrix.points[2][0]));
	matrix.points[3][1] = -( (matrix.points[3][0] * matrix.points[0][1]) + (matrix.points[3][1] * matrix.points[1][1]) + (matrix.points[3][2] * matrix.points[2][1]));
	matrix.points[3][2] = -( (matrix.points[3][0] * matrix.points[0][2]) + (matrix.points[3][1] * matrix.points[1][2]) + (matrix.points[3][2] * matrix.points[2][2]));


}

static Matrix RotXMatrix(float rads)
{
	Matrix rotX;

	rotX.points[0][0] = 1;			rotX.points[0][1] = 0;
	rotX.points[0][2] = 0;			rotX.points[0][3] = 0;

	rotX.points[1][0] = 0;			rotX.points[1][1] = cosf(rads);
	rotX.points[1][2] = -sinf(rads);  rotX.points[1][3] = 0;

	rotX.points[2][0] = 0;			rotX.points[2][1] = sinf(rads);
	rotX.points[2][2] = cosf(rads);	rotX.points[2][3] = 0;

	rotX.points[3][0] = 0;			rotX.points[3][1] = 0;
	rotX.points[3][2] = 0;			rotX.points[3][3] = 1;

	return rotX;
}

static Matrix RotYMatrix(float rads)
{
	Matrix roty;

	roty.points[0][0] = cosf(rads);
	roty.points[0][1] = 0.0;
	roty.points[0][2] = sinf(rads);
	roty.points[0][3] = 0.0;
	//
	roty.points[1][0] = 0.0;
	roty.points[1][1] = 1;
	roty.points[1][2] = 0.0;
	roty.points[1][3] = 0.0;
	//
	roty.points[2][0] = -sinf(rads);
	roty.points[2][1] = 0.0;
	roty.points[2][2] = cosf(rads);
	roty.points[2][3] = 0.0;
	//
	roty.points[3][0] = 0.0;
	roty.points[3][1] = 0.0;
	roty.points[3][2] = 0.0;
	roty.points[3][3] = 1.0;

	return roty;
}

static Matrix PerspectiveProjection(float Near, float Far, float vFOV, float AspRat)
{
	Matrix projectionMatrix;
	float cot = (1 / tan(vFOV / 2));
	float farminNear = (Far / (Far - Near));
	float FarmultNear = (-(Far * Near) / (Far - Near));

	projectionMatrix.points[0][0] = (cot*AspRat);
	projectionMatrix.points[0][1] = 0;
	projectionMatrix.points[0][2] = 0;
	projectionMatrix.points[0][3] = 0;

	projectionMatrix.points[1][0] = 0;
	projectionMatrix.points[1][1] = cot;
	projectionMatrix.points[1][2] = 0;
	projectionMatrix.points[1][3] = 0;

	projectionMatrix.points[2][0] = 0;
	projectionMatrix.points[2][1] = 0;
	projectionMatrix.points[2][2] = farminNear;
	projectionMatrix.points[2][3] = -1;
	
	projectionMatrix.points[3][0] = 0;
	projectionMatrix.points[3][1] = 0;
	projectionMatrix.points[3][2] = FarmultNear; 
	projectionMatrix.points[3][3] = 0;

	return projectionMatrix;
}

