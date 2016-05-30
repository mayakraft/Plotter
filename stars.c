#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define TWOPI 6.28318530718

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));

	int width = 640;
	int height = 640;

	char path[128];
	path[0] = '\0';
	// strcat(path, directory);
	// strcat(path, filename);
	strcat(path, "stars.svg");
	FILE *file = fopen(path, "w");
	fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(file, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" ");
	fprintf(file, "x=\"0px\" y=\"0px\" width=\"");
	fprintf(file, "%d",width);
	fprintf(file, "px\" height=\"");
	fprintf(file, "%d",height);
	fprintf(file, "px\" viewBox=\"0 0 ");
	fprintf(file, "%d",width);
	fprintf(file, " ");
	fprintf(file, "%d",height);
	fprintf(file, "\" xml:space=\"preserve\">\n");

	fprintf(file, "<g>\n");
	fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"");  // hanging open quote

	float x, y;
	for(int i = 0; i < 3; i++){
		x = rand()%width;
		y = rand()%height;
		int SIZE = 120 + rand()%150;
		float RADIUS = .4;
		float phase = rand()%628 / 100.0;
		for(float a = 0; a < phase + SIZE * TWOPI; a += .05){
			float rx = x + (cos(a) * a) * RADIUS;
			float ry = y + (sin(a) * a) * RADIUS;
			fprintf(file, "%.2f,%.2f ", rx, ry);
		}
		fprintf(file, "\"/>\n"); // closing quote
		fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"");  // hanging open quote
	}

	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}