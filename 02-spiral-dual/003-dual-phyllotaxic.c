#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "../common/noise.c"

#define TWOPI 6.28318530718

// output
char filename[128] = "003-dual-phyllotaxic.svg\0";
char path[128] = "out/\0";

// document
int width = 800;
int height = 800;

// shape
int REVOLUTIONS = 6;
float SPACING = 7.0f;
float SCALE = 26;
float wobbleFreq = 19.0;
float wobbleMag = 0.4;
// float SCALE = 45;
// float REVOLUTIONS = 7;
// float wobbleFreq = 7.0;
// float wobbleMag = 0.33;
float circleResolution = 5 * 60;

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

	for(int i = REVOLUTIONS-1; i >= 0; i--){
		for(float a = TWOPI; a >= 0; a -= TWOPI/circleResolution){
			float revolution = 2*(i+a/TWOPI);
			float x = width*.5  + cos(a) * SCALE * (revolution + sin(a*wobbleFreq)*wobbleMag);
			float y = height*.5 + sin(a) * SCALE * (revolution + sin(a*wobbleFreq)*wobbleMag);
			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}

	// // OPTIONAL: pick up the pen when it gets to the middle
	// fprintf(file, "\"/>\n"); // closing quote
	// fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote

	for(int i = 0; i < REVOLUTIONS; i++){
		for(float a = 0; a < TWOPI; a += TWOPI/circleResolution){
			float revolution = 2*(i+a/TWOPI);
			float x = width*.5  + cos(a-TWOPI*.5) * SCALE * (revolution + sin(a*wobbleFreq)*wobbleMag);
			float y = height*.5 + sin(a-TWOPI*.5) * SCALE * (revolution + sin(a*wobbleFreq)*wobbleMag);
			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}

	// fprintf(file, "\"/>\n"); // closing quote
	// fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote

	// int i = 14;
	// 	for(float a = 0; a <= TWOPI+.0001; a += TWOPI/circleResolution){
	// 		float wobbleIncr = 5*sqrt(i + 2*a/TWOPI);
	// 		wobbleIncr = 1.0;
	// 		x = width*.5  + SCALE * cos(a) * (i + sin(a*wobbleFreq)*wobbleMag*wobbleIncr );
	// 		y = height*.5 + SCALE * sin(a) * (i + sin(a*wobbleFreq)*wobbleMag*wobbleIncr );
	// 		fprintf(file, "%.2f,%.2f ", x, y);
	// 	}

	//+ cos(turn) * .2*sqrt(i + 2*a/TWOPI) 
	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}