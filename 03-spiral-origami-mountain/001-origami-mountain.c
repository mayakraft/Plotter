#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "../common/noise.c"

#define TWOPI 6.28318530718

// output
char filename[128] = "001-mountain.svg\0";
char path[128] = "out/\0";

// document
int width = 800;
int height = 800;

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

	float SCALE = 100;
	for(int i = 1; i < 4; i++){
		float circleResolution = 5 * 60;
		for(float a = 0; a < TWOPI; a += TWOPI/circleResolution){
			float bend1 = noise1(seed + a*3)*(i)*.7;
			float bend2 = noise1(seed + 8+a*10) * powf(i-2,2);
			if(i == 1) 
				bend2 = noise1(seed + 8+a*10) * powf(i-1.5,2);
				// bend2 = 0;
			float bend3 = noise1(-seed - a*40) * (i-4);
			// if(i < 4) 
				bend3 = 0;
			float x = width*.5  + SCALE * cos(a) * (i + bend1 + bend2);// * (i + bend1)+ cos(a) * bend2 - sin(a) * bend3;
			float y = height*.5 + SCALE * sin(a) * (i + bend1 + bend2);// * (i + bend1)+ sin(a) * bend2 - cos(a) * bend3;
			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}
	fprintf(file, "\"/>\n"); // closing polyline

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}