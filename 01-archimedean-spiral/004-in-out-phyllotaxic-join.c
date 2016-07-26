#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "../common/noise.c"

#define TWOPI 6.28318530718

// output
char filename[128] = "004-phyllotaxic-join.svg\0";
char path[128] = "out/\0";

// document
int width = 800;
int height = 800;

// shape
int REVOLUTIONS = 8;
float SPACING = 7.0f;

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

	float divider = 10 * 60;
	float wobbleFreq = 13.0;
	float wobbleMag = 1;
	// wobbleFreq = 7.0;
	// wobbleMag = 0.33;

	for(int i = REVOLUTIONS-1; i >= 0; i--){
		for(float a = TWOPI; a >= 0; a -= TWOPI/divider){
			float revolution = 2*(i+a/TWOPI);
			float SCALE = 1.5 * revolution;
			float x = width*.5  + cos(a) * SCALE * (revolution + sin(a*wobbleFreq)*wobbleMag );
			float y = height*.5 + sin(a) * SCALE * (revolution + sin(a*wobbleFreq)*wobbleMag );
			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}

	// // OPTIONAL: pick up the pen when it gets to the middle
	// fprintf(file, "\"/>\n"); // closing polyline
	// fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open polyline

	for(int i = 0; i < REVOLUTIONS; i++){
		for(float a = 0; a < TWOPI; a += TWOPI/divider){
			float revolution = 2*(i+a/TWOPI);
			float SCALE = 1.5 * revolution;
			float x = width*.5  + cos(a-TWOPI*.5) * SCALE * (revolution + sin(a*wobbleFreq)*wobbleMag );
			float y = height*.5 + sin(a-TWOPI*.5) * SCALE * (revolution + sin(a*wobbleFreq)*wobbleMag );
			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}

	fprintf(file, "\"/>\n"); // closing polyline

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}