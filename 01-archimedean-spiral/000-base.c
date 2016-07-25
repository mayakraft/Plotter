#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TWOPI 6.28318530718

// output
char filename[128] = "000-base.svg\0";
char path[128] = "out/\0";

// document
int width = 800;
int height = 800;

// shape
int REVOLUTIONS = 50;
float SPACING = 7.0f;

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
	fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"");  // hanging open polyline

	float x, y;
	for(int i = START_RADIUS; i < REVOLUTIONS; i++){
		float circleResolution = i * 10;  // how many points in one full circle
		for(float a = 0; a < TWOPI; a += TWOPI/circleResolution){
			
			float revolution = a/TWOPI;  // 0-1, progress of one revolution
			float radius = (i + revolution) * SPACING;

			x = width*.5  + cosf(a) * radius;
			y = height*.5 + sinf(a) * radius;
			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}
	fprintf(file, "\"/>\n"); // closing polyline

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}