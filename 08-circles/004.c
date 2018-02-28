#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TWOPI 6.28318530718
#define EPSILON 0.00001

// output
char filename[128] = "004.svg\0";
char path[128] = "out/\0";

// document
int width = 800;
int height = 800;

// shape
int NUM = 4;
int START_RADIUS = 2;
float SPACING = 32.0f;

// waves
float wobbleFreq = 7.0;
float wobbleMag = 1.5;

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));

	strcat(path, filename);
	FILE *file = fopen(path, "w");
	// HEADER
	fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(file, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" ");
	fprintf(file, "x=\"0px\" y=\"0px\" width=\"%dpx\" height=\"%dpx\" ", width, height);
	fprintf(file, "viewBox=\"0 0 %d %d\">\n", width, height);
	// BODY
	fprintf(file, "<g>\n");

	float x, y;
	for(int i = START_RADIUS; i < START_RADIUS + NUM; i++){

		float wobbleMagLoop = wobbleMag*sqrt(i-START_RADIUS+1);
		
		if(i%2==0){
			fprintf(file, "<polyline fill=\"none\" stroke=\"#FF005C\" stroke-width=\"2\" stroke-miterlimit=\"10\" stroke-dasharray=\"5.9976,2.9988\" points=\"");  // hanging open polyline
		} else{
			fprintf(file, "<polyline fill=\"none\" stroke=\"#0000FF\" stroke-width=\"2\" stroke-miterlimit=\"10\" points=\"");  // hanging open polyline
		}
		float circleResolution = (i+2) * 80;  // how many points in one full circle
		for(float a = 0; a <= TWOPI + EPSILON; a += TWOPI/circleResolution){
			// growth of each ring slows exponentially
			float shift = 0;//-powf((i-START_RADIUS),3);
			float secondLevel = sin(a*wobbleFreq*2+M_PI*0.5) * wobbleMagLoop * (i-3) * 1.8;
			if(i < 3) secondLevel = 0;
			float thirdLevel = sin(a*wobbleFreq*4+M_PI*0.5) * wobbleMagLoop * (i-3);
			// if(i < 3) thirdLevel = 0;
			thirdLevel = 0;
			
			float radius = SPACING * 2*i
			               + sin(a*wobbleFreq) * wobbleMagLoop * i
			               + secondLevel
			               + thirdLevel
			               + shift;
			x = width*.5  + cosf(a) * radius;
			y = height*.5 + sinf(a) * radius;
			fprintf(file, "%.2f,%.2f ", x, y);
		}
		fprintf(file, "\"/>\n"); // closing polyline
	}

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}