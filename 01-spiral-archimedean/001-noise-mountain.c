#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "../common/noise.c"

#define TWOPI 6.28318530718

// output
char filename[128] = "001-noise-mountain.svg\0";
char path[128] = "out/\0";

// document
int width = 800;
int height = 800;

// shape
int REVOLUTIONS = 50;
int START_RADIUS = 3;
float SPACING = 3.0f;


int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));
	float seed = rand()%1000/100.0;

	strcat(path, filename);
	FILE *file = fopen(path, "w");
	// HEADER
	fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(file, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" ");
	fprintf(file, "x=\"0px\" y=\"0px\" width=\"%dpx\" height=\"%dpx\" ", width, height);
	fprintf(file, "viewBox=\"0 0 %d %d\">\n", width, height);
	// BODY
	fprintf(file, "<g>\n");
	fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"");  // hanging open polyline

	float x, y;
	unsigned char newPolyline = 0;
	for(int i = START_RADIUS; i < REVOLUTIONS; i++){
		float circleResolution = i * 20;  // how many points in one full circle
		for(float a = 0; a < TWOPI; a += TWOPI/circleResolution){

			float revolution = a/TWOPI;  // 0-1, progress of one revolution

			float bend1 = noise1(seed + a*3)*(i-3)*.7;
			float bend2 = noise1(seed + 8+a*10) * powf(i-20,2)*.1;
			if(i < 20) bend2 = 0;
			float bend3 = noise1(-seed - a*40) * (i-40)*1.2;
			if(i < 40) bend3 = 0;

			float radius1 = (i + revolution + bend1) * SPACING;

			x = width*.5  + cosf(a) * radius1 + cos(a) * bend2 - sin(a) * bend3;
			y = height*.5 + sinf(a) * radius1 + sin(a) * bend2 - cos(a) * bend3;
			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}
	fprintf(file, "\"/>\n"); // closing polyline

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}