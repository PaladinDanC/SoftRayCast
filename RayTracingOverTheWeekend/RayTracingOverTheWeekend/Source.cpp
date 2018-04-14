#include <iostream>
#include "includes.h"

unsigned int bitShiftARGB(unsigned int color)
{
	return	((color & 0xFF000000) >> 24) | ((color & 0x00FF0000) >> 8) |
		((color & 0x0000FF00) << 8) | ((color & 0x000000FF) << 24);

}

void PaintItBlack()
{
	//set all to black
	for (int i = 0; i < numofPixs; i++)
	{
		rasterArray[i] = 0;
	}
}

void resetBuff()
{
	//set all to black
	for (int i = 0; i < numofPixs; i++)
	{
		zBuffer[i] = 255;
	}
}
//converts to ARGB format
unsigned int ConvertIntToColor(int R, int G, int B, int A)
{
	unsigned int finalColor = 0xffffffff;

return	finalColor = ((A & 0x000000FF) << 24) | ((R & 0x000000FF) << 16)| ((G & 0x000000FF) << 8)| ((B & 0x000000FF));

}

int main()
{

	for (int j = WHeight -1; j >=0; j--)
	{
		for (int i = 0; i < WWidth; i++)
		{
			float r = float(i) / float(WWidth);
			float g = float(j) / float(WHeight);
			float b = 0.2;
			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);

			PlotPixel(i, WHeight - j, ConvertIntToColor(ir, ig, ib, 1));
			
		}
	}
	RS_Initialize(WWidth, WHeight);
	while (RS_Update(rasterArray, numofPixs))
	{

	}
	RS_Shutdown();
}