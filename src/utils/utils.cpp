/**
 * @file utils.cpp
 * @author Matthew Sasakamoose (matt.sasakamoose@gmail.com)
 * @brief utility function implementations for the purple rain project
 * @version 0.1
 * @date 2022-01-22 
 */

#include "utils.h"

// Maps the input within the input range [inputStart, inputEnd], to the output range [outputStart, outputEnd]
float map (float input, float inputStart, float inputEnd, float outputStart, float outputEnd) {
	float slope = (outputEnd - outputStart) / (inputEnd - inputStart);
	return outputStart + (slope * (input - inputStart));
}

// Produces a random integer in the range [a, b]
int random(int a, int b) {
	return a + (rand() % ((b - a) + 1));
}

//input: ratio is between 0.0 to 1.0
//output: rgb color
//based from https://stackoverflow.com/questions/40629345/fill-array-dynamicly-with-gradient-color-c
uint32_t gradient(float ratio)
{
    //we want to normalize ratio so that it fits in to 6 regions
    //where each region is 256 units long
    int normalized = int(ratio * 256 * 6);

    //find the region for this position
    int region = normalized / 256;

    //find the distance to the start of the closest region
    int x = normalized % 256;

    uint8_t r = 0, g = 0, b = 0, a = olc::nDefaultAlpha;
    switch (region)
    {
    case 0: r = 255; g = 0;   b = 0;   g += x; break;
    case 1: r = 255; g = 255; b = 0;   r -= x; break;
    case 2: r = 0;   g = 255; b = 0;   b += x; break;
    case 3: r = 0;   g = 255; b = 255; g -= x; break;
    case 4: r = 0;   g = 0;   b = 255; r += x; break;
    case 5: r = 255; g = 0;   b = 255; b -= x; break;
    }
    return (r << 0) + (g << 8) + (b << 16) + (a << 24);
}