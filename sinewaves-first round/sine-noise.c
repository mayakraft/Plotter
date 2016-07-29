#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../common/noise.c"

#define TWOPI 6.28318530718

// output
char filename[128] = "sine-noise.svg\0";
char path[128] = "out/\0";

// document
int width = 1200;
int height = 800;

// shape
float COLUMNS = 16;
float waveMag = 18;

int posNeg(int in){
	if(in == 0){ return -1; }
	return 1;
}

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));
	float seed = rand()%1000/100.0;

	strcat(path, filename);
	FILE *file = fopen(path, "w");
	fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(file, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" ");
	fprintf(file, "x=\"0px\" y=\"0px\" width=\"%dpx\" height=\"%d", width, height);
	fprintf(file, "px\" viewBox=\"0 0 %d %d", width, height);
	fprintf(file, "\" xml:space=\"preserve\">\n<g>\n");

	for(int i = 0; i < COLUMNS; i++){
		fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote
		for(float j = 0; j < height; j++){
			int halfI = floor(i*.5);
			int one = 1.5*floor((i+0)*.25);
			int three = 1.5*floor((i+2)*.25);

			float vec[2];
			vec[0] = i*.33;
			vec[1] = j/(float)height*3;

			float xShift = 30 * noise2(vec);

			float x = 70 + 40*i + 30*one + 30*three + waveMag*sinf(j*.023) * posNeg(halfI%2) + xShift;
			float y = j;

			fprintf(file, "%.2f,%.2f ", x, y);
		}
		fprintf(file, "\"/>\n"); // closing quote
	}
	// fprintf(file, "\"/>\n"); // closing quote
	// fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote

	// float turn = 0;
	// for(int i = 0; i < COLUMNS; i+=2){
	// 	for(float j = 0; j < TWOPI; j += TWOPI/divider){
	// 		x = 0;
	// 		y = 0;
	// 		fprintf(file, "%.2f,%.2f ", x, y);
	// 	}
	// }


	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}