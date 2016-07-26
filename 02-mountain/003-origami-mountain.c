#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "../common/noise.c"

#define TWOPI 6.28318530718

// output
char filename[128] = "003-mountain.svg\0";
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

	float SCALE = 60;
	for(int i = 1; i < 6; i++){
		float circleResolution = 10 * 60;
		for(float a = 0; a < TWOPI; a += TWOPI/circleResolution){
			float bend1 = noise1(seed + a*2)*3;
			float bend2 = noise1(seed + 8+a*3) * powf(i-3,1.5) * 1.5;
			if(i < 3) 
				bend2 = 0;
			// 	bend2 = noise1(seed + 8+a*10) * powf(i-1.5,2);
				// bend2 = 0;
			// float bend3 = noise1(-seed - a*40) * (i-2) * 0.2;
			// if(i < 3) 
				// bend3 = 0;

			float weight1 = (1+cos(i/4.0*M_PI))*.5;
			float weight2 = (1-cos(i/4.0*M_PI))*.5;

			float x = width*.5  + SCALE * cos(a) * (i + bend1*weight1 + bend2*weight2);// * (i + bend1)+ cos(a) * bend2 - sin(a) * bend3;
			float y = height*.5 + SCALE * sin(a) * (i + bend1*weight1 + bend2*weight2);// * (i + bend1)+ sin(a) * bend2 - cos(a) * bend3;
			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}
	fprintf(file, "\"/>\n"); // closing polyline

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}