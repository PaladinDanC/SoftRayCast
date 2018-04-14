#pragma once
#include "allStructs.h"
//Pre-Rasterization. 
void(*VertexShader)(Vertex&) = 0;

//Post-Rasterization.
void(*PixelShader)(Vertex&) = 0;

//(Always Pre-fixed by “SV_”)
Matrix sv_WorldMatrix;
Matrix sv_CubeWorld;
Matrix sv_GridWorld;
Matrix sv_Viewer;
Matrix sv_Projection;

void VS_World(Vertex &vert)
{
	//world matrix to move into the world
	MultiplyVertexByMatrix(vert, sv_WorldMatrix);
	//view matrix to set up the main camera
	MultiplyVertexByMatrix(vert, sv_Viewer);
	//projection matrix for better camera and depth
	MultiplyVertexByMatrix(vert, sv_Projection);

	vert.xyzw[0] = vert.xyzw[0] / vert.xyzw[3];
	vert.xyzw[1] = vert.xyzw[1] / vert.xyzw[3];
	vert.xyzw[2] = vert.xyzw[2] / vert.xyzw[3];
}

